#ifndef __WHISKEY_Unicode_IStreamByteInStream_HPP
#define __WHISKEY_Unicode_IStreamByteInStream_HPP

#include <whiskey/Unicode/ByteInStream.hpp>

namespace whiskey {
class IStreamByteInStream : public ByteInStream {
private:
	std::istream *is;

protected:
	bool onIsMore() const;
	Char8 onReadChar() const;
	void onSkipChar();

public:
	IStreamByteInStream(std::istream &is);

	std::istream &getIStream();
	void setIStream(std::istream &value);
};
}

#endif
