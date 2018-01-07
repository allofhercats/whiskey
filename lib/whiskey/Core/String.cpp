#include <whiskey/Core/String.hpp>

namespace whiskey {
String::const_iterator::const_iterator(const Char8 *pointer,
                                       CharWidth width)
    : pointer(pointer), width(width) {
}

Char32 String::const_iterator::get() const {
  if (width == 1) {
    return *pointer & 0xff;
  } else if (width == 2) {
    return *((const Char16 *)pointer) & 0xffff;
  } else if (width == 4) {
    return *((const Char32 *)pointer);
  } else {
    W_ASSERT_UNREACHABLE("Unsupported character width " << width << ".");
  }
}

Char32 String::const_iterator::operator*() const {
  return get();
}

String::const_iterator &String::const_iterator::operator++() {
  pointer += width;
  return *this;
}

String::const_iterator String::const_iterator::operator++(int) {
  this->operator++();
  return *this;
}

bool String::const_iterator::
operator==(const String::const_iterator &other) const {
  return pointer == other.pointer;
}

bool String::const_iterator::
operator!=(const String::const_iterator &other) const {
  return !this->operator==(other);
}

String::String() : width(1), length(0) {
  data.asChar8 = nullptr;
}

bool String::isGood() const {
  return data.asChar8 != nullptr;
}

CharWidth String::getWidth() const {
  return width;
}

const Char8 *String::getData8() const {
  W_ASSERT_EQ(width,
              1,
              "Cannot access char width " << width
                                          << " string as 1-byte wide.");
  return data.asChar8;
}

const Char16 *String::getData16() const {
  W_ASSERT_EQ(width,
              2,
              "Cannot access char width " << width
                                          << " string as 2-byte wide.");
  return data.asChar16;
}

const Char32 *String::getData32() const {
  W_ASSERT_EQ(width,
              4,
              "Cannot access char width " << width
                                          << " string as 4-byte wide.");
  return data.asChar32;
}

String::Length String::getLength() const {
  return length;
}

Char32 String::getChar(String::Index index) const {
  if (index < 0 || index >= length) {
    return 0;
  } else if (width == 1) {
    return data.asChar8[index] & 0xff;
  } else if (width == 2) {
    return data.asChar16[index] & 0xffff;
  } else if (width == 4) {
    return data.asChar32[index];
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << width << ".");
  }
}

String::const_iterator String::begin() const {
  return cbegin();
}

String::const_iterator String::end() const {
  return cend();
}

String::const_iterator String::cbegin() const {
  return const_iterator(data.asChar8, width);
}

String::const_iterator String::cend() const {
  return const_iterator(data.asChar8 + (width * length), width);
}
} // namespace whiskey
