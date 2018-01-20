#include <whiskey/Unicode/FileByteInStream.hpp>

#include <string.h>

#include <iostream>

namespace whiskey {
bool FileByteInStream::onIsMore() const {
	W_ASSERT_TRUE(isOpen(), "Cannot check if more characters in unopened file stream.");
	return (!feof(file)) && offset < length;
}

Char8 FileByteInStream::onReadChar() const {
	W_ASSERT_TRUE(isOpen(), "Cannot read characters in unopened file stream.");

	if (lastGood) {
		return last;
	} else if (feof(file)) {
		return 0;
	} else {
		const_cast<FileByteInStream *>(this)->last = fgetc(file);
		const_cast<FileByteInStream *>(this)->lastGood = true;
		return last;
	}
}

void FileByteInStream::onSkipChar() {
	W_ASSERT_TRUE(isOpen(), "Cannot skip characters in unopened file stream.");

	offset++;
	lastGood = false;
}

FileByteInStream::FileByteInStream(std::string path) : path(path), file(nullptr), offset(0), length(0), encoding(Encoding::Auto), last(0), lastGood(false) {
	W_ASSERT_UGT(path.size(), 0, "Cannot create file stream with empty path.");
}

FileByteInStream::~FileByteInStream() {
	W_ASSERT_FALSE(isOpen(), "Cannot destroy file stream while still open.");
}

const std::string &FileByteInStream::getPath() const {
	return path;
}

void FileByteInStream::setPath(std::string value) {
	W_ASSERT_UGT(value.size(), 0, "Cannot have file stream with empty path.");
	path = value;
}

bool FileByteInStream::isOpen() const {
	return file != nullptr;
}

bool FileByteInStream::open() {
	W_ASSERT_FALSE(isOpen(), "File stream is already open.");

	file = fopen(path.c_str(), "r");
	if (file == nullptr) {
		return false;
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	Char8 bom[4];
	fread(bom, 1, 4, file);

	if (length >= 3 && memcmp(bom, "\xef\xbb\xbf", 3) == 0) {
		fseek(file, 3, SEEK_SET);
		length -= 3;
		encoding = Encoding::UTF8;
	} else if (length >= 4 && memcmp(bom, "\xff\xfe\x00\x00", 4) == 0) {
		fseek(file, 4, SEEK_SET);
		length -= 4;
		encoding = Encoding::UTF32LE;
	} else if (length >= 4 && memcmp(bom, "\x00\x00\xfe\xff", 4) == 0) {
		fseek(file, 4, SEEK_SET);
		length -= 4;
		encoding = Encoding::UTF32BE;
	} else if (length >= 2 && memcmp(bom, "\xfe\xff", 2) == 0) {
		fseek(file, 2, SEEK_SET);
		length -= 2;
		encoding = Encoding::UTF16LE;
	} else if (length >= 2 && memcmp(bom, "\xff\xfe", 2) == 0) {
		fseek(file, 2, SEEK_SET);
		length -= 2;
		encoding = Encoding::UTF16BE;
	} else {
		fseek(file, 0, SEEK_SET);
		encoding = Encoding::Auto;
	}

	last = 0;
	lastGood = false;

	return true;
}

void FileByteInStream::close() {
	W_ASSERT_TRUE(isOpen(), "File stream is not open.");

	fclose(file);
	file = nullptr;
}

size_t FileByteInStream::getLength() const {
	W_ASSERT_TRUE(isOpen(), "Cannot get length of unopened file stream.");

	return length;
}

Encoding FileByteInStream::getEncoding() const {
	W_ASSERT_TRUE(isOpen(), "Cannot get encoding of unopened file stream.");

	return encoding;
}
}
