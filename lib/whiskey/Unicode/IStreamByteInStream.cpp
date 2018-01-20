#include <whiskey/Unicode/IStreamByteInStream.hpp>

#include <istream>

namespace whiskey {
bool IStreamByteInStream::onIsMore() const {
	return is->rdbuf()->in_avail() > 0;
}

Char8 IStreamByteInStream::onReadChar() const {
	return is->peek();
}

void IStreamByteInStream::onSkipChar() {
	is->get();
}

IStreamByteInStream::IStreamByteInStream(std::istream &is) : is(&is) {}

std::istream &IStreamByteInStream::getIStream() {
	return *is;
}

void IStreamByteInStream::setIStream(std::istream &value) {
	is = &value;
}
}
