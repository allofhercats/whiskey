#ifndef __WHISKEY_AST_Field_HPP
#define __WHISKEY_AST_Field_HPP

#include <whiskey/Core/Types.hpp>
#include <whiskey/Core/Char.hpp>

namespace whiskey {
class Node;

class Field {
public:
  enum class Kind { Int, UInt, Real, String8, String16, String32, Node };

private:
  Kind kind;
  union {
    Int asInt;
    UInt asUInt;
    Real asReal;
    Char8 *asString8;
    Char16 *asString16;
    Char32 *asString32;
    Node *asNode;
  } dataAtomic;
  unsigned int length;

  Field(Kind kind);

public:
  Field(const Field &) = delete;
  ~Field();

  static Field *createInt(Int value);
  static Field *createUInt(UInt value);
  static Field *createReal(Real value);
  static Field *createString8(const Char8 *value = nullptr,
                              unsigned int length = 0);
  static Field *createString16(const Char16 *value = nullptr,
                               unsigned int length = 0);
  static Field *createString32(const Char32 *value = nullptr,
                               unsigned int length = 0);
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

  const Char8 *getString8() const;
  void setString8(const Char8 *value = nullptr, unsigned int length = 0);

  const Char16 *getString16() const;
  void setString16(const Char16 *value = nullptr, unsigned int length = 0);

  const Char32 *getString32() const;
  void setString32(const Char32 *value = nullptr, unsigned int length = 0);

  unsigned int getLength() const;

  Node *getNode();
  const Node *getNode() const;
  void setNode(Node *value);

  bool compare(const Field *other) const;

  void printLiteral(std::ostream &os) const;
};
} // namespace whiskey

#endif
