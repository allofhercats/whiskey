#include <whiskey/Unicode/StringCharOutStream.hpp>

#include <whiskey/Unicode/StringContainer.hpp>

namespace whiskey {
void StringCharOutStream::onWriteChar(Char32 value) {
	this->value->append(value);
}

StringCharOutStream::StringCharOutStream(StringContainer &value) : value(&value) {}

StringContainer &StringCharOutStream::getStringContainer() {
	return *value;
}

const StringContainer &StringCharOutStream::getStringContainer() const {
	return *value;
}

void StringCharOutStream::setStringContainer(StringContainer &value) {
	this->value = &value;
}
}
