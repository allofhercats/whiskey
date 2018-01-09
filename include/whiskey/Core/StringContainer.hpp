#ifndef __WHISKEY_Core_StringContainer_HPP
#define __WHISKEY_Core_StringContainer_HPP

#include <whiskey/Core/String.hpp>
#include <whiskey/Core/StringRef.hpp>

namespace whiskey {
class StringContainer : public String {
private:
  Length capacity;

public:
  static Length getLowerBoundPow2(Length value, Length min = 32);

  StringContainer();
  StringContainer(const char *value, Length length = 0);
  StringContainer(const char16_t *value, Length length = 0);
  StringContainer(const char32_t *value, Length length = 0);
  StringContainer(const wchar_t *value, Length length = 0);
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

  Length capacity() const;
  void reserve(Length value);
  void shrink_to_fit();

  void resize(size_t value);
  void resize(size_t value, Char32 chr);

  void append(size_t n, Char32 value);
  void append(const String &value);
  void push_back(Char32 value);
  void insert(size_t pos, const String &value);
  void insert(size_t pos, const String &value, size_t valueOffset, size_t valueLength);
  void insert(size_t pos, size_t n, Char32 value);
  void erase(size_t pos, size_t len = npos);
  void replace(size_t pos, size_t len, const String &value);
  void pop_back();
};
} // namespace whiskey

#endif
