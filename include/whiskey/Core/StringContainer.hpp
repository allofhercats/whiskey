#ifndef __WHISKEY_Core_StringContainer_HPP
#define __WHISKEY_Core_StringContainer_HPP

#include <whiskey/Core/Module.inc>

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

	Char8 *getData8();
	Char16 *getData16();
	Char32 *getData32();

	Length getCapacity() const;
	void setCapacity(Length value);

	void setLength(Length value);

	void append(Char32 value);
	void append(const String &value);
};
}

#endif
