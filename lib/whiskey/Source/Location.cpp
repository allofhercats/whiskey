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
                   unsigned int line,
                   unsigned int column)
    : source(nullptr), pathOverride(pathOverride), line(line),
      column(column) {
}

Location::Location(const Source &source,
           unsigned int line,
           unsigned int column)
    : source(&source), iter(source.getText().cbegin()), line(line), column(column) {
}

Location::Location(const Source &source,
                   std::string pathOverride,
                   unsigned int line,
                   unsigned int column)
    : source(&source), pathOverride(pathOverride), iter(source.getText().cbegin()), line(line),
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
  return hasSource();
}

size_t Location::getOffset() const {
  W_ASSERT_TRUE(hasOffset(), "Cannot access empty offset.");
  return std::distance(source->getText().cbegin(), iter);
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
    if ((lookahead == 0 && iter != source->getText().cend()) || (lookahead != 0 && getOffset() + lookahead < getSource().getText().size())) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

char Location::getChar(size_t lookahead) const {
  if (areMoreChars(lookahead)) {
    char32_t chr;
    if (lookahead == 0) {
      chr = *iter;
    } else {
      chr = source->getText()[getOffset() + lookahead];
    }

    if (chr == '\r') {
      chr = '\n';
    }

    return chr;
  } else {
    return 0;
  }
}

char Location::eatChar() {
  char32_t chr = getChar();
  iter++;

  if (chr == '\r') {
    chr = getChar();
    if (chr == '\n') {
      iter++;
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
