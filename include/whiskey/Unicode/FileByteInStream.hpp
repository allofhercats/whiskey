#ifndef __WHISKEY_Unicode_FileByteInStream_HPP
#define __WHISKEY_Unicode_FileByteInStream_HPP

#include <whiskey/Unicode/ByteInStream.hpp>

namespace whiskey {
class FileByteInStream : public ByteInStream {
private:
	std::string path;
	FILE *file;
	size_t offset;
	size_t length;
	Encoding encoding;

protected:
	Char32 onRead() const;
	void onSkip();

public:
	FileByteInStream(std::string path);
	~FileByteInStream();

	const std::string &getPath() const;
	void setPath(std::string value);

	bool isOpen() const;
	bool open();
	void close();

	size_t getLength() const;
	Encoding getEncoding() const;
};
}

#endif
