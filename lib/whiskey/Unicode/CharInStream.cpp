#include <whiskey/Unicode/CharInStream.hpp>

#include <whiskey/Unicode/StringContainer.hpp>

namespace whiskey {
CharInStream::CharInStream() {}

CharInStream::~CharInStream() {}

bool CharInStream::isMore() const {
	return onIsMore();
}

Char32 CharInStream::getChar() const {
	if (isMore()) {
		return onGetChar();
	} else {
		return 0;
	}
}

Char32 CharInStream::eatChar() {
	Char32 rtn = getChar();
	onSkipChar();
	return rtn;
}

StringContainer CharInStream::read() {
	StringContainer rtn;
	while (isMore()) {
		rtn.append(eatChar());
	}
	return rtn;
}
}
