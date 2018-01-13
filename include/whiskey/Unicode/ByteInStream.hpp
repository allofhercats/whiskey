#ifndef __WHISKEY_Unicode_ByteInStream_HPP
#define __WHISKEY_Unicode_ByteInStream_HPP

#include <whiskey/Unicode/Char.hpp>

namespace whiskey {
class ByteInStream {
protected:
	virtual Char32 onRead() const = 0;
	virtual void onSkip() = 0;

public:
	ByteInStream();
	ByteInStream(const ByteInStream &) = delete;
	virtual ~ByteInStream();

	bool more() const;
	Char8 getChar8() const;
	Char16 getChar16() const;
	Char32 getChar32() const;
	Char8 eatChar8();
	Char16 eatChar16();
	Char32 eatChar32();

	size_t getOffset() const;
};
}

#endif
