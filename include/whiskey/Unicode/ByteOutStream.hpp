#ifndef __WHISKEY_Unicode_ByteOutStream_HPP
#define __WHISKEY_Unicode_ByteOutStream_HPP

namespace whiskey {
class ByteOutStream {
protected:
	virtual void onWrite(UInt32 value) = 0;

public:
	ByteOutStream();
	ByteOutStream(const ByteOutStream &) = delete;
	virtual ~ByteOutStream();

	void writeUInt8(UInt8 value);
	void writeUInt16(UInt16 value);
	void writeUInt32(UInt32 value);
};
}

#endif
