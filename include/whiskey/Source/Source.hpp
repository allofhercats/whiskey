#ifndef __WHISKEY_Source_Source_HPP
#define __WHISKEY_Source_Source_HPP

#include <string>

#include <whiskey/Unicode/Endianness.hpp>
#include <whiskey/Unicode/String.hpp>

namespace whiskey {
class Source {
  friend class Location;

public:
  enum Encoding { Auto, UTF8, UTF16LE, UTF16BE, UTF32LE, UTF32BE };

  static int getEncodingWidth(Encoding encoding);
  static Endianness getEncodingEndianness(Encoding encoding);

private:
  std::string path;
  String *text;

public:
  static const std::string defaultPath;

  Source(std::string path = defaultPath);
  Source(const Source &) = delete;
  Source &operator=(const Source &) = delete;

  bool loadString(const String &value);
  bool loadFile(Encoding encoding = Auto);

  const std::string &getPath() const;
  void setPath(std::string value);

  const String &getText() const;
};
} // namespace whiskey

#endif
