#ifndef __WHISKEY_Unicode_ByteInStream_HPP
#define __WHISKEY_Unicode_ByteInStream_HPP

#include <whiskey/Unicode/Char.hpp>

namespace whiskey {
class ByteInStream {
protected:
	virtual bool onIsMore() const = 0;
	virtual Char8 onReadChar() const = 0;
	virtual void onSkipChar() = 0;

public:
	ByteInStream();
	ByteInStream(const ByteInStream &) = delete;
	virtual ~ByteInStream();

	bool isMore() const;
	Char8 getChar() const;
	Char8 eatChar();
};
}

#endif
