#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/FieldUInt.hpp>
#include <whiskey/AST/FieldInt.hpp>
#include <whiskey/AST/FieldReal.hpp>
#include <whiskey/AST/FieldString.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/AST/Node.hpp>

using namespace whiskey;

TEST(Unit_AST_Node, Token) {
  Token t0(TokenID::Symbol);
  Token t1(TokenID::Int);

  Node n0(t0);
  Node n1(t1);

  ASSERT_TRUE(n0.getToken() == t0);
  ASSERT_FALSE(n0.getToken() == t1);
  ASSERT_TRUE(n1.getToken() == t1);
  ASSERT_FALSE(n1.getToken() == t0);
}

TEST(Unit_AST_Node, Type) {
  Node n0(NodeType::TypeAtomicInt8);
  Node n1(NodeType::TypeAtomicInt16);

  ASSERT_EQ(n0.getType(), NodeType::TypeAtomicInt8);
  ASSERT_EQ(n1.getType(), NodeType::TypeAtomicInt16);
}

TEST(Unit_AST_Node, GetNFields_None) {
  Node n0(NodeType::StmtWhile);
  ASSERT_EQ(n0.getNFields(), 0);
}

TEST(Unit_AST_Node, GetNFields_OneNull) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Condition, nullptr);
  ASSERT_EQ(n0.getNFields(), 1);
}

TEST(Unit_AST_Node, GetNFields_OneSimple) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralBool)));
  ASSERT_EQ(n0.getNFields(), 1);
}

TEST(Unit_AST_Node, GetNFields_OneNoneOneNull) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Body, nullptr);
  ASSERT_EQ(n0.getNFields(), 2);
}

TEST(Unit_AST_Node, GetNFields_OneNoneOneSimple) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Body, std::make_unique<FieldNode>(Node(NodeType::StmtEmpty)));
  ASSERT_EQ(n0.getNFields(), 2);
}

TEST(Unit_AST_Node, GetNFields_TwoNull) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Condition, nullptr);
  n0.setField(FieldTag::StmtWhile_Body, nullptr);
  ASSERT_EQ(n0.getNFields(), 2);
}

TEST(Unit_AST_Node, GetNFields_OneNullOneSimple) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Condition, nullptr);
  n0.setField(FieldTag::StmtWhile_Body, std::make_unique<FieldNode>(Node(NodeType::StmtEmpty)));
  ASSERT_EQ(n0.getNFields(), 2);
}

TEST(Unit_AST_Node, GetNFields_OneSimpleOneNull) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralBool)));
  n0.setField(FieldTag::StmtWhile_Body, nullptr);
  ASSERT_EQ(n0.getNFields(), 2);
}

TEST(Unit_AST_Node, GetNFields_TwoSimple) {
  Node n0(NodeType::StmtWhile);
  n0.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralBool)));
  n0.setField(FieldTag::StmtWhile_Body, std::make_unique<FieldNode>(Node(NodeType::StmtEmpty)));
  ASSERT_EQ(n0.getNFields(), 2);
}

TEST(Unit_AST_Node, HasField_None) {
	Node n0(NodeType::StmtWhile);
	ASSERT_FALSE(n0.hasField(FieldTag::StmtWhile_Condition));
}

TEST(Unit_AST_Node, HasField_Null) {
	Node n0(NodeType::StmtWhile);
	n0.setField(FieldTag::StmtWhile_Condition, nullptr);
	ASSERT_FALSE(n0.hasField(FieldTag::StmtWhile_Condition));
}

TEST(Unit_AST_Node, HasField_Simple) {
	Node n0(NodeType::StmtWhile);
	n0.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralBool)));
	ASSERT_TRUE(n0.hasField(FieldTag::StmtWhile_Condition));
	ASSERT_FALSE(n0.hasField(FieldTag::StmtWhile_Body));
}

TEST(Unit_AST_Node, GetField) {
	Node n0(NodeType::StmtWhile);
	n0.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralBool)));
	ASSERT_EQ(n0.getField(FieldTag::StmtWhile_Condition).getFormat(), FieldFormat::Node);
}

TEST(Unit_AST_Node, SetFieldUInt) {
	Node n0(NodeType::ExprLiteralUInt64);
	n0.setFieldUInt(FieldTag::ExprLiteralUInt64_Value, 5);
	ASSERT_EQ(n0.getField(FieldTag::ExprLiteralUInt64_Value).getFormat(), FieldFormat::UInt);
	ASSERT_EQ(n0.getField(FieldTag::ExprLiteralUInt64_Value).as<FieldUInt>().getValue(), 5);
}

TEST(Unit_AST_Node, SetFieldInt) {
	Node n0(NodeType::ExprLiteralInt64);
	n0.setFieldInt(FieldTag::ExprLiteralInt64_Value, 5);
	ASSERT_EQ(n0.getField(FieldTag::ExprLiteralInt64_Value).getFormat(), FieldFormat::Int);
	ASSERT_EQ(n0.getField(FieldTag::ExprLiteralInt64_Value).as<FieldInt>().getValue(), 5);
}

TEST(Unit_AST_Node, SetFieldReal) {
	Node n0(NodeType::ExprLiteralReal);
	n0.setFieldReal(FieldTag::ExprLiteralReal_Value, 5);
	ASSERT_EQ(n0.getField(FieldTag::ExprLiteralReal_Value).getFormat(), FieldFormat::Real);
	ASSERT_EQ(n0.getField(FieldTag::ExprLiteralReal_Value).as<FieldReal>().getValue(), 5);
}

TEST(Unit_AST_Node, SetFieldString) {
	Node n0(NodeType::StmtBreak);
	n0.setFieldString(FieldTag::StmtBreak_Name, "hi");
	ASSERT_EQ(n0.getField(FieldTag::StmtBreak_Name).getFormat(), FieldFormat::String);
	ASSERT_STREQ(n0.getField(FieldTag::StmtBreak_Name).as<FieldString>().getValue().c_str(), "hi");
}

TEST(Unit_AST_Node, SetFieldNode) {
	Node n0(NodeType::ExprBoolNot);
	n0.setFieldNode(FieldTag::ExprBoolNot_Arg, Node(NodeType::ExprSymbol));
	ASSERT_EQ(n0.getField(FieldTag::ExprBoolNot_Arg).getFormat(), FieldFormat::Node);
	ASSERT_EQ(n0.getField(FieldTag::ExprBoolNot_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
}

TEST(Unit_AST_Node, SetFieldNodeVector) {
	Node n0(NodeType::ExprBoolAnd);
	n0.setFieldNodeVector(FieldTag::ExprBoolAnd_Args, {Node(NodeType::ExprLiteralBool), Node(NodeType::ExprSymbol)});
	ASSERT_EQ(n0.getField(FieldTag::ExprBoolAnd_Args).getFormat(), FieldFormat::NodeVector);
	ASSERT_EQ(n0.getField(FieldTag::ExprBoolAnd_Args).as<FieldNodeVector>().getValue().size(), 2);
	ASSERT_EQ(n0.getField(FieldTag::ExprBoolAnd_Args).as<FieldNodeVector>().getValue()[0].getType(), NodeType::ExprLiteralBool);
	ASSERT_EQ(n0.getField(FieldTag::ExprBoolAnd_Args).as<FieldNodeVector>().getValue()[1].getType(), NodeType::ExprSymbol);
}

TEST(Unit_AST_Node, Compare_Type) {
	Node n0(NodeType::ExprLiteralInt8);
	Node n1(NodeType::ExprLiteralInt16);

	ASSERT_TRUE(n0 == n0);
	ASSERT_FALSE(n0 == n1);
	ASSERT_TRUE(n1 == n1);
	ASSERT_FALSE(n1 == n0);

	ASSERT_FALSE(n0 != n0);
	ASSERT_TRUE(n0 != n1);
	ASSERT_FALSE(n1 != n1);
	ASSERT_TRUE(n1 != n0);
}

TEST(Unit_AST_Node, Compare_Field) {
	Node n0(NodeType::ExprLiteralInt8);
	n0.setFieldInt(FieldTag::ExprLiteralInt8_Value, 5);
	Node n1(NodeType::ExprLiteralInt8);
	n1.setFieldInt(FieldTag::ExprLiteralInt8_Value, 6);

	ASSERT_TRUE(n0 == n0);
	ASSERT_FALSE(n0 == n1);
	ASSERT_TRUE(n1 == n1);
	ASSERT_FALSE(n1 == n0);

	ASSERT_FALSE(n0 != n0);
	ASSERT_TRUE(n0 != n1);
	ASSERT_FALSE(n1 != n1);
	ASSERT_TRUE(n1 != n0);
}
