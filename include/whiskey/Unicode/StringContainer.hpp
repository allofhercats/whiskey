#ifndef __WHISKEY_Unicode_StringContainer_HPP
#define __WHISKEY_Unicode_StringContainer_HPP

#include <string.h>

#include <whiskey/Unicode/String.hpp>
#include <whiskey/Unicode/StringRef.hpp>

namespace whiskey {
class StringContainer : public String {
private:
	size_t capacity;

	static size_t getNextPowOf2(size_t from);

	template<typename T>
	void assign(const T *data);

	template<typename T>
	void assign(const T *data, size_t length);

public:
	StringContainer();
	StringContainer(Encoding encoding);
	StringContainer(const Char8 *value);
	StringContainer(const Char8 *value, size_t length);
	StringContainer(const Char16 *value);
	StringContainer(const Char16 *value, size_t length);
	StringContainer(const Char32 *value);
	StringContainer(const Char32 *value, size_t length);
	StringContainer(const std::string &value);
	StringContainer(const std::string &value, size_t length);
	StringContainer(const std::u16string &value);
	StringContainer(const std::u16string &value, size_t length);
	StringContainer(const std::u32string &value);
	StringContainer(const std::u32string &value, size_t length);
	StringContainer(const StringRef &value);
	StringContainer(const StringContainer &other);
	StringContainer(StringContainer &&other);
	~StringContainer();

	StringContainer &operator=(const StringContainer &other);
	StringContainer &operator=(StringContainer &&other);

	operator StringRef() const;

	size_t getCapacity() const;
	void setCapacity(size_t value);

	void setChar8At(size_t index, Char8 value);
	void setChar16At(size_t index, Char16 value);
	void setChar32At(size_t index, Char32 value);

	void setCharAt(size_t index, Char32 value);
	void writeCharAt(size_t &index, Char32 value);

	void append(Char32 value, size_t length = 1);
	void append(const String &value);

	void remove(size_t offset, size_t length = 1);
	
	void insert(size_t offset, Char32 value, size_t length = 1);
	void insert(size_t offset, const String &value);
};
}

#include <whiskey/Unicode/StringContainer.tpp>

#endif
