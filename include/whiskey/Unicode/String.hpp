#ifndef __WHISKEY_Unicode_String_HPP
#define __WHISKEY_Unicode_String_HPP

#include <whiskey/Unicode/Encoding.hpp>
#include <whiskey/Unicode/Char.hpp>

namespace whiskey {
class StringRef;
class StringContainer;

class String {
	friend class StringContainer;

private:
	Encoding encoding;
	union {
		Char8 *asChar8;
		Char16 *asChar16;
		Char32 *asChar32;
	} data;
	size_t length;

public:
	String();
	String(Encoding encoding);
	String(const Char8 *value);
	String(const Char8 *value, size_t length);
	String(const Char16 *value);
	String(const Char16 *value, size_t length);
	String(const Char32 *value);
	String(const Char32 *value, size_t length);
	String(const std::string &value);
	String(const std::string &value, size_t length);
	String(const std::u16string &value);
	String(const std::u16string &value, size_t length);
	String(const std::u32string &value);
	String(const std::u32string &value, size_t length);
	
	Encoding getEncoding() const;

	size_t getLength() const;
	void setLength(size_t value);

	Char8 getChar8At(size_t index) const;
	Char16 getChar16At(size_t index) const;
	Char32 getChar32At(size_t index) const;
	
	Char32 getCharAt(size_t index) const;
	Char32 eatCharAt(size_t &index) const;
	
	StringRef subString(size_t offset) const;
	StringRef subString(size_t offset, size_t length) const;

	size_t findFirst(Char32 value) const;
	size_t findFirst(Char32 value, size_t after) const;
	size_t findFirst(const String &value) const;
	size_t findFirst(const String &value, size_t after) const;
	size_t findLast(Char32 value) const;
	size_t findLast(Char32 value, size_t after) const;
	size_t findLast(const String &value) const;
	size_t findLast(const String &value, size_t after) const;

	bool compare(const String &value) const;
	bool compare(const String &value, size_t length) const;

	StringContainer convertToEncoding(Encoding encoding) const;
};
}

#endif
