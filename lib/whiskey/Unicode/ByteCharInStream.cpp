#include <whiskey/Unicode/ByteCharInStream.hpp>

#include <whiskey/Unicode/ByteInStream.hpp>

namespace whiskey {
bool ByteCharInStream::onMore() const {
	return byteStream->more();
}

Char32 ByteCharInStream::onGetChar() const {
	if (lastGood) {
		return last;
	} else {
		if (encoding == Encoding::UTF8) {
			Char8 buf[4];
			buf[0] = byteStream->eatChar8();
			size_t n = getNAdditionalCharsUTF8(buf[0])+1;
			for (size_t i = 1; i < n; i++) {
				buf[i] = byteStream->eatChar8();
			}
			size_t tmp = 0;
			const_cast<ByteCharInStream *>(this)->last = readCharUTF8(buf, tmp, n);
		} else if (encoding == Encoding::UTF16LE || encoding == Encoding::UTF16BE) {
			Char8 buf[4];
			if (getSystemEndianness() != getEncodingEndianness(encoding)) {
				buf[1] = byteStream->eatChar8();
				buf[0] = byteStream->eatChar8();
			} else {
				buf[0] = byteStream->eatChar8();
				buf[1] = byteStream->eatChar8();
			}
			
			size_t n = getNAdditionalCharsUTF16(((Char16 *)buf)[0])+1;
			for (size_t i = 1; i < n; i++) {
				if (getSystemEndianness() != getEncodingEndianness(encoding)) {
					buf[3] = byteStream->eatChar8();
					buf[2] = byteStream->eatChar8();
				} else {
					buf[2] = byteStream->eatChar8();
					buf[3] = byteStream->eatChar8();
				}
			}
			size_t tmp = 0;
			const_cast<ByteCharInStream *>(this)->last = readCharUTF16((Char16 *)buf, tmp, n);
		} else if (encoding == Encoding::UTF32LE || encoding == Encoding::UTF32BE) {
			Char8 buf[4];
			if (getSystemEndianness() != getEncodingEndianness(encoding)) {
				buf[3] = byteStream->eatChar8();
				buf[2] = byteStream->eatChar8();
				buf[1] = byteStream->eatChar8();
				buf[0] = byteStream->eatChar8();
			} else {
				buf[0] = byteStream->eatChar8();
				buf[1] = byteStream->eatChar8();
				buf[2] = byteStream->eatChar8();
				buf[3] = byteStream->eatChar8();
			}
			const_cast<ByteCharInStream *>(this)->last = *((Char32 *)buf);
		} else {
			W_ASSERT_UNREACHABLE("Unsupported encoding.");
		}

		const_cast<ByteCharInStream *>(this)->lastGood = true;
		return last;
	}
}

void ByteCharInStream::onSkipChar() {
	lastGood = false;
}

ByteCharInStream::ByteCharInStream(ByteInStream &byteStream, Encoding encoding) : byteStream(&byteStream), encoding(encoding), last(0), lastGood(false) {}

ByteInStream &ByteCharInStream::getByteStream() {
	return *byteStream;
}

const ByteInStream &ByteCharInStream::getByteStream() const {
	return *byteStream;
}

void ByteCharInStream::setByteStream(ByteInStream &value) {
	byteStream = &value;
}

Encoding ByteCharInStream::getEncoding() const {
	return encoding;
}

void ByteCharInStream::setEncoding(Encoding value) {
	encoding = value;
}
}
