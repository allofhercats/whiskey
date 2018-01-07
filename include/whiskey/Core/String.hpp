#ifndef __WHISKEY_Core_String_HPP
#define __WHISKEY_Core_String_HPP

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Char.hpp>

namespace whiskey {
class StringRef;

class String {
  friend class StringContainer;

public:
  typedef uint32_t Length;
  typedef int32_t Index;

  struct const_iterator {
  private:
    const Char8 *pointer;
    CharWidth width;

  public:
    const_iterator(const Char8 *pointer, CharWidth width);

    Char32 get() const;
    Char32 operator*() const;

    const_iterator &operator++();
    const_iterator operator++(int);

    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;
  };

  struct const_reverse_iterator {
  private:
    const Char8 *pointer;
    CharWidth width;

  public:
    const_reverse_iterator(const Char8 *pointer, CharWidth width);

    Char32 get() const;
    Char32 operator*() const;

    const_reverse_iterator &operator++();
    const_reverse_iterator operator++(int);

    bool operator==(const const_reverse_iterator &other) const;
    bool operator!=(const const_reverse_iterator &other) const;
  };

protected:
  CharWidth width;
  union {
    Char8 *asChar8;
    Char16 *asChar16;
    Char32 *asChar32;
  } data;
  Length length;

public:
  String();

  bool isGood() const;

  CharWidth getWidth() const;
  const Char8 *getData8() const;
  const Char16 *getData16() const;
  const Char32 *getData32() const;

  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;

  size_t size() const;
  void clear();
  bool empty() const;

  Char32 operator[](Index index) const;
  Char32 at(Index index) const;
  Char32 back() const;
  Char32 front() const;

  ssize_t find(Char32 value) const;
  ssize_t find(StringRef value) const;
  ssize_t rfind(Char32 value) const;
  ssize_t rfind(StringRef value) const;

  StringRef substr(Index offset, Length length = 0);

  bool compare();

  bool operator<(const String &other) const;
  bool operator<=(const String &other) const;
  bool operator>(const String &other) const;
  bool operator>=(const String &other) const;
  bool operator!=(const String &other) const;
  bool operator==(const String &other) const;
};
} // namespace whiskey

#endif
