#include <whiskey/Source/Source.hpp>

#include <string.h>

#include <whiskey/Core/Assert.hpp>

#include <whiskey/Unicode/FileByteInStream.hpp>
#include <whiskey/Unicode/ByteCharInStream.hpp>

namespace whiskey {
const std::string Source::defaultPath = "--";

Source::Source(std::string path)
    : path(path), text(nullptr) {
  W_ASSERT_GT(path.size(), 0, "Cannot have empty path.");
}

Source::~Source() {
  delete text;
}

bool Source::loadString(StringContainer value) {
  delete text;
  text = new StringContainer(value);
  return true;
}

bool Source::loadString(StringRef value) {
  delete text;
  text = new StringRef(value);
  return true;
}

bool Source::loadFile(Encoding encoding) {
  delete text;

  FileByteInStream fbis(path);
  if (!fbis.open()) {
    return false;
  }

  if (encoding == Encoding::Auto) {
    encoding = fbis.getEncoding();
  } else if (encoding != fbis.getEncoding()) {
    return false;
  }

  ByteCharInStream cis(fbis, encoding);
  text = new StringContainer(cis.read());

  fbis.close();
  return true;
}

const std::string &Source::getPath() const {
  return path;
}

void Source::setPath(std::string value) {
  W_ASSERT_GT(value.size(), 0, "Cannot have empty path.");
  path = value;
}

bool Source::isLoaded() const {
  return text != nullptr;
}

const String &Source::getText() const {
  W_ASSERT_NONNULL(text, "Cannot get unloaded text.");
  return *text;
}
} // namespace whiskey
