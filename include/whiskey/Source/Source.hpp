#ifndef __WHISKEY_Source_Source_HPP
#define __WHISKEY_Source_Source_HPP

#include <string>

namespace whiskey {
class Source {
  friend class Location;

private:
  std::string path;
  std::string text;

public:
  static const std::string defaultPath;

  Source();
  Source(const Source &) = delete;
  Source &operator=(const Source &) = delete;

  void loadString(std::string value, std::string path = defaultPath);
  bool loadFile(std::string path);

  const std::string &getPath() const;
  void setPath(std::string value);

  bool isLoaded() const;
  const std::string &getText() const;
};
} // namespace whiskey

#endif
