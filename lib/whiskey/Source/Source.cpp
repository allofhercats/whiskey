#include <whiskey/Source/Source.hpp>

#include <string.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
const std::string Source::defaultPath = "--";

Source::Source()
{}

void Source::loadString(std::string value, std::string path) {
  W_ASSERT_UGT(path.size(), 0, "Cannot have source with empty path.");
  text = value;
  this->path = path;
}

bool Source::loadFile(std::string path) {
  
}

const std::string &Source::getPath() const {
  return path;
}

void Source::setPath(std::string value) {
  W_ASSERT_GT(value.size(), 0, "Cannot have empty path.");
  path = value;
}

bool Source::isLoaded() const {
  return !path.empty();
}

const std::string &Source::getText() const {
  W_ASSERT_TRUE(isLoaded(), "Cannot get unloaded text.");
  return text;
}
} // namespace whiskey
