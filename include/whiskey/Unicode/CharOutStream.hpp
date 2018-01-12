#ifndef __WHISKEY_Unicode_CharOutStream_HPP
#define __WHISKEY_Unicode_CharOutStream_HPP

namespace whiskey {
class CharOutStream {
private:
	ByteOutStream *byteStream;
	Encoding encoding;

public:
	CharOutStream(ByteOutStream &byteStream, Encoding encoding);
	CharOutStream(const CharOutStream &) = delete;
	virtual ~CharOutStream();

	const ByteOutStream &getByteStream() const;

	Encoding getEncoding() const;
	void setEncoding(Encoding value);

	void write(Char32 value);
};
}

#endif
