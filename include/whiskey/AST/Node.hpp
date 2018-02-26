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

  bool operator==(const Node &other) const;
  bool operator!=(const Node &other) const;

  void print(std::ostream &os, int indent = 0) const;
};

std::ostream &operator<<(std::ostream &os, const Node &value);
} // namespace whiskey

#endif
