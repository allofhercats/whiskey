#include <whiskey/Source/Range.hpp>

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

std::string Range::getText() const {
  std::string rtn;
  Location i = start;
  while (i.getOffset() < start.getOffset() + length) {
    if (!i.areMoreChars()) {
      break;
    } else {
      rtn.push_back(i.getChar());
    }
    i.eatChar();
  }
  return rtn;
}
} // namespace whiskey
