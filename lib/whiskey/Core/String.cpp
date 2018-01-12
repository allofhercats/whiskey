#include <whiskey/Core/String.hpp>

#include <whiskey/Core/StringRef.hpp>

#include <iostream>

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

Char32 String::const_iterator::operator[](size_t n) const {
 if (width == 1) {
    return pointer[n] & 0xff;
  } else if (width == 2) {
    return ((const Char16 *)pointer)[n] & 0xffff;
  } else if (width == 4) {
    return ((const Char32 *)pointer)[n];
  } else {
    W_ASSERT_UNREACHABLE("Unsupported character width " << width << ".");
  } 
}

String::const_iterator &String::const_iterator::operator++() {
  pointer += width;
  return *this;
}

String::const_iterator String::const_iterator::operator++(int) {
  this->operator++();
  return *this;
}

String::const_iterator &String::const_iterator::operator--() {
  pointer -= width;
  return *this;
}

String::const_iterator String::const_iterator::operator--(int) {
  this->operator--();
  return *this;
}

bool String::const_iterator::
operator<(const String::const_iterator &other) const {
  return pointer < other.pointer;
}

bool String::const_iterator::
operator<=(const String::const_iterator &other) const {
  return pointer <= other.pointer;
}

bool String::const_iterator::
operator>(const String::const_iterator &other) const {
  return pointer > other.pointer;
}

bool String::const_iterator::
operator>=(const String::const_iterator &other) const {
  return pointer >= other.pointer;
}

bool String::const_iterator::
operator!=(const String::const_iterator &other) const {
  return pointer != other.pointer;
}

bool String::const_iterator::
operator==(const String::const_iterator &other) const {
  return pointer == other.pointer;
}

String::const_iterator &String::const_iterator::operator+=(ssize_t n) {
  pointer += width * n;
  return *this;
}

String::const_iterator &String::const_iterator::operator-=(ssize_t n) {
  pointer -= width * n;
  return *this;
}

String::const_reverse_iterator::const_reverse_iterator(const Char8 *pointer,
                                       CharWidth width)
    : pointer(pointer), width(width) {
}

Char32 String::const_reverse_iterator::get() const {
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

Char32 String::const_reverse_iterator::operator*() const {
  return get();
}

Char32 String::const_reverse_iterator::operator[](size_t n) const {
 if (width == 1) {
    return pointer[-n] & 0xff;
  } else if (width == 2) {
    return ((const Char16 *)pointer)[-n] & 0xffff;
  } else if (width == 4) {
    return ((const Char32 *)pointer)[-n];
  } else {
    W_ASSERT_UNREACHABLE("Unsupported character width " << width << ".");
  } 
}

String::const_reverse_iterator &String::const_reverse_iterator::operator++() {
  pointer -= width;
  return *this;
}

String::const_reverse_iterator String::const_reverse_iterator::operator++(int) {
  this->operator++();
  return *this;
}

String::const_reverse_iterator &String::const_reverse_iterator::operator--() {
  pointer += width;
  return *this;
}

String::const_reverse_iterator String::const_reverse_iterator::operator--(int) {
  this->operator--();
  return *this;
}

bool String::const_reverse_iterator::
operator<(const String::const_reverse_iterator &other) const {
  return pointer > other.pointer;
}

bool String::const_reverse_iterator::
operator<=(const String::const_reverse_iterator &other) const {
  return pointer >= other.pointer;
}

bool String::const_reverse_iterator::
operator>(const String::const_reverse_iterator &other) const {
  return pointer < other.pointer;
}

bool String::const_reverse_iterator::
operator>=(const String::const_reverse_iterator &other) const {
  return pointer <= other.pointer;
}

bool String::const_reverse_iterator::
operator!=(const String::const_reverse_iterator &other) const {
  return pointer != other.pointer;
}

bool String::const_reverse_iterator::
operator==(const String::const_reverse_iterator &other) const {
  return pointer == other.pointer;
}

String::const_reverse_iterator &String::const_reverse_iterator::operator+=(ssize_t n) {
  pointer -= width * n;
  return *this;
}

String::const_reverse_iterator &String::const_reverse_iterator::operator-=(ssize_t n) {
  pointer += width * n;
  return *this;
}

const size_t String::npos = (size_t)-1;

String::String() : width(1), _length(0) {
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

String::const_iterator String::begin() const {
  return cbegin();
}

String::const_iterator String::end() const {
  return cend();
}

String::const_reverse_iterator String::rbegin() const {
  return crbegin();
}

String::const_reverse_iterator String::rend() const {
  return crend();
}

String::const_iterator String::cbegin() const {
  return const_iterator(data.asChar8, width);
}

String::const_iterator String::cend() const {
  return const_iterator(data.asChar8 + (width * _length), width);
}

String::const_reverse_iterator String::crbegin() const {
  return const_reverse_iterator(data.asChar8 + (width * _length), width);
}

String::const_reverse_iterator String::crend() const {
  return const_reverse_iterator(data.asChar8, width);
}

size_t String::size() const {
  return _length;
}

size_t String::length() const {
  return _length;
}

void String::clear() {
  width = 1;
  data.asChar8 = nullptr;
  _length = 0;
}

bool String::empty() const {
  return _length == 0;
}

Char32 String::operator[](size_t index) const {
  return at(index);
}

Char32 String::at(size_t index) const {
  if (index >= _length) {
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

Char32 String::back() const {
  if (empty()) {
    return 0;
  } else {
    return at(size()-1);
  }
}

Char32 String::front() const {
  if (empty()) {
    return 0;
  } else {
    return at(0);
  }
}

size_t String::find(Char32 value) const {
  size_t n = 0;
  while (n < size()) {
    if (at(n) == value) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::find(StringRef value) const {
  size_t n = 0;
  while (n + value.size() < size()) {
    size_t m = 0;
    bool matched = true;
    while (m < value.size()) {
      if (at(n + m) != value.at(m)) {
        matched = false;
        break;
      }
    }

    if (matched) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::rfind(Char32 value) const {
  if (empty()) {
    return npos;
  }

  ssize_t n = size()-1;
  while (n >= 0) {
    if (at(n) == value) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::rfind(StringRef value) const {
  if (size() < value.size() + 1) {
    return npos;
  }

  ssize_t n = size() - value.size() - 1;
  while (n >= 0) {
    size_t m = 0;
    bool matched = true;
    while (m < value.size()) {
      if (at(n + m) != value.at(m)) {
        matched = false;
        break;
      }
    }

    if (matched) {
      return n;
    } else {
      n--;
    }
  }

  return npos;
}

size_t String::find_first_of(Char32 value) const {
  return find(value);
}

size_t String::find_first_of(StringRef value) const {
  size_t n = 0;
  while (n < size()) {
    if (value.find(at(n)) != String::npos) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::find_last_of(Char32 value) const {
  return rfind(value);
}

size_t String::find_last_of(StringRef value) const {
  if (empty()) {
    return npos;
  }

  ssize_t n = size()-1;
  while (n >= 0) {
    if (value.find(at(n)) != String::npos) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::find_first_not_of(Char32 value) const {
  size_t n = 0;
  while (n < size()) {
    if (at(n) != value) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::find_first_not_of(StringRef value) const {
  size_t n = 0;
  while (n < size()) {
    if (value.find(at(n)) == String::npos) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::find_last_not_of(Char32 value) const {
  if (empty()) {
    return npos;
  }

  ssize_t n = size()-1;
  while (n >= 0) {
    if (at(n) != value) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

size_t String::find_last_not_of(StringRef value) const {
  if (empty()) {
    return npos;
  }

  ssize_t n = size()-1;
  while (n >= 0) {
    if (value.find(at(n)) == String::npos) {
      return n;
    } else {
      n++;
    }
  }

  return npos;
}

StringRef String::substr(size_t offset, size_t length) const {
  if (length == npos) {
    length = this->_length;
  }

  if (offset + length > this->_length) {
    length = this->_length - offset;
  }

  if (offset >= this->_length) {
    return StringRef();
  } else if (width == 1) {
    return StringRef(data.asChar8+offset, length);
  } else if (width == 2) {
    return StringRef(data.asChar16+offset, length);
  } else if (width == 4) {
    return StringRef(data.asChar32+offset, length);
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << width << ".");
  }
}

int String::compare(const String &other) const {
  return compare(0, size(), other, 0, other.size());
}

int String::compare(size_t offset, size_t length, const String &other) const {
  return compare(offset, length, other, 0, other.size());
}

int String::compare(size_t offset, size_t length, const String &other, size_t subpos, size_t sublen) const {
  size_t ia = offset, ib = subpos;

  while (ia < length && ib < sublen) {
    if (at(ia) < other.at(ib)) {
      return -1;
    } else if (at(ia) > other.at(ib)) {
      return -1;
    }

    ++ia;
    ++ib;
  }

  if (length < sublen) {
    return -1;
  } else if (length > sublen) {
    return 1;
  }

  return 0;
}

bool String::operator<(const String &other) const {
  return compare(other) < 0;
}

bool String::operator<=(const String &other) const {
  return compare(other) <= 0;
}

bool String::operator>(const String &other) const {
  return compare(other) > 0;
}

bool String::operator>=(const String &other) const {
  return compare(other) >= 0;
}

bool String::operator!=(const String &other) const {
  return compare(other) != 0;
}

bool String::operator==(const String &other) const {
  return compare(other) == 0;
}

bool String::operator<(const char *other) const {
  return this->operator<(StringRef(other));
}

bool String::operator<=(const char *other) const {
  return this->operator<=(StringRef(other));
}

bool String::operator>(const char *other) const {
  return this->operator>(StringRef(other));
}

bool String::operator>=(const char *other) const {
  return this->operator>=(StringRef(other));
}

bool String::operator!=(const char *other) const {
  return this->operator!=(StringRef(other));
}

bool String::operator==(const char *other) const {
  return this->operator==(StringRef(other));
}

bool String::operator<(const char16_t *other) const {
  return this->operator<(StringRef(other));
}

bool String::operator<=(const char16_t *other) const {
  return this->operator<=(StringRef(other));
}

bool String::operator>(const char16_t *other) const {
  return this->operator>(StringRef(other));
}

bool String::operator>=(const char16_t *other) const {
  return this->operator>=(StringRef(other));
}

bool String::operator!=(const char16_t *other) const {
  return this->operator!=(StringRef(other));
}

bool String::operator==(const char16_t *other) const {
  return this->operator==(StringRef(other));
}

bool String::operator<(const char32_t *other) const {
  return this->operator<(StringRef(other));
}

bool String::operator<=(const char32_t *other) const {
  return this->operator<=(StringRef(other));
}

bool String::operator>(const char32_t *other) const {
  return this->operator>(StringRef(other));
}

bool String::operator>=(const char32_t *other) const {
  return this->operator>=(StringRef(other));
}

bool String::operator!=(const char32_t *other) const {
  return this->operator!=(StringRef(other));
}

bool String::operator==(const char32_t *other) const {
  return this->operator==(StringRef(other));
}

String::const_iterator operator+(const String::const_iterator &i, ssize_t n) {
  String::const_iterator rtn = i;
  rtn += n;
  return rtn;
}

String::const_iterator operator+(ssize_t n, const String::const_iterator &i) {
  String::const_iterator rtn = i;
  rtn += n;
  return rtn;
}

String::const_iterator operator-(const String::const_iterator &i, ssize_t n) {
  String::const_iterator rtn = i;
  rtn -= n;
  return rtn;
}

ssize_t operator-(const String::const_iterator &a, const String::const_iterator &b) {
  W_ASSERT_EQ(a.width, b.width, "Can only compare iterators of same width.");
  return (a.pointer - b.pointer) / a.width;
}

void swap(String::const_iterator &a, String::const_iterator &b) {
  String::const_iterator tmp = a;
  a = b;
  b = tmp;
}

String::const_reverse_iterator operator+(const String::const_reverse_iterator &i, ssize_t n) {
  String::const_reverse_iterator rtn = i;
  rtn += n;
  return rtn;
}

String::const_reverse_iterator operator+(ssize_t n, const String::const_reverse_iterator &i) {
  String::const_reverse_iterator rtn = i;
  rtn += n;
  return rtn;
}

String::const_reverse_iterator operator-(const String::const_reverse_iterator &i, ssize_t n) {
  String::const_reverse_iterator rtn = i;
  rtn -= n;
  return rtn;
}

ssize_t operator-(const String::const_reverse_iterator &a, const String::const_reverse_iterator &b) {
  W_ASSERT_EQ(a.width, b.width, "Can only compare iterators of same width.");
  return (b.pointer - a.pointer) / a.width;
}

void swap(String::const_reverse_iterator &a, String::const_reverse_iterator &b) {
  String::const_reverse_iterator tmp = a;
  a = b;
  b = tmp;
}
} // namespace whiskey
