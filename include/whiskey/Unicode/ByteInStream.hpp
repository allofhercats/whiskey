#ifndef __WHISKEY_Unicode_ByteInStream_HPP
#define __WHISKEY_Unicode_ByteInStream_HPP

#include <whiskey/Unicode/Char.hpp>

namespace whiskey {
class ByteInStream {
private:
	size_t offset;

protected:
	virtual bool onMore() const = 0;
	virtual Char8 onReadChar8() const = 0;
	virtual void onSkipChar8() = 0;

public:
	ByteInStream();
	ByteInStream(const ByteInStream &) = delete;
	virtual ~ByteInStream();

	bool more() const;
	Char8 getChar8() const;
	Char8 eatChar8();
	
	size_t getOffset() const;
};
}

#endif
