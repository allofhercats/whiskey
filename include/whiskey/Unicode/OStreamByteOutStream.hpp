#ifndef __WHISKEY_Unicode_OStreamByteOutStream_HPP
#define __WHISKEY_Unicode_OStreamByteOutStream_HPP

#include <whiskey/Unicode/ByteOutStream.hpp>

namespace whiskey {
class OStreamByteOutStream : public ByteOutStream {
private:
	std::ostream *os;
	size_t offset;

protected:
	void onWrite(Char32 value);

public:
	OStreamByteOutStream(std::ostream &os);
	~OStreamByteOutStream();

	std::ostream &getOStream();
	void setOStream(std::ostream &value);
};
}

#endif
