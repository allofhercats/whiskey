#ifndef __WHISKEY_Unicode_FileByteOutStream_HPP
#define __WHISKEY_Unicode_FileByteOutStream_HPP

#include <whiskey/Unicode/ByteOutStream.hpp>
#include <whiskey/Unicode/Encoding.hpp>

namespace whiskey {
class FileByteOutStream : public ByteOutStream {
private:
	std::string path;
	Encoding encoding;
	FILE *file;

protected:
	void onWriteChar8(Char8 value);

public:
	FileByteOutStream(std::string path, Encoding encoding = Encoding::Auto);
	~FileByteOutStream();

	const std::string &getPath() const;
	void setPath(std::string value);

	Encoding getEncoding() const;
	void setEncoding(Encoding value);

	bool isOpen() const;
	bool open();
	void close();
};
}

#endif
