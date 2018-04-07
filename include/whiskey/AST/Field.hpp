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

  UInt64 getUInt() const;
  void setUInt(UInt64 value);

  Int64 getInt() const;
  void setInt(Int64 value);

  Real getReal() const;
  void setReal(Real value);

  std::string &getString();
  const std::string &getString() const;
  void setString(std::string value);

  Node &getNode();
  const Node &getNode() const;
  void setNode(Node value);

  std::vector<Node> &getNodeVector();
  const std::vector<Node> &getNodeVector() const;
  void setNodeVector(std::vector<Node> value);

  void printAsLiteral(std::ostream &os) const;

  bool operator==(const Field &other) const;
  bool operator!=(const Field &other) const;

  void print(std::ostream &os, int indent = 0) const;
};

std::ostream &operator<<(std::ostream &os, const Field &value);
} // namespace whiskey

#include <whiskey/AST/Field.tpp>

#endif
