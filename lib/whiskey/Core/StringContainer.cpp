#include <whiskey/Core/StringContainer.hpp>

#include <string.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
String::Length StringContainer::getLowerBoundPow2(String::Length value,
                                                  String::Length min) {
  String::Length rtn = min;

  while (rtn < value) {
    rtn *= 2;
  }

  return rtn;
}

StringContainer::StringContainer() : String() {
}

StringContainer::StringContainer(const char *value,
                                 StringContainer::Length length)
    : String() {
  width = 1;
  this->length = length == 0 ? getStringLength(value) : length;
  capacity = getLowerBoundPow2(length + 1);
  data.asChar8 = new Char8[capacity];
  if (value != nullptr) {
    memcpy(data.asChar8, value, this->length);
  }
  data.asChar8[this->length] = 0;
}

StringContainer::StringContainer(const char16_t *value,
                                 StringContainer::Length length)
    : String() {
  width = 2;
  this->length = length == 0 ? getStringLength(value) : length;
  capacity = getLowerBoundPow2(length + 1);
  data.asChar16 = new Char16[capacity];
  if (value != nullptr) {
    memcpy(data.asChar16, value, this->length * 2);
  }
  data.asChar16[this->length] = 0;
}

StringContainer::StringContainer(const char32_t *value,
                                 StringContainer::Length length)
    : String() {
  width = 4;
  this->length = length == 0 ? getStringLength(value) : length;
  capacity = getLowerBoundPow2(length + 1);
  data.asChar32 = new Char32[capacity];
  if (value != nullptr) {
    memcpy(data.asChar32, value, this->length * 4);
  }
  data.asChar32[this->length] = 0;
}

StringContainer::StringContainer(const wchar_t *value,
                                 StringContainer::Length length)
    : String() {
  this->length = length == 0 ? getStringLength(value) : length;
  capacity = getLowerBoundPow2(length + 1);
  if (sizeof(wchar_t) == 1) {
    width = 1;
    data.asChar8 = new Char8[capacity];
    if (value != nullptr) {
      memcpy(data.asChar8, value, this->length);
    }
    data.asChar8[this->length] = 0;
  } else if (sizeof(wchar_t) == 2) {
    width = 2;
    data.asChar16 = new Char16[capacity];
    if (value != nullptr) {
      memcpy(data.asChar16, value, this->length * 2);
    }
    data.asChar16[this->length] = 0;
  } else if (sizeof(wchar_t) == 4) {
    width = 4;
    data.asChar32 = new Char32[capacity];
    if (value != nullptr) {
      memcpy(data.asChar32, value, this->length * 4);
    }
    data.asChar32[this->length] = 0;
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
  capacity = getLowerBoundPow2(length + 1);
  data.asChar8 = new Char8[capacity * value.width];
  if (value.data.asChar8 != nullptr) {
    memcpy(data.asChar8, value.data.asChar8, value.length * value.width);
  }
  length = value.length;
}

StringContainer::StringContainer(const StringContainer &value) {
  width = value.width;
  capacity = getLowerBoundPow2(length + 1);
  data.asChar8 = new Char8[capacity * value.width];
  if (value.data.asChar8 != nullptr) {
    memcpy(data.asChar8, value.data.asChar8, value.length * value.width);
  }
  length = value.length;
}

StringContainer::StringContainer(StringContainer &&value) {
  width = value.width;
  data.asChar8 = value.data.asChar8;
  value.data.asChar8 = nullptr;
  length = value.length;
  value.length = 0;
  capacity = value.length;
  value.capacity = 0;
}

StringContainer::~StringContainer() {
  delete[] data.asChar8;
}

StringContainer &StringContainer::operator=(const StringContainer &other) {
  delete[] data.asChar8;

  width = other.width;
  capacity = getLowerBoundPow2(length + 1);
  data.asChar8 = new Char8[capacity * other.width];
  if (other.data.asChar8 != nullptr) {
    memcpy(data.asChar8, other.data.asChar8, other.length * other.width);
  }
  length = other.length;

  return *this;
}

StringContainer &StringContainer::operator=(StringContainer &&other) {
  delete[] data.asChar8;

  width = other.width;
  data.asChar8 = other.data.asChar8;
  other.data.asChar8 = nullptr;
  length = other.length;
  other.length = 0;
  capacity = other.length;
  other.capacity = 0;

  return *this;
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

String::Length StringContainer::getCapacity() const {
  return capacity;
}

void StringContainer::setCapacity(String::Length value) {
  W_ASSERT_GT(value, 0, "Cannot have non-positive capacity.");
  W_ASSERT_LE(length, value, "Cannot set capacity to less than length.");

  value = getLowerBoundPow2(value);

  if (value != capacity) {
    Char8 *tmp = new Char8[value * width];
    if (data.asChar8 != nullptr) {
      memcpy(tmp, data.asChar8, width * length);
    }

    delete[] data.asChar8;
    data.asChar8 = tmp;
    capacity = value;
  }
}

void StringContainer::setLength(String::Length value) {
  if (value < length) {
    length = value;
  } else if (value > length) {
    W_ASSERT_UNREACHABLE("Cannot resize to larger size.");
  }
}

void StringContainer::append(Char32 value) {
  if (length + 4 >= capacity) {
    setCapacity(length + 4);
  }

  if (width == 1) {
    CharOffset tmp = length;
    writeCharUTF8(data.asChar8, value, tmp, capacity);
    length = tmp;
  } else if (width == 2) {
    CharOffset tmp = length;
    writeCharUTF16(data.asChar16, value, tmp, capacity);
    length = tmp;
  } else if (width == 4) {
    CharOffset tmp = length;
    writeCharUTF32(data.asChar32, value, tmp, capacity);
    length = tmp;
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << width << ".");
  }
}

void StringContainer::append(const String &value) {
  if (value.length == 0) {
    return;
  }

  if (length + value.length >= capacity) {
    setCapacity(length + value.length);
  }

  if (width == value.width) {
    memcpy(data.asChar8 + (length * width),
           value.data.asChar8,
           value.length * value.width);
    length += value.length;
  } else {
    CharOffset pos = 0;
    while (pos < value.length) {
      Char32 chr;
      if (value.width == 1) {
        chr = readCharUTF8(value.data.asChar8, pos, value.length);
      } else if (value.width == 2) {
        chr = readCharUTF16(value.data.asChar16, pos, value.length);
      } else if (value.width == 4) {
        chr = readCharUTF32(value.data.asChar32, pos, value.length);
      } else {
        W_ASSERT_UNREACHABLE("Unsupported char width " << value.width << ".");
      }

      append(chr);
    }
  }
}
} // namespace whiskey
