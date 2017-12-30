#ifndef __WHISKEY_Source_Source_HPP
#define __WHISKEY_Source_Source_HPP

#include <whiskey/Source/Module.inc>

#define W_DEFAULT_PATH "--"

namespace whiskey {
class Source {
  friend class Location;

public:
  enum Encoding { Auto, UTF8, UTF16LE, UTF16BE, UTF32LE, UTF32BE };

  static int getEncodingWidth(Encoding encoding);
  static bool isEncodingBE(Encoding encoding);
  static bool isHostBE();
  static char16_t swapBytes16(char16_t value);
  static char32_t swapBytes32(char32_t value);

private:
  std::string path;
  bool owned;
  void *data;
  unsigned int width;
  size_t length;

  void unload();
  bool load(void *data, unsigned int width, size_t length, bool copy);

public:
  Source(std::string path = W_DEFAULT_PATH);
  Source(const Source &) = delete;
  Source &operator=(const Source &) = delete;
  ~Source();

  bool isLoaded() const;
  bool loadCString(const char *text);
  bool loadCString(const char *text, bool copy);
  bool loadCString(const char *text, size_t length, bool copy);
  bool loadCWString(const wchar_t *text);
  bool loadCWString(const wchar_t *text, bool copy);
  bool loadCWString(const wchar_t *text, size_t length, bool copy);
  bool loadC16String(const char16_t *text);
  bool loadC16String(const char16_t *text, bool copy);
  bool loadC16String(const char16_t *text, size_t length, bool copy);
  bool loadC32String(const char32_t *text);
  bool loadC32String(const char32_t *text, bool copy);
  bool loadC32String(const char32_t *text, size_t length, bool copy);
  bool loadString(const std::string &text, bool copy = false);
  bool loadWString(const std::wstring &text, bool copy = false);
  bool loadU16String(const std::u16string &text, bool copy = false);
  bool loadU32String(const std::u32string &text, bool copy = false);
  bool loadFile(Encoding encoding = Auto);

  const std::string &getPath() const;
  void setPath(std::string value);

  unsigned int getCharWidth() const;
  size_t getLength() const;
};
} // namespace whiskey

#endif
