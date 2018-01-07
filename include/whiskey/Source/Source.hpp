#ifndef __WHISKEY_Source_Source_HPP
#define __WHISKEY_Source_Source_HPP

#include <string>

#include <whiskey/Core/Endianness.hpp>
#include <whiskey/Core/StringContainer.hpp>

namespace whiskey {
class Source {
  friend class Location;

public:
  enum Encoding { Auto, UTF8, UTF16LE, UTF16BE, UTF32LE, UTF32BE };

  static int getEncodingWidth(Encoding encoding);
  static Endianness getEncodingEndianness(Encoding encoding);

private:
  std::string path;
  StringContainer text;

public:
  static const std::string defaultPath;

  Source(std::string path = defaultPath);
  Source(const Source &) = delete;
  Source &operator=(const Source &) = delete;

  bool loadString(StringContainer value);
  bool loadFile(Encoding encoding = Auto);

  const std::string &getPath() const;
  void setPath(std::string value);

  const StringContainer &getText() const;
};
} // namespace whiskey

#endif
