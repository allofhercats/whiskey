#include <whiskey/Unicode/IStreamByteInStream.hpp>

#include <istream>

namespace whiskey {
bool IStreamByteInStream::onMore() const {
	return is->good();
}

Char8 IStreamByteInStream::onReadChar8() const {
	return is->peek();
}

void IStreamByteInStream::onSkipChar8() {
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
