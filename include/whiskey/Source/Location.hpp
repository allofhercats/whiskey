#ifndef __WHISKEY_Source_Location_HPP
#define __WHISKEY_Source_Location_HPP

#include <string>

namespace whiskey {
class Source;

class Location {
private:
  const Source *source;
  std::string pathOverride;
  size_t offset;
  unsigned int line;
  unsigned int column;

public:
  static size_t distance(const Location &first, const Location &last);

  Location(std::string pathOverride = "",
           size_t offset = (size_t)-1,
           unsigned int line = 0,
           unsigned int column = 0);
  Location(const Source &source,
           size_t offset = 0,
           unsigned int line = 1,
           unsigned int column = 1);
  Location(const Source &source,
           std::string pathOverride,
           size_t offset = 0,
           unsigned int line = 1,
           unsigned int column = 1);

  bool hasSource() const;
  const Source &getSource() const;
  void setSource(const Source &value);
  void setSource();

  bool hasPathOverride() const;
  const std::string &getPathOverride() const;
  void setPathOverride(std::string value = "");

  bool hasPath() const;
  const std::string &getPath() const;

  bool hasOffset() const;
  size_t getOffset() const;
  void setOffset(size_t value = (size_t)-1);

  bool hasLine() const;
  unsigned int getLine() const;
  void setLine(unsigned int value = 0);

  bool hasColumn() const;
  unsigned int getColumn() const;
  void setColumn(unsigned int value = 0);

  bool areMoreChars(size_t lookahead = 0) const;
  char32_t getChar(size_t lookahead = 0) const;
  char32_t eatChar();
};
} // namespace whiskey

#endif
