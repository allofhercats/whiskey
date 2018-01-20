#ifndef __WHISKEY_AST_Field_HPP
#define __WHISKEY_AST_Field_HPP

#include <whiskey/Core/Types.hpp>

namespace whiskey {
class Node;

class Field {
public:
  enum class Kind { Int, UInt, Real, String, Node };

private:
  Kind kind;
  union {
    Int64 asInt;
    UInt64 asUInt;
    Real asReal;
    Node *asNode;
  } dataAtomic;
  std::string asString;

  Field(Kind kind);

public:
  Field(const Field &) = delete;
  ~Field();

  static Field *createInt(Int64 value);
  static Field *createUInt(UInt64 value);
  static Field *createReal(Real value);
  static Field *createString(std::string value);
  static Field *createNode(Node *value);
  static Field *createNode(std::initializer_list<Node *> value);

  Field *clone() const;

  Kind getKind() const;

  Int64 getInt() const;
  void setInt(Int64 value);

  UInt64 getUInt() const;
  void setUInt(UInt64 value);

  Real getReal() const;
  void setReal(Real value);

  std::string &getString();
  const std::string &getString() const;
  void setString(std::string value);

  Node *getNode();
  const Node *getNode() const;
  void setNode(Node *value);

  bool compare(const Field *other) const;

  void printLiteral(std::ostream &os) const;
};
} // namespace whiskey

#endif
