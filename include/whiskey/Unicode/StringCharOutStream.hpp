#ifndef __WHISKEY_Unicode_StringCharOutStream_HPP
#define __WHISKEY_Unicode_StringCharOutStream_HPP

#include <whiskey/Unicode/CharOutStream.hpp>

namespace whiskey {
class StringContainer;

class StringCharOutStream : public CharOutStream {
private:
	StringContainer *value;
	
protected:
	void onWriteChar(Char32 value);

public:
	StringCharOutStream(StringContainer &value);
	
	StringContainer &getStringContainer();
	const StringContainer &getStringContainer() const;
	void setStringContainer(StringContainer &value);
};
}

#endif
