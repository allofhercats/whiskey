#include <whiskey/Unicode/ByteInStream.hpp>

namespace whiskey {
ByteInStream::ByteInStream() : offset(0) {}

ByteInStream::~ByteInStream() {}

bool ByteInStream::more() const {
	return onMore();
}

Char8 ByteInStream::getChar8() const {
	if (more()) {
		return onReadChar8();
	} else {
		return 0;
	}
}

Char8 ByteInStream::eatChar8() {
	Char8 rtn = getChar8();
	onSkipChar8();
	offset++;
	return rtn;
}

size_t ByteInStream::getOffset() const {
	return offset;
}
}
