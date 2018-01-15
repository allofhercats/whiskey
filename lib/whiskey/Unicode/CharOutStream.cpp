#include <whiskey/Unicode/CharOutStream.hpp>

namespace whiskey {
CharOutStream::CharOutStream() {}

CharOutStream::~CharOutStream() {}

void CharOutStream::write(Char32 value) {
	onWriteChar(value);
}

void CharOutStream::write(StringRef value) {
	for (size_t i = 0; i < value.getLength();) {
		write(value.eatCharAt(i));
	}
}
}
