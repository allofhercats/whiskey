#include <whiskey/Source/Source.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Verbose.hpp>

namespace whiskey {
Source::Source(std::istream &is, std::string defaultPath) : is(&is), offset(0), defaultPath(defaultPath) {
	W_ASSERT_GT(defaultPath.size(), 0u, "Cannot have empty default path.");
	W_ASSERT_TRUE(is.good(), "Cannot create source from bad stream.");

	is.seekg(0, std::ios_base::end);
	W_ASSERT_FALSE(is.fail(), "Unable to seek within stream.");

	length = is.tellg();
	W_VERBOSE("create source of length " << length << " with default path '" << defaultPath << "'");

	is.seekg(0, std::ios_base::beg);
	W_ASSERT_FALSE(is.fail(), "Unable to seek within stream.");
}

const std::string &Source::getDefaultPath() const {
	return defaultPath;
}

std::istream::off_type Source::getOffset() const {
	return offset;
}

void Source::setOffset(std::istream::off_type value) {
	W_ASSERT_LT(value, length, "Cannot seek past end of stream.");

	is->seekg(value, std::ios_base::beg);
	W_ASSERT_FALSE(is->fail(), "Unable to seek within stream.");

	offset = value;
}

bool Source::more() const {
	return offset < length;
}

Char8 Source::get() const {
	if (more()) {
		int chr = is->peek();
		if (chr == EOF) {
			return 0;
		} else if (chr == '\r') {
			return '\n';
		} else {
			W_ASSERT_GE(chr, 0, "Read character is out of 1-byte range.");
			W_ASSERT_LE(chr, 0xff, "Read character is out of 1-byte range.")
			return static_cast<Char8>(chr);
		}
	} else {
		return 0;
	}
}

Char8 Source::eat() {
	if (more()) {
		int chr = is->get();
		offset++;
		if (chr == EOF) {
			return 0;
		} else if (chr == '\r') {
			if (is->good() && is->peek() == '\n') {
				is->get();
				offset++;
			}
			return '\n';
		} else {
			W_ASSERT_GE(chr, 0, "Read character is out of 1-byte range.");
			W_ASSERT_LE(chr, 0xff, "Read character is out of 1-byte range.")
			return static_cast<Char8>(chr);
		}
	} else {
		return 0;
	}
}
} // namespace whiskey
