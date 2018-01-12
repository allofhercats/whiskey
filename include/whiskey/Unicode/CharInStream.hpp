#ifndef __WHISKEY_Unicode_CharInStream_HPP
#define __WHISKEY_Unicode_CharInStream_HPP

namespace whiskey {
class CharInStream {
private:
	ByteInStream *byteStream;
	Encoding encoding;

public:
	CharInStream(ByteInStream &byteStream, Encoding encoding);
	CharInStream(const CharInStream &) = delete;
	virtual ~CharInStream();

	const ByteInStream &getByteStream() const;

	Encoding getEncoding() const;
	void setEncoding(Encoding value);

	bool more() const;
	Char32 getChar() const;
	Char32 eatChar();

	size_t getOffset() const;
};
}

#endif
