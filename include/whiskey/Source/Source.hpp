#ifndef __WHISKEY_Source_Source_HPP
#define __WHISKEY_Source_Source_HPP

#include <istream>
#include <string>

#include <whiskey/Core/Types.hpp>

#define W_SOURCE_DEFAULT_PATH "--"

namespace whiskey {
class Source {
private:
  std::istream *is;
  std::istream::off_type offset;
  std::istream::off_type length;
  std::string defaultPath;

public:
  static std::string stripUnneededWhitespace(const std::string &text);

  Source(std::istream &is, std::string defaultPath = W_SOURCE_DEFAULT_PATH);
  Source(const Source &) = delete;

  const std::string &getDefaultPath() const;

  std::istream::off_type getOffset() const;
  void setOffset(std::istream::off_type value);

  bool more() const;
  Char8 get() const;
  Char8 eat();
};
} // namespace whiskey

#endif
