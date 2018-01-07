#ifndef __WHISKEY_Core_String_HPP
#define __WHISKEY_Core_String_HPP

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Char.hpp>

namespace whiskey {
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

  Length getLength() const;
  Char32 getChar(Index index) const;

  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};
} // namespace whiskey

#endif
