#ifndef __WHISKEY_Unicode_OStreamByteOutStream_HPP
#define __WHISKEY_Unicode_OStreamByteOutStream_HPP

namespace whiskey {
class OStreamByteOutStream : public ByteOutStream {
private:
	std::ostream &os;
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
