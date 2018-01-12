#ifndef __WHISKEY_Unicode_ByteInStream_HPP
#define __WHISKEY_Unicode_ByteInStream_HPP

namespace whiskey {
class ByteInStream {
protected:
	virtual UInt32 onRead() const = 0;
	virtual void onSkip() = 0;

public:
	ByteInStream();
	ByteInStream(const ByteInStream &) = delete;
	virtual ~ByteInStream();

	bool more() const;
	UInt8 getUInt8() const;
	UInt16 getUInt16() const;
	UInt32 getUInt32() const;
	UInt8 eatUInt8();
	UInt16 eatUInt16();
	UInt32 eatUInt32();

	size_t getOffset() const;
};
}

#endif
