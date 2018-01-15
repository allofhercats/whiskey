#include <whiskey/Unicode/StringCharInStream.hpp>

namespace whiskey {
bool StringCharInStream::onIsMore() const {
	return offset < value.getLength();
}

Char32 StringCharInStream::onGetChar() const {
	return value.getCharAt(offset);
}

void StringCharInStream::onSkipChar() {
	value.eatCharAt(offset);
}

StringCharInStream::StringCharInStream(StringRef value) : value(value) {}

StringRef &StringCharInStream::getStringRef() {
	return value;
}

const StringRef &StringCharInStream::getStringRef() const {
	return value;
}
}
