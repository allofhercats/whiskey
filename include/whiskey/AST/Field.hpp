#ifndef __WHISKEY_AST_Field_HPP
#define __WHISKEY_AST_Field_HPP

#include <whiskey/Unicode/Char.hpp>
#include <whiskey/Code/Types.hpp>
#include <whiskey/Unicode/StringRef.hpp>
#include <whiskey/Unicode/StringContainer.hpp>

namespace whiskey {
class Node;

class Field {
public:
  enum class Kind { Int, UInt, Real, String, Node };

private:
  Kind kind;
  union {
    Int asInt;
    UInt asUInt;
    Real asReal;
    Node *asNode;
  } dataAtomic;
  String *asString;

  Field(Kind kind);

public:
  Field(const Field &) = delete;
  ~Field();

  static Field *createInt(Int value);
  static Field *createUInt(UInt value);
  static Field *createReal(Real value);
  static Field *createString(const String &value);
  static Field *createNode(Node *value);
  static Field *createNode(std::initializer_list<Node *> value);

  Field *clone() const;

  Kind getKind() const;

  Int getInt() const;
  void setInt(Int value);

  UInt getUInt() const;
  void setUInt(UInt value);

  Real getReal() const;
  void setReal(Real value);

  StringContainer &getString();
  const StringContainer &getString() const;
  void setString(StringContainer value);

  Node *getNode();
  const Node *getNode() const;
  void setNode(Node *value);

  bool compare(const Field *other) const;

  void printLiteral(std::ostream &os) const;
};
} // namespace whiskey

#endif
