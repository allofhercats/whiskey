#include <whiskey/Unicode/CharInStream.hpp>

#include <whiskey/Unicode/StringContainer.hpp>

namespace whiskey {
CharInStream::CharInStream() : offset(0) {}

CharInStream::~CharInStream() {}

bool CharInStream::more() const {
	return onMore();
}

Char32 CharInStream::getChar() const {
	if (more()) {
		return onGetChar();
	} else {
		return 0;
	}
}

Char32 CharInStream::eatChar() {
	Char32 rtn = getChar();
	onSkipChar();
	offset++;
	return rtn;
}

StringContainer CharInStream::read() {
	StringContainer rtn;
	while (more()) {
		rtn.append(eatChar());
	}
	return rtn;
}

size_t CharInStream::getOffset() const {
	return offset;
}
}
