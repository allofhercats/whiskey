#include <whiskey/Source/Location.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Source/Source.hpp>

namespace whiskey {
size_t Location::distance(const Location &first, const Location &last) {
  W_ASSERT_LE(first.getOffset(),
              last.getOffset(),
              "First location must not be after last.");
  return last.getOffset() - first.getOffset();
}

Location::Location(std::string pathOverride,
                   size_t offset,
                   unsigned int line,
                   unsigned int column)
    : source(nullptr), pathOverride(pathOverride), offset(offset), line(line),
      column(column) {
}

Location::Location(const Source &source,
                   size_t offset,
                   unsigned int line,
                   unsigned int column)
    : source(&source), offset(offset), line(line), column(column) {
}

Location::Location(const Source &source,
                   std::string pathOverride,
                   size_t offset,
                   unsigned int line,
                   unsigned int column)
    : source(&source), pathOverride(pathOverride), offset(offset), line(line),
      column(column) {
}

bool Location::hasSource() const {
  return source != nullptr;
}

const Source &Location::getSource() const {
  W_ASSERT_TRUE(hasSource(), "Cannot access null source.");
  return *source;
}

void Location::setSource(const Source &value) {
  source = &value;
}

void Location::setSource() {
  source = nullptr;
}

bool Location::hasPathOverride() const {
  return !pathOverride.empty();
}

const std::string &Location::getPathOverride() const {
  return pathOverride;
}

void Location::setPathOverride(std::string value) {
  pathOverride = value;
}

bool Location::hasPath() const {
  return hasSource() || hasPathOverride();
}

const std::string &Location::getPath() const {
  if (hasPathOverride()) {
    return getPathOverride();
  } else if (!hasSource()) {
    return getPathOverride();
  } else {
    return source->getPath();
  }
}

bool Location::hasOffset() const {
  return offset != (size_t)-1;
}

size_t Location::getOffset() const {
  W_ASSERT_TRUE(hasOffset(), "Cannot access empty offset.");
  return offset;
}

void Location::setOffset(size_t value) {
  offset = value;
}

bool Location::hasLine() const {
  return line > 0;
}

unsigned int Location::getLine() const {
  W_ASSERT_TRUE(hasLine(), "Cannot access empty line.");
  return line;
}

void Location::setLine(unsigned int value) {
  line = value;
}

bool Location::hasColumn() const {
  return column > 0;
}

unsigned int Location::getColumn() const {
  W_ASSERT_TRUE(hasColumn(), "Cannot access empty column.");
  return column;
}

void Location::setColumn(unsigned int value) {
  column = value;
}

bool Location::areMoreChars(size_t lookahead) const {
  if (hasSource()) {
    if (offset + lookahead < getSource().getText().getLength()) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

char32_t Location::getChar(size_t lookahead) const {
  if (areMoreChars(lookahead)) {
    char32_t chr = source->getText().getChar(offset + lookahead);

    if (chr == '\r') {
      chr = '\n';
    }

    return chr;
  } else {
    return 0;
  }
}

char32_t Location::eatChar() {
  char32_t chr = getChar();
  offset++;

  if (chr == '\r') {
    chr = getChar();
    if (chr == '\n') {
      offset++;
    } else {
      chr = '\n';
    }
  }

  if (chr == '\n') {
    line++;
    column = 1;
  } else {
    column++;
  }

  return chr;
}
} // namespace whiskey
