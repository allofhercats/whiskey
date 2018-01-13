#ifndef __WHISKEY_Source_Range_HPP
#define __WHISKEY_Source_Range_HPP

#include <whiskey/Unicode/StringRef.hpp>
#include <whiskey/Source/Location.hpp>

namespace whiskey {
class Range {
private:
  Location start;
  size_t length;

public:
  Range();
  Range(Location start, size_t length = 0);
  Range(Location first, Location last);

  Location &getStart();
  const Location &getStart() const;
  void setStart(Location value);

  size_t getLength() const;
  void setLength(size_t value);

  StringRef getText() const;
};
} // namespace whiskey

#endif
