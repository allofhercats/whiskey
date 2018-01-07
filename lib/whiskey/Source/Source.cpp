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

Endianness Source::getEncodingEndianness(Source::Encoding encoding) {
  switch (encoding) {
  case Auto:
    W_ASSERT_UNREACHABLE("Cannot get endianness of encoding Auto.");
    break;
  case UTF8:
    W_ASSERT_UNREACHABLE("Cannot get endianness of encoding UTF8.");
    break;
  case UTF16LE:
    return Endianness::Little;
  case UTF16BE:
    return Endianness::Big;
  case UTF32LE:
    return Endianness::Little;
  case UTF32BE:
    return Endianness::Big;
  default:
    W_ASSERT_UNREACHABLE("Unsupported encoding " << (int)encoding << ".");
  }
}

const std::string Source::defaultPath = "--";

Source::Source(std::string path)
    : path(path) {
  W_ASSERT_GT(path.size(), 0, "Cannot have empty path.");
}

bool Source::loadString(StringContainer value) {
  text = value;
  return true;
}

bool Source::loadFile(Source::Encoding encoding) {
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

  int width = getEncodingWidth(encoding);

  fseek(f, SEEK_SET, 0);

  text = StringContainer();

  if (width == 1) {
    text = "";
    text.setCapacity(l);
    ssize_t r = fread(text.getData8(), 1, l, f);
    W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    text.setLength(l);
  } else if (width == 2) {
    // char16_t *buf = new char16_t[l / 2 + 1];
    // ssize_t r = fread(buf, 1, 2 * l, f);
    // W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    // buf[l / 2] = 0;

    // if (isEncodingBE(encoding) != isHostBE()) {
    //   char16_t *p = buf;
    //   size_t i = 0;
    //   while (i < l / 2) {
    //     *p = swapBytes16(*p);
    //     p++;
    //     i++;
    //   }
    // }

    // data = (void *)buf;
    // length = l;
    text = u"";
    text.setCapacity(l/2);
    ssize_t r = fread(text.getData16(), 1, l, f);
    W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    text.setLength(l/2);
  } else if (width == 4) {
    // char32_t *buf = new char32_t[l / 4 + 1];
    // ssize_t r = fread(buf, 1, 4 * l, f);
    // W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    // buf[l / 4] = 0;

    // if (isEncodingBE(encoding) != isHostBE()) {
    //   char32_t *p = buf;
    //   size_t i = 0;
    //   while (i < l / 4) {
    //     *p = swapBytes32(*p);
    //     p++;
    //     i++;
    //   }
    // }

    // data = (void *)buf;
    // length = l;
    text = U"";
    text.setCapacity(l/4);
    ssize_t r = fread(text.getData32(), 1, l, f);
    W_ASSERT_EQ(r, l, "Could not read all characters from file.");
    text.setLength(l/4);
  } else {
    W_ASSERT_UNREACHABLE("Unsupported width " << width << ".");
  }

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

const StringContainer &Source::getText() const {
  return text;
}
} // namespace whiskey
