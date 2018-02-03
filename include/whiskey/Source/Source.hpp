#ifndef __WHISKEY_Source_Source_HPP
#define __WHISKEY_Source_Source_HPP

#include <istream>
#include <string>

#define W_SOURCE_DEFAULT_PATH "--"

namespace whiskey {
class Source {
private:
  std::istream *is;
  std::istream::off_type offset;
  std::istream::off_type length;
  std::string defaultPath;

public:
  Source(std::istream &is, std::string defaultPath = W_SOURCE_DEFAULT_PATH);

  const std::string &getDefaultPath() const;

  std::istream::off_type getOffset() const;
  void setOffset(std::istream::off_type value);

  bool more() const;
  char get() const;
  char eat();
};
} // namespace whiskey

#endif
