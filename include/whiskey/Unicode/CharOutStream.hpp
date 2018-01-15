#ifndef __WHISKEY_Unicode_CharOutStream_HPP
#define __WHISKEY_Unicode_CharOutStream_HPP

#include <whiskey/Unicode/Encoding.hpp>
#include <whiskey/Unicode/Char.hpp>
#include <whiskey/Unicode/StringRef.hpp>

namespace whiskey {
class CharOutStream {
private:
	virtual void onWriteChar(Char32 value) = 0;

public:
	CharOutStream();
	CharOutStream(const CharOutStream &) = delete;
	virtual ~CharOutStream();

	void write(Char32 value);
	void write(StringRef value);
};
}

#endif
