#ifndef __WHISKEY_Unicode_ByteCharOutStream_HPP
#define __WHISKEY_Unicode_ByteCharOutStream_HPP

#include <whiskey/Unicode/Encoding.hpp>
#include <whiskey/Unicode/CharOutStream.hpp>

namespace whiskey {
class ByteOutStream;

class ByteCharOutStream : public CharOutStream {
private:
	ByteOutStream *byteStream;
	Encoding encoding;

protected:
	void onWriteChar(Char32 value);

public:
	ByteCharOutStream(ByteOutStream &byteStream, Encoding encoding);
	
	ByteOutStream &getByteStream();
	const ByteOutStream &getByteStream() const;
	void setByteStream(ByteOutStream &value);

	Encoding getEncoding() const;
	void setEncoding(Encoding value);
};
}

#endif
