#include <whiskey/Unicode/ByteOutStream.hpp>

namespace whiskey {
ByteOutStream::ByteOutStream() {}

ByteOutStream::~ByteOutStream() {}

void ByteOutStream::writeChar(Char8 value) {
	onWriteChar(value);
}
}
