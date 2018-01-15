#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Backtrace.hpp>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <bfd.h>
#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <link.h>
#include <unistd.h>
#include <string.h>

#include <whiskey/Core/Color.hpp>

namespace whiskey {
namespace {
struct PHeaderData {
  const char *file;
  void *address;
  void *base;
  void *hdr;
};

int onIteratePHeader(struct dl_phdr_info *info, size_t size, void *data) {
  PHeaderData *casted = (PHeaderData *)data;

  const ElfW(Phdr) *phdr = info->dlpi_phdr;

  for (long i = info->dlpi_phnum; i >= 0; i--) {
    if (phdr->p_type == PT_LOAD) {
      ElfW(Addr) vaddr = phdr->p_vaddr + info->dlpi_addr;
      if (casted->address >= (void *)vaddr &&
          casted->address < (void *)(vaddr + phdr->p_memsz)) {
        casted->file = info->dlpi_name;
        casted->base = (void *)info->dlpi_addr;
      }
    }

    phdr++;
  }

  return 0;
}

struct SectionData {
  bool found;
  bfd_vma address;
  asymbol **symbols;
  const char *filename;
  const char *funcname;
  unsigned int line;
};

void onMapOverSections(bfd *abfd, asection *section, void *data) {
  SectionData *casted = (SectionData *)data;

  if (casted->found) {
    return;
  }

  if ((bfd_get_section_flags(abfd, section) & SEC_ALLOC) == 0) {
    return;
  }

  bfd_vma vma = bfd_get_section_vma(abfd, section);
  if (casted->address < vma) {
    return;
  }

  bfd_size_type size = bfd_section_size(abfd, section);
  if (casted->address >= vma + size) {
    return;
  }

  casted->found = bfd_find_nearest_line(abfd,
                                        section,
                                        casted->symbols,
                                        casted->address - vma,
                                        &casted->filename,
                                        &casted->funcname,
                                        &casted->line);
}

std::string getBinaryNameAndOffsetOfSymbol(void *symbol, bfd_vma &addr) {
  PHeaderData data;
  data.address = symbol;
  dl_iterate_phdr(onIteratePHeader, &data);
  addr = (bfd_vma)symbol - (bfd_vma)data.base;
  if (data.file != nullptr && data.file[0] != 0) {
    return data.file;
  } else {
    return getCurrentBinaryName();
  }
}
} // namespace

std::string getCurrentBinaryName(int maxLength) {
  char *buf = new char[maxLength];
  ssize_t n = readlink("/proc/self/exe", buf, maxLength);
  if (n >= 0) {
    std::string rtn(buf, n);
    delete[] buf;
    return rtn;
  } else {
    return "/proc/self/exe";
  }
}

std::string getBinaryNameOfSymbol(void *symbol) {
  bfd_vma addr;
  return getBinaryNameAndOffsetOfSymbol(symbol, addr);
}

void printBacktrace(std::ostream &os, int maxDepth) {
  W_ASSERT_GT(maxDepth, 0, "Max depth must be positive.");

  os << "\n";

  void **symbols = new void *[maxDepth + 1];
  int depth = backtrace(symbols, maxDepth + 1);

  for (int i = 1; i < depth; i++) {
    bfd_vma addr;
    std::string binaryName = getBinaryNameAndOffsetOfSymbol(symbols[i], addr);

    bfd *abfd = bfd_openr(binaryName.c_str(), nullptr);
    if (abfd == nullptr) {
      continue;
    }

    if (bfd_check_format(abfd, bfd_archive) != 0) {
      continue;
    }

    if (bfd_check_format_matches(abfd, bfd_object, nullptr) == 0) {
      continue;
    }

    if ((bfd_get_file_flags(abfd) & HAS_SYMS) == 0) {
      continue;
    }

    asymbol **symbols;
    unsigned int size;
    long nSymbols = bfd_read_minisymbols(abfd, false, (void **)&symbols, &size);
    if (nSymbols == 0) {
      nSymbols = bfd_read_minisymbols(abfd, true, (void **)&symbols, &size);
    }

    if (nSymbols < 0) {
      continue;
    }

    SectionData data;
    data.found = false;
    data.address = addr;
    data.symbols = symbols;
    bfd_map_over_sections(abfd, onMapOverSections, (void *)&data);

    os << Color::greyLight << "[" << i << "] " << Color::reset;
    if (data.found) {
      if (data.filename != nullptr && data.filename[0] != 0) {
        os << data.filename << ":";
        if (data.line > 0) {
          os << data.line << ":";
        }
        os << "\n  ";
      }
      if (data.funcname != nullptr && data.funcname[0] != 0) {
        int status;
        char *realname = abi::__cxa_demangle(data.funcname, 0, 0, &status);
        if (realname != nullptr && realname[0] != 0) {
          if (strcmp(realname, "main") == 0) {
            os << "\n";
            break;
          }
          os << Color::cyan << realname << "\n" << Color::reset;
          free(realname);
        } else {
          if (strcmp(data.funcname, "main") == 0) {
            os << "\n";
            break;
          }
          os << Color::cyan << data.funcname << "\n" << Color::reset;
        }
      }

    } else {
      os << Color::cyan << binaryName << Color::yellowLight << "+" << symbols[i]
         << "\n"
         << Color::reset;
    }

    os << "\n";

    bfd_close(abfd);
  }
}
} // namespace whiskey
