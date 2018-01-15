#ifndef __WHISKEY_Source_Source_HPP
#define __WHISKEY_Source_Source_HPP

#include <string>

#include <whiskey/Unicode/Endianness.hpp>
#include <whiskey/Unicode/StringRef.hpp>
#include <whiskey/Unicode/StringContainer.hpp>

namespace whiskey {
class Source {
  friend class Location;

private:
  std::string path;
  String *text;

public:
  static const std::string defaultPath;

  Source(std::string path = defaultPath);
  Source(const Source &) = delete;
  Source &operator=(const Source &) = delete;
  ~Source();

  bool loadString(StringContainer value);
  bool loadString(StringRef value);
  bool loadFile(Encoding encoding = Encoding::Auto);

  const std::string &getPath() const;
  void setPath(std::string value);

  bool isLoaded() const;
  const String &getText() const;
};
} // namespace whiskey

#endif
