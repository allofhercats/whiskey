#include <whiskey/Unicode/OStreamByteOutStream.hpp>

namespace whiskey {
void OStreamByteOutStream::onWriteChar(Char8 value) {
	os->put(value);
}

OStreamByteOutStream::OStreamByteOutStream(std::ostream &os) : os(&os) {}

std::ostream &OStreamByteOutStream::getOStream() {
	return *os;
}

void OStreamByteOutStream::setOStream(std::ostream &value) {
	os = &value;
}
}
