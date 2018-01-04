#ifndef __WHISKEY_Core_StringRef_HPP
#define __WHISKEY_Core_StringRef_HPP

#include <whiskey/Core/String.hpp>

namespace whiskey {
class StringRef : public String {
friend class StringContainer;

public:
	StringRef();
	StringRef(const char *value, Length length = 0);
	StringRef(const char16_t *value, Length length = 0);
	StringRef(const char32_t *value, Length length = 0);
	StringRef(const wchar_t *value, Length length = 0);
	StringRef(const std::string &value);
	StringRef(const std::u16string &value);
	StringRef(const std::u32string &value);
	StringRef(const std::wstring &value);

	void setLength(Length value);
};
}

#endif
