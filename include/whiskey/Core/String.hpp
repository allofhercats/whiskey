#ifndef __WHISKEY_Core_String_HPP
#define __WHISKEY_Core_String_HPP

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Char.hpp>

namespace whiskey {
class String {
  friend class StringContainer;

public:
  typedef uint32_t Width;
  typedef uint32_t Length;
  typedef int32_t Index;

  struct const_iterator {
  private:
    const Char8 *pointer;
    Width width;

  public:
    const_iterator(const Char8 *pointer, Width width);

    Char32 get() const;
    Char32 operator*() const;

    const_iterator &operator++();
    const_iterator operator++(int);

    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;
  };

protected:
  Width width;
  union {
    Char8 *asChar8;
    Char16 *asChar16;
    Char32 *asChar32;
  } data;
  Length length;

public:
  static bool isValidWidth(Width value);

  template <typename T>
  static Length getLength(const T *value);

  template <typename T>
  static Char32 readCharFromString(const T *src, Length &pos, Length length);

  template <typename T>
  static void writeCharToString(Char32 chr, T *dst, Length &pos, Length length);

  String();

  bool isGood() const;

  Width getWidth() const;
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

#include <whiskey/Core/String.tpp>

#endif
