#ifndef __WHISKEY_Unicode_StringByteInStream_HPP
#define __WHISKEY_Unicode_StringByteInStream_HPP

namespace whiskey {
class StringByteInStream : public ByteInStream {
private:
	StringRef text;
	size_t offset;

protected:
	UInt32 onRead() const;
	void onSkip();

public:
	StringByteInStream(StringRef text);

	const StringRef &getText() const;
};
}

#endif
