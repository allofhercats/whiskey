#ifndef __WHISKEY_Unicode_ByteOutStream_HPP
#define __WHISKEY_Unicode_ByteOutStream_HPP

#include <whiskey/Unicode/Char.hpp>

namespace whiskey {
class ByteOutStream {
protected:
	virtual void onWriteChar8(Char8 value) = 0;

public:
	ByteOutStream();
	ByteOutStream(const ByteOutStream &) = delete;
	virtual ~ByteOutStream();

	void writeChar8(Char8 value);
};
}

#endif
