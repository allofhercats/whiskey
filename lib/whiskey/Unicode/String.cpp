#include <whiskey/Unicode/String.hpp>

#include <whiskey/Unicode/StringRef.hpp>
#include <whiskey/Unicode/StringContainer.hpp>

namespace whiskey {
String::String() : encoding(Encoding::Auto), length(0) {
	data.asChar8 = nullptr;
}

String::String(Encoding encoding) : encoding(encoding), length(0) {
	data.asChar8 = nullptr;
}

String::String(const Char8 *value) : String(value, getStringLength(value)) {}

String::String(const Char8 *value, size_t length) : encoding(Encoding::UTF8), length(length) {
	data.asChar8 = (Char8 *)value;
}

String::String(const Char16 *value) : String(value, getStringLength(value)) {}

String::String(const Char16 *value, size_t length) : length(length) {
	if (getSystemEndianness() == Endianness::Little) {
		encoding = Encoding::UTF16LE;
	} else {
		encoding = Encoding::UTF16BE;
	}
	data.asChar16 = (Char16 *)value;
}

String::String(const Char32 *value) : String(value, getStringLength(value)) {}

String::String(const Char32 *value, size_t length) : length(length) {
	if (getSystemEndianness() == Endianness::Little) {
		encoding = Encoding::UTF32LE;
	} else {
		encoding = Encoding::UTF32BE;
	}
	data.asChar32 = (Char32 *)value;
}

String::String(const std::string &value) : String(value.c_str()) {}

String::String(const std::string &value, size_t length) : String(value.c_str(), length) {
	W_ASSERT_ULE(length, value.size(), "Cannot access past end of string.");
}

String::String(const std::u16string &value) : String(value.c_str()) {}

String::String(const std::u16string &value, size_t length) : String(value.c_str(), length) {
	W_ASSERT_ULE(length, value.size(), "Cannot access past end of string.");
}

String::String(const std::u32string &value) : String(value.c_str()) {}

String::String(const std::u32string &value, size_t length) : String(value.c_str(), length) {
	W_ASSERT_ULE(length, value.size(), "Cannot access past end of string.");
}

Encoding String::getEncoding() const {
	return encoding;
}

size_t String::getLength() const {
	return length;
}

void String::setLength(size_t value) {
	W_ASSERT_ULE(value, length, "Cannot access past end of string.");
}

Char8 String::getChar8At(size_t index) const {
	W_ASSERT_EQ(getEncodingWidth(encoding), 1, "Cannot access " << getEncodingWidth(encoding) << "-byte width string as 1-byte width.");
	W_ASSERT_ULT(index, length, "Cannot access past end of string.");
	return data.asChar8[index];
}

Char16 String::getChar16At(size_t index) const {
	W_ASSERT_EQ(getEncodingWidth(encoding), 2, "Cannot access " << getEncodingWidth(encoding) << "-byte width string as 2-byte width.");
	W_ASSERT_ULT(index, length, "Cannot access past end of string.");
	return data.asChar16[index];
}

Char32 String::getChar32At(size_t index) const {
	W_ASSERT_EQ(getEncodingWidth(encoding), 4, "Cannot access " << getEncodingWidth(encoding) << "-byte width string as 4-byte width.");
	W_ASSERT_ULT(index, length, "Cannot access past end of string.");
	return data.asChar32[index];
}

Char32 String::getCharAt(size_t index) const {
	return eatCharAt(index);
}

Char32 String::eatCharAt(size_t &index) const {
	switch (getEncodingWidth(encoding)) {
		case 1:
			return readCharUTF8(data.asChar8, index, length);
		case 2:
			return readCharUTF16(data.asChar16, index, length);
		case 4:
			return readCharUTF32(data.asChar32, index, length);
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}
}

StringRef String::subString(size_t offset) const {
	if (offset >= length) {
		return StringRef();
	}

	return subString(offset, length - offset);
}

StringRef String::subString(size_t offset, size_t length) const {
	if (offset+length >= this->length) {
		return StringRef();
	}

	switch (getEncodingWidth(encoding)) {
		case 1:
			return StringRef(data.asChar8 + offset, length);
		case 2:
			return StringRef(data.asChar16 + offset, length);
		case 4:
			return StringRef(data.asChar32 + offset, length);
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}
}

size_t String::findFirst(Char32 value) const {
	for (size_t i = 0; i < length;) {
		size_t tmp = i;
		if (eatCharAt(tmp) == value) {
			return i;
		} else {
			i = tmp;
		}
	}

	return -1;
}

size_t String::findFirst(Char32 value, size_t after) const {
	for (size_t i = after; i < length;) {
		size_t tmp = i;
		if (eatCharAt(tmp) == value) {
			return i;
		} else {
			i = tmp;
		}
	}

	return -1;
}

size_t String::findFirst(const String &value) const {
	if (length < value.getLength()) {
		return -1;
	}

	for (size_t i = 0; i < length;) {
		if (subString(i, value.getLength()).compare(value)) {
			return i;
		} else {
			eatCharAt(i);
		}
	}

	return -1;
}

size_t String::findFirst(const String &value, size_t after) const {
	if (after >= length) {
		return -1;
	}

	if (length - after < value.getLength()) {
		return -1;
	}

	for (size_t i = 0; i < length;) {
		if (subString(i, value.getLength()).compare(value)) {
			return i;
		} else {
			eatCharAt(i);
		}
	}

	return -1;
}

size_t String::findLast(Char32 value) const {
	for (ssize_t i = length - 1; i >= 0; i--) {
		size_t tmp = i;
		if (eatCharAt(tmp) == value) {
			return i;
		}
	}

	return -1;
}

size_t String::findLast(Char32 value, size_t after) const {
	for (ssize_t i = length - 1; i >= (ssize_t)after; i--) {
		size_t tmp = i;
		if (eatCharAt(tmp) == value) {
			return i;
		}
	}

	return -1;
}

size_t String::findLast(const String &value) const {
	if (length < value.getLength()) {
		return -1;
	}

	for (ssize_t i = length - 1; i >= 0; i--) {
		if (subString(i, value.getLength()).compare(value)) {
			return i;
		}
	}

	return -1;
}

size_t String::findLast(const String &value, size_t after) const {
	if (after >= length) {
		return -1;
	}

	if (length - after < value.getLength()) {
		return -1;
	}

	for (ssize_t i = length - 1; i >= 0; i--) {
		if (subString(i, value.getLength()).compare(value)) {
			return i;
		}
	}

	return -1;
}

bool String::compare(const String &value) const {
	if (length != value.length) {
		return false;
	}

	for (size_t i = 0, j = 0; i < length && j < value.length;) {
		if (eatCharAt(i) != value.eatCharAt(j)) {
			return false;
		}
	}

	return true;
}

bool String::compare(const String &value, size_t length) const {
	if (this->length < length || value.length < length) {
		return false;
	}

	for (size_t i = 0, j = 0; i < length && j < length;) {
		if (eatCharAt(i) != value.eatCharAt(j)) {
			return false;
		}
	}

	return true;
}

StringContainer String::convertToEncoding(Encoding encoding) const {
	StringContainer rtn(encoding);
	for (size_t i = 0; i < length;) {
		rtn.append(eatCharAt(i));
	}
	return rtn;
}
}
