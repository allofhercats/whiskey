#include <whiskey/Unicode/FileByteOutStream.hpp>

namespace whiskey {
void FileByteOutStream::onWriteChar(Char8 value) {
	W_ASSERT_NONNULL(file, "Cannot write to null file handle.");
	fputc(value, file);
}

FileByteOutStream::FileByteOutStream(std::string path, Encoding encoding) : path(path), encoding(encoding), file(nullptr) {
	W_ASSERT_UGT(path.size(), 0, "Cannot create file stream with empty path.");
}

FileByteOutStream::~FileByteOutStream() {
	W_ASSERT_FALSE(isOpen(), "Cannot destroy file stream while file is still open.");
}

const std::string &FileByteOutStream::getPath() const {
	return path;
}

void FileByteOutStream::setPath(std::string value) {
	W_ASSERT_UGT(path.size(), 0, "Cannot create file stream with empty path.");
	path = value;
}

Encoding FileByteOutStream::getEncoding() const {
	return encoding;
}

void FileByteOutStream::setEncoding(Encoding value) {
	encoding = value;
}

bool FileByteOutStream::isOpen() const {
	return file != nullptr;
}

bool FileByteOutStream::open() {
	W_ASSERT_FALSE(isOpen(), "File stream is already open.");

	file = fopen(path.c_str(), "w");
	if (file == nullptr) {
		return false;
	}

	switch (encoding) {
		case Encoding::UTF8:
			fputs("\xef\xbb\xbf", file);
			break;
		case Encoding::UTF16LE:
			fputs("\xfe\xff", file);
			break;
		case Encoding::UTF16BE:
			fputs("\xff\xfe", file);
			break;
		case Encoding::UTF32LE:
			fputs("\xff\xfe\x00\x00", file);
			break;
		case Encoding::UTF32BE:
			fputs("\x00\x00\xfe\xff", file);
			break;
		default:
			break;
	}

	return true;
}

void FileByteOutStream::close() {
	W_ASSERT_TRUE(isOpen(), "File stream is not open.");

	fclose(file);
	file = nullptr;
}
}
