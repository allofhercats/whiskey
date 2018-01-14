#ifndef __WHISKEY_Unicode_CharInStream_HPP
#define __WHISKEY_Unicode_CharInStream_HPP

#include <whiskey/Unicode/Char.hpp>

namespace whiskey {
class StringContainer;

class CharInStream {
private:
	size_t offset;

protected:
	virtual bool onMore() const = 0;
	virtual Char32 onGetChar() const = 0;
	virtual void onSkipChar() = 0;

public:
	CharInStream();
	CharInStream(const CharInStream &) = delete;
	virtual ~CharInStream();

	bool more() const;
	Char32 getChar() const;
	Char32 eatChar();

	StringContainer read();

	size_t getOffset() const;
};
}

#endif
