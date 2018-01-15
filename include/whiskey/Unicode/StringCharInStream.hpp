#ifndef __WHISKEY_Unicode_StringCharInStream_HPP
#define __WHISKEY_Unicode_StringCharInStream_HPP

#include <whiskey/Unicode/StringRef.hpp>
#include <whiskey/Unicode/CharInStream.hpp>

namespace whiskey {
class StringCharInStream : public CharInStream {
private:
	StringRef value;
	size_t offset;
	
protected:
	bool onIsMore() const;
	Char32 onGetChar() const;
	void onSkipChar();

public:
	StringCharInStream(StringRef value);
	
	StringRef &getStringRef();
	const StringRef &getStringRef() const;
};
}

#endif
