#include <whiskey/Unicode/ByteOutStream.hpp>

namespace whiskey {
ByteOutStream::ByteOutStream() {}

ByteOutStream::~ByteOutStream() {}

void ByteOutStream::writeChar8(Char8 value) {
	onWriteChar8(value);
}
}
