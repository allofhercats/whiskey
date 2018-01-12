#include <whiskey/Source/Range.hpp>

#include <whiskey/Source/Source.hpp>

namespace whiskey {
Range::Range() : length(0) {
}

Range::Range(Location start, size_t length) : start(start), length(length) {
}

Range::Range(Location first, Location last)
    : start(first), length(Location::distance(first, last)) {
}

Location &Range::getStart() {
  return start;
}

const Location &Range::getStart() const {
  return start;
}

void Range::setStart(Location value) {
  start = value;
}

size_t Range::getLength() const {
  return length;
}

void Range::setLength(size_t value) {
  length = value;
}

StringRef Range::getText() const {
  return start.getSource().getText().substr(start.getOffset(), length);
}
} // namespace whiskey
