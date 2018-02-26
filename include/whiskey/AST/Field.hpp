#ifndef __WHISKEY_AST_Field_HPP
#define __WHISKEY_AST_Field_HPP

#include <whiskey/Core/Types.hpp>
#include <whiskey/AST/FieldTag.hpp>

namespace whiskey {
class Node;

class Field {
private:
  FieldFormat format;

protected:
  virtual void onPrintAsLiteral(std::ostream &os) const;
  virtual bool onCompare(const Field &other) const = 0;
  virtual void onPrint(std::ostream &os, int indent) const = 0;

public:
  Field(FieldFormat format);

  template<class T>
  T &as();
  template<class T>
  const T &as() const;

  FieldFormat getFormat() const;

  void printAsLiteral(std::ostream &os) const;

  bool operator==(const Field &other) const;
  bool operator!=(const Field &other) const;

  void print(std::ostream &os, int indent = 0) const;
};

std::ostream &operator<<(std::ostream &os, const Field &value);
} // namespace whiskey

#include <whiskey/AST/Field.tpp>

#endif
