#ifndef __WHISKEY_AST_Field_HPP
#define __WHISKEY_AST_Field_HPP

#include <whiskey/Core/Types.hpp>
#include <whiskey/AST/FieldTag.hpp>

namespace whiskey {
class Node;
class Scope;

class Field {
private:
  FieldFormat format;

protected:
  virtual std::unique_ptr<Field> onClone() const = 0;
  virtual void onPrintAsLiteral(std::ostream &os) const;
  virtual bool onCompare(const Field &other) const = 0;
  virtual void onPrint(std::ostream &os, int indent) const = 0;

public:
  Field(FieldFormat format);
  Field(const Field &) = delete;

  std::unique_ptr<Field> clone() const;

  template<class T>
  T &as();
  template<class T>
  const T &as() const;

  FieldFormat getFormat() const;

  UInt64 &getUInt();
  const UInt64 &getUInt() const;
  void setUInt(UInt64 value);

  Int64 &getInt();
  const Int64 &getInt() const;
  void setInt(Int64 value);

  Real &getReal();
  const Real &getReal() const;
  void setReal(Real value);

  std::string &getString();
  const std::string &getString() const;
  void setString(std::string value);

  std::unique_ptr<Node> &getNode();
  const std::unique_ptr<Node> &getNode() const;
  void setNode(std::unique_ptr<Node> value);

  std::vector<std::unique_ptr<Node>> &getNodeVector();
  const std::vector<std::unique_ptr<Node>> &getNodeVector() const;
  void setNodeVector(std::vector<std::unique_ptr<Node>> value);

  Scope &getScope();
  const Scope &getScope() const;

  void printAsLiteral(std::ostream &os) const;

  bool operator==(const Field &other) const;
  bool operator!=(const Field &other) const;

  void print(std::ostream &os, int indent = 0) const;
};

std::ostream &operator<<(std::ostream &os, const Field &value);
} // namespace whiskey

#include <whiskey/AST/Field.tpp>

#endif
