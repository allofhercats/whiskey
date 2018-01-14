#ifndef __WHISKEY_Unicode_StringRef_HPP
#define __WHISKEY_Unicode_StringRef_HPP

#include <whiskey/Unicode/String.hpp>

namespace whiskey {
class StringRef : public String {
public:
	StringRef();
	StringRef(Encoding encoding);
	StringRef(const Char8 *value);
	StringRef(const Char8 *value, size_t length);
	StringRef(const Char16 *value);
	StringRef(const Char16 *value, size_t length);
	StringRef(const Char32 *value);
	StringRef(const Char32 *value, size_t length);
	StringRef(const std::string &value);
	StringRef(const std::string &value, size_t length);
	StringRef(const std::u16string &value);
	StringRef(const std::u16string &value, size_t length);
	StringRef(const std::u32string &value);
	StringRef(const std::u32string &value, size_t length);
};
}

#endif
