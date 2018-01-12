#ifndef __WHISKEY_Unicode_FileByteOutStream_HPP
#define __WHISKEY_Unicode_FileByteOutStream_HPP

namespace whiskey {
class FileByteOutStream : public ByteOutStream {
private:
	std::string path;
	FILE *file;
	size_t offset;

protected:
	void onWrite(UInt32 value);

public:
	FileByteOutStream(std::string path);
	~FileByteOutStream();

	const std::string &getPath() const;
	void setPath(std::string value);

	bool isOpen() const;
	bool open();
	void close();
};
}

#endif
