#include <whiskey/Source/Source.hpp>

#include <string.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
int Source::getEncodingWidth(Source::Encoding encoding) {
  switch (encoding) {
  case Auto:
    W_ASSERT_UNREACHABLE("Cannot get width of encoding Auto.");
    break;
  case UTF8:
    return 1;
  case UTF16LE:
    return 2;
  case UTF16BE:
    return 2;
  case UTF32LE:
    return 4;
  case UTF32BE:
    return 4;
  default:
    W_ASSERT_UNREACHABLE("Unsupported encoding " << (int)encoding << ".");
  }
}

bool Source::isEncodingBE(Source::Encoding encoding) {
  switch (encoding) {
  case Auto:
    W_ASSERT_UNREACHABLE("Cannot get endianness of encoding Auto.");
    break;
  case UTF8:
    W_ASSERT_UNREACHABLE("Cannot get endianness of encoding UTF8.");
    break;
  case UTF16LE:
    return false;
  case UTF16BE:
    return true;
  case UTF32LE:
    return false;
  case UTF32BE:
    return true;
  default:
    W_ASSERT_UNREACHABLE("Unsupported encoding " << (int)encoding << ".");
  }
}

bool Source::isHostBE() {
  int x = 1;
  const char *p = (const char *)&x;
  if (p[0] == 1 && (p[1] == 0 && (p[2] == 0 && p[3] == 0))) {
    return false;
  } else if (p[0] == 0 && (p[1] == 0 && (p[2] == 0 && p[3] == 1))) {
    return true;
  } else {
    W_ASSERT_UNREACHABLE("Cannot detect system endianness.");
  }
}

char16_t Source::swapBytes16(char16_t value) {
  return (value << 8) | (value >> 8);
}

char32_t Source::swapBytes32(char32_t value) {
  return ((value >> 24) & 0xff) | ((value << 8) & 0xff0000) |
         ((value >> 8) & 0xff00) | ((value << 24) & 0xff000000);
}

void Source::unload() {
  if (owned) {
    delete[](char *) data;
  }
  data = nullptr;
}

bool Source::load(void *data, unsigned int width, size_t length, bool copy) {
  W_ASSERT_NONNULL(data, "Cannot load null data.");
  W_ASSERT_TRUE(width == 1 || width == 2 || width == 4,
                "Unsupported character width " << width << ".");

  unload();

  this->width = width;

  if (length == 0) {
    if (width == 1) {
      const char *p = (const char *)data;
      while (*p != 0) {
        p++;
        length++;
      }
    } else if (width == 2) {
      const char16_t *p = (const char16_t *)data;
      while (*p != 0) {
        p++;
        length++;
      }
    } else if (width == 4) {
      const char32_t *p = (const char32_t *)data;
      while (*p != 0) {
        p++;
        length++;
      }
    } else {
      W_ASSERT_UNREACHABLE("Unsupported character width " << width << ".");
    }
  }

  this->length = length;

  if (copy) {
    this->data = new char[width * (this->length + 1)];
    memcpy(this->data, data, width * this->length);
    memset((char *)this->data + (width * this->length), 0, width);
    owned = true;
  } else {
    this->data = data;
    owned = false;
  }

  return true;
}

Source::Source(std::string path)
    : path(path), owned(false), data(nullptr), width(0), length(0) {
  W_ASSERT_GT(path.size(), 0, "Cannot have empty path.");
}

Source::~Source() {
  unload();
}

bool Source::isLoaded() const {
  return data != nullptr;
}

bool Source::loadCString(const char *text) {
  return loadCString(text, 0, false);
}

bool Source::loadCString(const char *text, bool copy) {
  return loadCString(text, 0, copy);
}

bool Source::loadCString(const char *text, size_t length, bool copy) {
  return load((void *)text, 1, length, copy);
}

bool Source::loadCWString(const wchar_t *text) {
  return loadCWString(text, 0, false);
}

bool Source::loadCWString(const wchar_t *text, bool copy) {
  return loadCWString(text, 0, copy);
}

bool Source::loadCWString(const wchar_t *text, size_t length, bool copy) {
  return load((void *)text, sizeof(wchar_t), length, copy);
}

bool Source::loadC16String(const char16_t *text) {
  return loadC16String(text, 0, false);
}

bool Source::loadC16String(const char16_t *text, bool copy) {
  return loadC16String(text, 0, copy);
}

bool Source::loadC16String(const char16_t *text, size_t length, bool copy) {
  return load((void *)text, 2, length, copy);
}

bool Source::loadC32String(const char32_t *text) {
  return loadC32String(text, 0, false);
}

bool Source::loadC32String(const char32_t *text, bool copy) {
  return loadC32String(text, 0, copy);
}

bool Source::loadC32String(const char32_t *text, size_t length, bool copy) {
  return load((void *)text, 4, length, copy);
}

bool Source::loadString(const std::string &text, bool copy) {
  return load((void *)text.c_str(), 1, text.size(), copy);
}

bool Source::loadWString(const std::wstring &text, bool copy) {
  return load((void *)text.c_str(), sizeof(wchar_t), text.size(), copy);
}

bool Source::loadU16String(const std::u16string &text, bool copy) {
  return load((void *)text.c_str(), 2, text.size(), copy);
}

bool Source::loadU32String(const std::u32string &text, bool copy) {
  return load((void *)text.c_str(), 4, text.size(), copy);
}

bool Source::loadFile(Source::Encoding encoding) {
  unload();

  FILE *f = fopen(path.c_str(), "r");
  if (f == NULL) {
    return false;
  }

  fseek(f, SEEK_END, 0);
  size_t l = ftell(f);
  fseek(f, SEEK_SET, 0);

  char bom[4];
  memset(bom, 0, sizeof(bom));
  int bomCount = fread(bom, 1, 4, f);

  W_ASSERT_LE(bomCount,
              l,
              "Could not read more than " << bomCount << " byte"
                                          << (bomCount == 1 ? "" : "s")
                                          << " of a " << l << " byte file.");

  if (bom[0] == '\xef' && (bom[1] == '\xbb' && bom[2] == '\xbf')) {
    W_ASSERT_TRUE(encoding == Auto || encoding == UTF8,
                  "Detected encoding conflicts with specified.");
    encoding = UTF8;
  } else if (bom[0] == '\xff' &&
             (bom[1] == '\xfe' && (bom[2] == '\x00' && bom[3] == '\x00'))) {
    W_ASSERT_TRUE(encoding == Auto || encoding == UTF32LE,
                  "Detected encoding conflicts with specified.");
    encoding = UTF32LE;
  } else if (bom[0] == '\x00' &&
             (bom[1] == '\x00' && (bom[2] == '\xfe' && bom[3] == '\xff'))) {
    W_ASSERT_TRUE(encoding == Auto || encoding == UTF32BE,
                  "Detected encoding conflicts with specified.");
    encoding = UTF32BE;
  } else if (bom[0] == '\xff' && bom[1] == '\xfe') {
    W_ASSERT_TRUE(encoding == Auto || encoding == UTF16LE,
                  "Detected encoding conflicts with specified.");
    encoding = UTF16LE;
  } else if (bom[0] == '\xfe' && bom[1] == '\xff') {
    W_ASSERT_TRUE(encoding == Auto || encoding == UTF16BE,
                  "Detected encoding conflicts with specified.");
    encoding = UTF16BE;
  } else {
    W_ASSERT_TRUE(encoding == Auto || encoding == UTF8,
                  "Detected encoding conflicts with specified.");
    encoding = UTF8;
  }

  width = getEncodingWidth(encoding);

  fseek(f, SEEK_SET, 0);

  if (width == 1) {
    char *buf = new char[l + 1];
    ssize_t r = fread(buf, 1, l, f);
    W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    buf[l] = 0;

    data = (void *)buf;
    length = l;
  } else if (width == 2) {
    char16_t *buf = new char16_t[l / 2 + 1];
    ssize_t r = fread(buf, 1, 2 * l, f);
    W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    buf[l / 2] = 0;

    if (isEncodingBE(encoding) != isHostBE()) {
      char16_t *p = buf;
      size_t i = 0;
      while (i < l / 2) {
        *p = swapBytes16(*p);
        p++;
        i++;
      }
    }

    data = (void *)buf;
    length = l;
  } else if (width == 4) {
    char32_t *buf = new char32_t[l / 4 + 1];
    ssize_t r = fread(buf, 1, 4 * l, f);
    W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    buf[l / 4] = 0;

    if (isEncodingBE(encoding) != isHostBE()) {
      char32_t *p = buf;
      size_t i = 0;
      while (i < l / 4) {
        *p = swapBytes32(*p);
        p++;
        i++;
      }
    }

    data = (void *)buf;
    length = l;
  } else {
    W_ASSERT_UNREACHABLE("Unsupported width " << width << ".");
  }

  owned = true;

  fclose(f);
  return true;
}

const std::string &Source::getPath() const {
  return path;
}

void Source::setPath(std::string value) {
  W_ASSERT_GT(value.size(), 0, "Cannot have empty path.");
  path = value;
}

unsigned int Source::getCharWidth() const {
  W_ASSERT_TRUE(isLoaded(), "Cannot access unloaded source.");
  return width;
}

size_t Source::getLength() const {
  W_ASSERT_TRUE(isLoaded(), "Cannot access unloaded source.");
  return length;
}
} // namespace whiskey
