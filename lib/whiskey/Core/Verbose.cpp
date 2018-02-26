#include <whiskey/Core/Verbose.hpp>

#include <string.h>
#include <libgen.h>

#include <iostream>

namespace whiskey {
namespace {
std::ostream *verboseOStream = nullptr;
}

bool verbose = false;

std::ostream &getVerboseOStream() {
  if (verboseOStream == nullptr) {
    verboseOStream = &std::cerr;
  }

  return *verboseOStream;
}

void setVerboseOStream(std::ostream &os) {
  verboseOStream = &os;
}

void printVerbosePrefix(const char *file, int line, const char *func) {
	char buf[W_VERBOSE_PATH_MAXLEN];
	size_t len = strlen(file);
	if (len >= W_VERBOSE_PATH_MAXLEN) {
		strncpy(buf, file + (len + 1 - W_VERBOSE_PATH_MAXLEN), W_VERBOSE_PATH_MAXLEN);
	} else {
		strncpy(buf, file, W_VERBOSE_PATH_MAXLEN);
	}
	getVerboseOStream() << "[" << basename(buf) << ":" << std::dec << line << ": " << func << "] ";
}

void printVerboseSuffix() {
	getVerboseOStream() << "\n";
}
}
