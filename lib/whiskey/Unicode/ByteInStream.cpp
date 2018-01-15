#include <whiskey/Unicode/ByteInStream.hpp>

namespace whiskey {
ByteInStream::ByteInStream() {}

ByteInStream::~ByteInStream() {}

bool ByteInStream::isMore() const {
	return onIsMore();
}

Char8 ByteInStream::getChar() const {
	if (isMore()) {
		return onReadChar();
	} else {
		return 0;
	}
}

Char8 ByteInStream::eatChar() {
	Char8 rtn = getChar();
	onSkipChar();
	return rtn;
}
}
