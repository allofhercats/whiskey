#ifndef __WHISKEY_AST_Require_HPP
#define __WHISKEY_AST_Require_HPP

#include <whiskey/AST/FieldTag.hpp>
#include <whiskey/AST/NodeType.hpp>

namespace whiskey {
class Node;
class MessageContext;

bool requireFieldWithFormat(const Node &node, MessageContext &msgs, FieldTag fieldTag, std::initializer_list<FieldFormat> formats, bool optional = false);
bool requireNodeFieldWithCategory(const Node &node, MessageContext &msgs, FieldTag fieldTag, std::initializer_list<NodeTypeCategory> categories, bool optional = false);
bool requireNodeVectorFieldWithCategory(const Node &node, MessageContext &msgs, FieldTag fieldTag, std::initializer_list<NodeTypeCategory> categories);
}

#endif
