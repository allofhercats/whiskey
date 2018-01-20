#include <whiskey/Unicode/ByteCharOutStream.hpp>

#include <whiskey/Unicode/ByteOutStream.hpp>

#include <iostream>

namespace whiskey {
void ByteCharOutStream::onWriteChar(Char32 value) {
	std::cout << "WRITE " << std::hex << (int)value << "\n";

	if (encoding == Encoding::UTF8) {
		Char8 buf[4];
		size_t length = 0;
		writeCharUTF8(buf, value, length, 4);
		for (size_t i = 0; i < length; i++) {
			byteStream->writeChar(buf[i]);
		}
	} else if (encoding == Encoding::UTF16LE || encoding == Encoding::UTF16BE) {
		Char16 buf[2];
		size_t length = 0;
		writeCharUTF16(buf, value, length, 2, getEncodingEndianness(encoding));
		for (size_t i = 0; i < length*2; i++) {
			byteStream->writeChar(((Char8 *)buf)[i]);
		}
	} else if (encoding == Encoding::UTF32LE || encoding == Encoding::UTF32BE) {
		Char32 buf;
		size_t length = 0;
		writeCharUTF32(&buf, value, length, 1, getEncodingEndianness(encoding));
		for (size_t i = 0; i < 4; i++) {
			byteStream->writeChar(((Char8 *)&buf)[i]);
		}
	} else {
		W_ASSERT_UNREACHABLE("Unsupported encoding.");
	}
}

ByteCharOutStream::ByteCharOutStream(ByteOutStream &byteStream, Encoding encoding) : byteStream(&byteStream), encoding(encoding) {}

ByteOutStream &ByteCharOutStream::getByteStream() {
	return *byteStream;
}

const ByteOutStream &ByteCharOutStream::getByteStream() const {
	return *byteStream;
}

void ByteCharOutStream::setByteStream(ByteOutStream &value) {
	byteStream = &value;
}

Encoding ByteCharOutStream::getEncoding() const {
	return encoding;
}

void ByteCharOutStream::setEncoding(Encoding value) {
	encoding = value;
}
}
