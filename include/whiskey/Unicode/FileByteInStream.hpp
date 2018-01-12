#ifndef __WHISKEY_Unicode_FileByteInStream_HPP
#define __WHISKEY_Unicode_FileByteInStream_HPP

namespace whiskey {
class FileByteInStream : public ByteInStream {
private:
	std::string path;
	FILE *file;
	size_t offset;

protected:
	UInt32 onRead() const;
	void onSkip();

public:
	FileByteInStream(std::string path);
	~FileByteInStream();

	const std::string &getPath() const;
	void setPath(std::string value);

	bool isOpen() const;
	bool open();
	void close();
};
}

#endif
