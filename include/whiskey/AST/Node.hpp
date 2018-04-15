#ifndef __WHISKEY_AST_Node_HPP
#define __WHISKEY_AST_Node_HPP

#include <memory>
#include <vector>

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/NodeType.hpp>
#include <whiskey/Source/Token.hpp>

namespace whiskey {
class Node {
private:
  NodeType type;
  Token token;
  std::vector<std::unique_ptr<Field>> fields;

public:
  Node();
  Node(NodeType type);
  Node(Token token);
  Node(NodeType type, Token token);
  Node(const Node &other);
  Node(Node &&other);

  Node &operator=(const Node &other);
  Node &operator=(Node &&other);

  Token &getToken();
  const Token &getToken() const;
  void setToken(Token value);

  NodeType getType() const;
  void setType(NodeType value);

  std::vector<std::unique_ptr<Field>>::size_type getNFields() const;
  bool hasField(FieldTag fieldTag) const;
  bool hasField(std::vector<std::unique_ptr<Field>>::size_type index) const;
  void setField(FieldTag fieldTag, std::unique_ptr<Field> value);
  Field &getField(FieldTag fieldTag);
  Field &getField(std::vector<std::unique_ptr<Field>>::size_type index);
  const Field &getField(FieldTag fieldTag) const;
  const Field &getField(std::vector<std::unique_ptr<Field>>::size_type index) const;
  void removeField(FieldTag fieldTag);
  void removeField(std::vector<std::unique_ptr<Field>>::size_type index);

  UInt64 &getFieldUInt(FieldTag fieldTag);
  const UInt64 &getFieldUInt(FieldTag fieldTag) const;
  Node &setFieldUInt(FieldTag fieldTag, UInt64 value = 0);
  Int64 &getFieldInt(FieldTag fieldTag);
  const Int64 &getFieldInt(FieldTag fieldTag) const;
  Node &setFieldInt(FieldTag fieldTag, Int64 value = 0);
  Real &getFieldReal(FieldTag fieldTag);
  const Real &getFieldReal(FieldTag fieldTag) const;
  Node &setFieldReal(FieldTag fieldTag, Real value = 0);
  std::string &getFieldString(FieldTag fieldTag);
  const std::string &getFieldString(FieldTag fieldTag) const;
  Node &setFieldString(FieldTag fieldTag, std::string value = "");
  Node &getFieldNode(FieldTag fieldTag);
  const Node &getFieldNode(FieldTag fieldTag) const;
  Node &setFieldNode(FieldTag fieldTag, Node value = Node());
  std::vector<Node> &getFieldNodeVector(FieldTag fieldTag);
  const std::vector<Node> &getFieldNodeVector(FieldTag fieldTag) const;
  Node &setFieldNodeVector(FieldTag fieldTag, std::vector<Node> value = {});
  Scope &getFieldScope(FieldTag fieldTag);
  const Scope &getFieldScope(FieldTag fieldTag) const;
  Node &setFieldScope(FieldTag fieldTag);

  bool operator==(const Node &other) const;
  bool operator!=(const Node &other) const;

  void print(std::ostream &os, int indent = 0) const;
};

std::ostream &operator<<(std::ostream &os, const Node &value);
} // namespace whiskey

#endif
