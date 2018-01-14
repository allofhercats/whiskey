#ifndef __WHISKEY_Unicode_OStreamByteOutStream_HPP
#define __WHISKEY_Unicode_OStreamByteOutStream_HPP

#include <whiskey/Unicode/ByteOutStream.hpp>

namespace whiskey {
class OStreamByteOutStream : public ByteOutStream {
private:
	std::ostream *os;

protected:
	void onWriteChar8(Char8 value);

public:
	OStreamByteOutStream(std::ostream &os);

	std::ostream &getOStream();
	void setOStream(std::ostream &value);
};
}

#endif
