#ifndef __WHISKEY_Unicode_ByteCharInStream_HPP
#define __WHISKEY_Unicode_ByteCharInStream_HPP

#include <whiskey/Unicode/Encoding.hpp>
#include <whiskey/Unicode/CharInStream.hpp>

namespace whiskey {
class ByteInStream;

class ByteCharInStream : public CharInStream {
private:
	ByteInStream *byteStream;
	Encoding encoding;
	Char32 last;
	bool lastGood;

protected:
	bool onMore() const;
	Char32 onGetChar() const;
	void onSkipChar();

public:
	ByteCharInStream(ByteInStream &byteStream, Encoding encoding);
	
	ByteInStream &getByteStream();
	const ByteInStream &getByteStream() const;
	void setByteStream(ByteInStream &value);

	Encoding getEncoding() const;
	void setEncoding(Encoding value);
};
}

#endif
