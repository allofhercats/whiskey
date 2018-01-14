#include <whiskey/Unicode/StringContainer.hpp>

namespace whiskey {
size_t StringContainer::getNextPowOf2(size_t next) {
	size_t rtn = 1;
	while (rtn <= next) {
		rtn *= 2;
	}
	return rtn;
}

StringContainer::StringContainer() : String(), capacity(0) {}

StringContainer::StringContainer(Encoding encoding) : String(encoding), capacity(0) {}

StringContainer::StringContainer(const Char8 *value) : StringContainer(value, getStringLength(value)) {}

StringContainer::StringContainer(const Char8 *value, size_t length) : String(Encoding::UTF8) {
	assign(value, length);
}

StringContainer::StringContainer(const Char16 *value) : StringContainer(value, getStringLength(value)) {}

StringContainer::StringContainer(const Char16 *value, size_t length) : String(getSystemEndianness() == Endianness::Little ? Encoding::UTF16LE : Encoding::UTF16BE) {
	assign(value, length);
}

StringContainer::StringContainer(const Char32 *value) : StringContainer(value, getStringLength(value)) {}

StringContainer::StringContainer(const Char32 *value, size_t length) : String(getSystemEndianness() == Endianness::Little ? Encoding::UTF32LE : Encoding::UTF32BE) {
	assign(value, length);
}

StringContainer::StringContainer(const std::string &value) : StringContainer(value.c_str()) {}

StringContainer::StringContainer(const std::string &value, size_t length) : StringContainer(value.c_str(), length) {}

StringContainer::StringContainer(const std::u16string &value) : StringContainer(value.c_str()) {}

StringContainer::StringContainer(const std::u16string &value, size_t length) : StringContainer(value.c_str(), length) {}

StringContainer::StringContainer(const std::u32string &value) : StringContainer(value.c_str()) {}

StringContainer::StringContainer(const std::u32string &value, size_t length) : StringContainer(value.c_str(), length) {}

StringContainer::StringContainer(const StringRef &value) : String(value.getEncoding()) {
	switch (getEncodingWidth(encoding)) {
		case 1:
			assign(value.data.asChar8, value.length);
			break;
		case 2:
			assign(value.data.asChar16, value.length);
			break;
		case 4:
			assign(value.data.asChar32, value.length);
			break;
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}
}

StringContainer::StringContainer(const StringContainer &other) {
	switch (getEncodingWidth(encoding)) {
		case 1:
			assign(other.data.asChar8, other.length);
			break;
		case 2:
			assign(other.data.asChar16, other.length);
			break;
		case 4:
			assign(other.data.asChar32, other.length);
			break;
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}
}

StringContainer::StringContainer(StringContainer &&other) {
	encoding = other.encoding;
	data.asChar8 = other.data.asChar8;
	length = other.length;
	capacity = other.capacity;

	other.data.asChar8 = nullptr;
	other.length = 0;
	other.capacity = 0;
}

StringContainer::~StringContainer() {
	delete[] data.asChar8;
}

StringContainer &StringContainer::operator=(const StringContainer &other) {
	delete[] data.asChar8;

	switch (getEncodingWidth(encoding)) {
		case 1:
			assign(other.data.asChar8, other.length);
			break;
		case 2:
			assign(other.data.asChar16, other.length);
			break;
		case 4:
			assign(other.data.asChar32, other.length);
			break;
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}

	return *this;
}

StringContainer &StringContainer::operator=(StringContainer &&other) {
	delete[] data.asChar8;

	encoding = other.encoding;
	data.asChar8 = other.data.asChar8;
	length = other.length;
	capacity = other.capacity;

	other.data.asChar8 = nullptr;
	other.length = 0;
	other.capacity = 0;

	return *this;
}

StringContainer::operator StringRef() const {
	StringRef rtn;
	rtn.encoding = encoding;
	rtn.data.asChar8 = data.asChar8;
	rtn.length = length;
	return rtn;
}

size_t StringContainer::getCapacity() const {
	return capacity;
}

void StringContainer::setCapacity(size_t value) {
	W_ASSERT_UGE(getNextPowOf2(value), length, "Cannot set capacity to less than length.");

	if (data.asChar8 != nullptr) {
		delete[] data.asChar8;
	}

	if (length == 0) {
		data.asChar8 = nullptr;
		capacity = 0;
	} else if (getNextPowOf2(value) != capacity) {
		capacity = getNextPowOf2(value);
		Char8 *tmp = new Char8[capacity * getEncodingWidth(encoding)];
		memcpy(tmp, data.asChar8, length * getEncodingWidth(encoding));
		delete[] data.asChar8;
		data.asChar8 = tmp;
	}
}

void StringContainer::setChar8At(size_t index, Char8 value) {
	W_ASSERT_EQ(getEncodingWidth(encoding), 1, "Cannot access " << getEncodingWidth(encoding) << "-byte width string as 1-byte width.");
	W_ASSERT_ULT(index, length, "Cannot access past end of string.");
	data.asChar8[index] = value;
}

void StringContainer::setChar16At(size_t index, Char16 value) {
	W_ASSERT_EQ(getEncodingWidth(encoding), 2, "Cannot access " << getEncodingWidth(encoding) << "-byte width string as 2-byte width.");
	W_ASSERT_ULT(index, length, "Cannot access past end of string.");
	data.asChar16[index] = value;
}

void StringContainer::setChar32At(size_t index, Char32 value) {
	W_ASSERT_EQ(getEncodingWidth(encoding), 4, "Cannot access " << getEncodingWidth(encoding) << "-byte width string as 4-byte width.");
	W_ASSERT_ULT(index, length, "Cannot access past end of string.");
	data.asChar32[index] = value;
}

void StringContainer::setCharAt(size_t index, Char32 value) {
	writeCharAt(index, value);
}

void StringContainer::writeCharAt(size_t &index, Char32 value) {
	switch (getEncodingWidth(encoding)) {
		case 1:
			writeCharUTF8(data.asChar8 + index, value, index, length);
			break;
		case 2:
			writeCharUTF16(data.asChar16 + index, value, index, length);
			break;
		case 4:
			writeCharUTF32(data.asChar32 + index, value, index, length);
			break;
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}
}

void StringContainer::append(Char32 value, size_t length) {
	size_t width = 0;
	Char8 buf8[4];
	Char16 buf16[2];

	switch (getEncodingWidth(encoding)) {
		case 1:
			writeCharUTF8(buf8, value, width, 4);

			setCapacity(this->length + length);

			for (size_t i = 0; i < length; i++) {
				for (size_t j = 0; j < width; j++) {
					data.asChar8[this->length++] = buf8[j];
				}
			}

			break;
		case 2:
			writeCharUTF16(buf16, value, width, 2);

			setCapacity(this->length + length);

			for (size_t i = 0; i < length; i++) {
				for (size_t j = 0; j < width; j++) {
					data.asChar16[this->length++] = buf16[j];
				}
			}

			break;
		case 4:
			for (size_t i = 0; i < length; i++) {
				data.asChar32[this->length++] = value;
			}

			break;
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}
}

void StringContainer::append(const String &value) {
	for (size_t i = 0; i < value.length;) {
		append(value.eatCharAt(i));
	}
}

void StringContainer::remove(size_t offset, size_t length) {
	W_ASSERT_ULT(offset + length, this->length, "Cannot remove past end of string.");
	memcpy(data.asChar8 + offset * getEncodingWidth(encoding), data.asChar8 + (offset + length) * getEncodingWidth(encoding), length * getEncodingWidth(encoding));
	this->length -= length;
}

void StringContainer::insert(size_t offset, Char32 value, size_t length) {
	size_t width = 0;
	Char8 buf8[4];
	Char16 buf16[2];

	switch (getEncodingWidth(encoding)) {
		case 1:
			writeCharUTF8(buf8, value, width, 4);

			setCapacity(this->length + length);

			memcpy(data.asChar8 + (offset + length) * width, data.asChar8 + offset * width, length * width);

			for (size_t i = 0; i < length; i++) {
				for (size_t j = 0; j < width; j++) {
					data.asChar8[this->length++] = buf8[j];
				}
			}

			break;
		case 2:
			writeCharUTF16(buf16, value, width, 2);

			setCapacity(this->length + length);

			memcpy(data.asChar16 + (offset + length) * width, data.asChar16 + offset * width, length * width);

			for (size_t i = 0; i < length; i++) {
				for (size_t j = 0; j < width; j++) {
					data.asChar16[this->length++] = buf16[j];
				}
			}

			break;
		case 4:
			memcpy(data.asChar32 + (offset + length) * width, data.asChar32 + offset * width, length * width);

			for (size_t i = 0; i < length; i++) {
				data.asChar32[this->length++] = value;
			}

			break;
		default:
			W_ASSERT_UNREACHABLE("Unsupported character width " << getEncodingWidth(encoding) << ".");
	}
}

void StringContainer::insert(size_t offset, const String &value) {
	if (getEncodingWidth(encoding) == getEncodingWidth(value.encoding)) {
		setCapacity(length + value.length);
		memcpy(data.asChar8 + (offset + value.length) * getEncodingWidth(encoding), data.asChar8 + offset * getEncodingWidth(encoding), value.length * getEncodingWidth(encoding));
		memcpy(data.asChar8 + offset * getEncodingWidth(encoding), value.data.asChar8, value.length * getEncodingWidth(encoding));
		length += value.length;
	} else {
		StringContainer tmp = value.convertToEncoding(encoding);
		insert(offset, tmp);
	}
}
}
