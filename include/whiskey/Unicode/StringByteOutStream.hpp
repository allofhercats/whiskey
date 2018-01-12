#ifndef __WHISKEY_Unicode_StringByteOutStream_HPP
#define __WHISKEY_Unicode_StringByteOutStream_HPP

namespace whiskey {
class StringByteOutStream : public ByteOutStream {
private:
	StringContainer text;
	size_t offset;

protected:
	void onWrite(UInt32 value);

public:
	StringByteOutStream();

	StringContainer &getText();
	const StringContainer &getText() const;
	void setText(StringContainer value);
};
}

#endif
