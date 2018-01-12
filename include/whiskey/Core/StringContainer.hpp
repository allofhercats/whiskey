#ifndef __WHISKEY_Core_StringContainer_HPP
#define __WHISKEY_Core_StringContainer_HPP

#include <whiskey/Core/String.hpp>
#include <whiskey/Core/StringRef.hpp>

namespace whiskey {
/*class StringContainer : public String {
private:
  size_t _capacity;

public:
  static size_t getLowerBoundPow2(size_t value, size_t min = 32);

  StringContainer();
  StringContainer(const char *value, size_t length = 0);
  StringContainer(const char16_t *value, size_t length = 0);
  StringContainer(const char32_t *value, size_t length = 0);
  StringContainer(const wchar_t *value, size_t length = 0);
  StringContainer(const std::string &value);
  StringContainer(const std::u16string &value);
  StringContainer(const std::u32string &value);
  StringContainer(const std::wstring &value);
  StringContainer(const StringRef &value);
  StringContainer(const StringContainer &other);
  StringContainer(StringContainer &&other);
  ~StringContainer();

  StringContainer &operator=(const StringContainer &other);
  StringContainer &operator=(StringContainer &&other);

  operator StringRef() const;

  Char8 *getData8();
  Char16 *getData16();
  Char32 *getData32();

  size_t capacity() const;
  void reserve(size_t value);
  void shrink_to_fit();

  void resize(size_t value);
  void resize(size_t value, Char32 chr);

  StringContainer &operator+=(const String &value);
  StringContainer &operator+=(Char32 value);
  StringContainer &operator+=(std::initializer_list<Char32> value);
  StringContainer &append(size_t n, Char32 value);
  StringContainer &append(const String &value);
  StringContainer &append(const String &value, size_t subpos, size_t sublen);
  template<class InputIterator>
  StringContainer &append(InputIterator first, InputIterator last);
  StringContainer &append(std::initializer_list<Char32> value);
  void push_back(Char32 value);
  StringContainer &assign(const String &value);
  StringContainer &assign(size_t n, Char32 value);
  template<class InputIterator>
  StringContainer &assign(InputIterator first, InputIterator last);
  StringContainer &assign(std::initializer_list<Char32> value);
  StringContainer &assign(StringContainer &&value);
  StringContainer &insert(size_t pos, const String &value);
  StringContainer &insert(size_t pos, const String &value, size_t valueOffset, size_t valueLength);
  StringContainer &insert(size_t pos, size_t n, Char32 value);
  StringContainer &insert(const_iterator pos, size_t n, Char32 value);
  StringContainer &insert(const_iterator pos, Char32 value);
  template<class InputIterator>
  StringContainer &insert(const_iterator pos, InputIterator first, InputIterator last);
  StringContainer &insert(const_iterator pos, std::initializer_list<Char32> value);
  StringContainer &erase(size_t pos, size_t len = npos);
  StringContainer &erase(const_iterator pos);
  StringContainer &erase(const_iterator first, const_iterator last);
  void swap(StringContainer &other);
  StringContainer &replace(size_t pos, size_t len, const String &value);
  StringContainer &replace(const_iterator first, const_iterator last, const String &value);
  StringContainer &replace(size_t pos, size_t len, const String &value, size_t subpos, size_t sublen);
  StringContainer &replace(size_t pos, size_t len, size_t n, Char32 value);
  StringContainer &replace(const_iterator first, const_iterator last, size_t n, Char32 value);
  template<class InputIterator>
  StringContainer &replace(const_iterator from, const_iterator to, InputIterator first, InputIterator last);
  StringContainer &replace(const_iterator first, const_iterator last, std::initializer_list<Char32> value);
  void pop_back();
};*/
} // namespace whiskey

#endif
