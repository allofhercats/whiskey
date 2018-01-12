#include <whiskey/Core/StringContainer.hpp>

#include <string.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
size_t StringContainer::getLowerBoundPow2(size_t value,
                                                  size_t min) {
  size_t rtn = min;

  while (rtn < value) {
    rtn *= 2;
  }

  return rtn;
}

StringContainer::StringContainer() : String() {
}

StringContainer::StringContainer(const char *value,
                                 size_t _length)
    : String() {
  width = 1;
  this->_length = _length == 0 ? getStringLength(value) : _length;
  _capacity = getLowerBoundPow2(_length + 1);
  data.asChar8 = new Char8[_capacity];
  if (value != nullptr) {
    memcpy(data.asChar8, value, this->_length);
  }
  data.asChar8[this->_length] = 0;
}

StringContainer::StringContainer(const char16_t *value,
                                 size_t _length)
    : String() {
  width = 2;
  this->_length = _length == 0 ? getStringLength(value) : _length;
  _capacity = getLowerBoundPow2(_length + 1);
  data.asChar16 = new Char16[_capacity];
  if (value != nullptr) {
    memcpy(data.asChar16, value, this->_length * 2);
  }
  data.asChar16[this->_length] = 0;
}

StringContainer::StringContainer(const char32_t *value,
                                 size_t _length)
    : String() {
  width = 4;
  this->_length = _length == 0 ? getStringLength(value) : _length;
  _capacity = getLowerBoundPow2(_length + 1);
  data.asChar32 = new Char32[_capacity];
  if (value != nullptr) {
    memcpy(data.asChar32, value, this->_length * 4);
  }
  data.asChar32[this->_length] = 0;
}

StringContainer::StringContainer(const wchar_t *value,
                                 size_t _length)
    : String() {
  this->_length = _length == 0 ? getStringLength(value) : _length;
  _capacity = getLowerBoundPow2(_length + 1);
  if (sizeof(wchar_t) == 1) {
    width = 1;
    data.asChar8 = new Char8[_capacity];
    if (value != nullptr) {
      memcpy(data.asChar8, value, this->_length);
    }
    data.asChar8[this->_length] = 0;
  } else if (sizeof(wchar_t) == 2) {
    width = 2;
    data.asChar16 = new Char16[_capacity];
    if (value != nullptr) {
      memcpy(data.asChar16, value, this->_length * 2);
    }
    data.asChar16[this->_length] = 0;
  } else if (sizeof(wchar_t) == 4) {
    width = 4;
    data.asChar32 = new Char32[_capacity];
    if (value != nullptr) {
      memcpy(data.asChar32, value, this->_length * 4);
    }
    data.asChar32[this->_length] = 0;
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << sizeof(wchar_t) << ".");
  }
}

StringContainer::StringContainer(const std::string &value)
    : StringContainer(value.c_str(), value.size()) {
}

StringContainer::StringContainer(const std::u16string &value)
    : StringContainer(value.c_str(), value.size()) {
}

StringContainer::StringContainer(const std::u32string &value)
    : StringContainer(value.c_str(), value.size()) {
}

StringContainer::StringContainer(const std::wstring &value)
    : StringContainer(value.c_str(), value.size()) {
}

StringContainer::StringContainer(const StringRef &value) {
  width = value.width;
  _capacity = getLowerBoundPow2(_length + 1);
  data.asChar8 = new Char8[_capacity * value.width];
  if (value.data.asChar8 != nullptr) {
    memcpy(data.asChar8, value.data.asChar8, value._length * value.width);
  }
  _length = value._length;
}

StringContainer::StringContainer(const StringContainer &value) {
  width = value.width;
  _capacity = getLowerBoundPow2(_length + 1);
  data.asChar8 = new Char8[_capacity * value.width];
  if (value.data.asChar8 != nullptr) {
    memcpy(data.asChar8, value.data.asChar8, value._length * value.width);
  }
  _length = value._length;
}

StringContainer::StringContainer(StringContainer &&value) {
  width = value.width;
  data.asChar8 = value.data.asChar8;
  value.data.asChar8 = nullptr;
  _length = value._length;
  value._length = 0;
  _capacity = value._length;
  value._capacity = 0;
}

StringContainer::~StringContainer() {
  delete[] data.asChar8;
}

StringContainer &StringContainer::operator=(const StringContainer &other) {
  delete[] data.asChar8;

  width = other.width;
  _capacity = getLowerBoundPow2(_length + 1);
  data.asChar8 = new Char8[_capacity * other.width];
  if (other.data.asChar8 != nullptr) {
    memcpy(data.asChar8, other.data.asChar8, other._length * other.width);
  }
  _length = other._length;

  return *this;
}

StringContainer &StringContainer::operator=(StringContainer &&other) {
  delete[] data.asChar8;

  width = other.width;
  data.asChar8 = other.data.asChar8;
  other.data.asChar8 = nullptr;
  _length = other._length;
  other._length = 0;
  _capacity = other._length;
  other._capacity = 0;

  return *this;
}

StringContainer::operator StringRef() const {
  if (width == 1) {
    return StringRef(String::getData8(), size());
  } else if (width == 2) {
    return StringRef(String::getData16(), size());
  } else if (width == 4) {
    return StringRef(String::getData32(), size());
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << width << ".");
  }
}

Char8 *StringContainer::getData8() {
  W_ASSERT_EQ(width,
              1,
              "Cannot access char width " << width
                                          << " string as 1-byte wide.");
  return data.asChar8;
}

Char16 *StringContainer::getData16() {
  W_ASSERT_EQ(width,
              2,
              "Cannot access char width " << width
                                          << " string as 2-byte wide.");
  return data.asChar16;
}

Char32 *StringContainer::getData32() {
  W_ASSERT_EQ(width,
              4,
              "Cannot access char width " << width
                                          << " string as 4-byte wide.");
  return data.asChar32;
}

size_t StringContainer::capacity() const {
  return _capacity;
}

void StringContainer::reserve(size_t value) {
  W_ASSERT_GT(value, 0, "Cannot have non-positive _capacity.");
  W_ASSERT_LE(_length, value, "Cannot set _capacity to less than _length.");

  value = getLowerBoundPow2(value);

  if (value != _capacity) {
    Char8 *tmp = new Char8[value * width];
    if (data.asChar8 != nullptr) {
      memcpy(tmp, data.asChar8, width * _length);
    }

    delete[] data.asChar8;
    data.asChar8 = tmp;
    _capacity = value;
  }
}

void StringContainer::resize(size_t value) {
  if (value < _length) {
    _length = value;
  } else if (value > _length) {
    W_ASSERT_UNREACHABLE("Cannot resize to larger size.");
  }
}

void StringContainer::push_back(Char32 value) {
  if (_length + 4 >= _capacity) {
    reserve(_length + 4);
  }

  if (width == 1) {
    CharOffset tmp = _length;
    writeCharUTF8(data.asChar8, value, tmp, _capacity);
    _length = tmp;
  } else if (width == 2) {
    CharOffset tmp = _length;
    writeCharUTF16(data.asChar16, value, tmp, _capacity);
    _length = tmp;
  } else if (width == 4) {
    CharOffset tmp = _length;
    writeCharUTF32(data.asChar32, value, tmp, _capacity);
    _length = tmp;
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << width << ".");
  }
}

// void StringContainer::append(const String &value) {
//   if (value._length == 0) {
//     return;
//   }

//   if (_length + value._length >= _capacity) {
//     setCapacity(_length + value._length);
//   }

//   if (width == value.width) {
//     memcpy(data.asChar8 + (_length * width),
//            value.data.asChar8,
//            value._length * value.width);
//     _length += value._length;
//   } else {
//     CharOffset pos = 0;
//     while (pos < value._length) {
//       Char32 chr;
//       if (value.width == 1) {
//         chr = readCharUTF8(value.data.asChar8, pos, value._length);
//       } else if (value.width == 2) {
//         chr = readCharUTF16(value.data.asChar16, pos, value._length);
//       } else if (value.width == 4) {
//         chr = readCharUTF32(value.data.asChar32, pos, value._length);
//       } else {
//         W_ASSERT_UNREACHABLE("Unsupported char width " << value.width << ".");
//       }

//       append(chr);
//     }
//   }
// }
} // namespace whiskey
