#include <whiskey/Unicode/StringCharInStream.hpp>

namespace whiskey {
bool StringCharInStream::onMore() const {
	return getOffset() < value.getLength();
}

Char32 StringCharInStream::onGetChar() const {
	return value.getCharAt(getOffset());
}

void StringCharInStream::onSkipChar() {
}

StringCharInStream::StringCharInStream(StringRef value) : value(value) {}

StringRef &StringCharInStream::getStringRef() {
	return value;
}

const StringRef &StringCharInStream::getStringRef() const {
	return value;
}
}
