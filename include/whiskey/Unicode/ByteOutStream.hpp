#ifndef __WHISKEY_Unicode_ByteOutStream_HPP
#define __WHISKEY_Unicode_ByteOutStream_HPP

#include <whiskey/Unicode/Char.hpp>

namespace whiskey {
class ByteOutStream {
protected:
	virtual void onWrite(Char32 value) = 0;

public:
	ByteOutStream();
	ByteOutStream(const ByteOutStream &) = delete;
	virtual ~ByteOutStream();

	void writeChar8(Char8 value);
	void writeChar16(Char16 value);
	void writeChar32(Char32 value);
};
}

#endif
