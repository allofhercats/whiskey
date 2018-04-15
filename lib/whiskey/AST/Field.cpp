#include <whiskey/AST/Field.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/AST/FieldUInt.hpp>
#include <whiskey/AST/FieldInt.hpp>
#include <whiskey/AST/FieldReal.hpp>
#include <whiskey/AST/FieldString.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/AST/FieldScope.hpp>

namespace whiskey {
void Field::onPrintAsLiteral(std::ostream &os) const {
	W_ASSERT_UNREACHABLE("Printing as literal is not supported for field format.");
}

Field::Field(FieldFormat format) : format(format) {}

FieldFormat Field::getFormat() const {
	return format;
}

UInt64 &Field::getUInt() {
	W_ASSERT_TRUE(format == FieldFormat::UInt, "Cannot access field outside of format.");
	return as<FieldUInt>().getValue();
}

const UInt64 &Field::getUInt() const {
	W_ASSERT_TRUE(format == FieldFormat::UInt, "Cannot access field outside of format.");
	return as<FieldUInt>().getValue();
}

void Field::setUInt(UInt64 value) {
	W_ASSERT_TRUE(format == FieldFormat::UInt, "Cannot access field outside of format.");
	as<FieldUInt>().setValue(value);
}

Int64 &Field::getInt() {
	W_ASSERT_TRUE(format == FieldFormat::Int, "Cannot access field outside of format.");
	return as<FieldInt>().getValue();
}

const Int64 &Field::getInt() const {
	W_ASSERT_TRUE(format == FieldFormat::Int, "Cannot access field outside of format.");
	return as<FieldInt>().getValue();
}

void Field::setInt(Int64 value) {
	W_ASSERT_TRUE(format == FieldFormat::Int, "Cannot access field outside of format.");
	as<FieldInt>().setValue(value);
}

Real &Field::getReal() {
	W_ASSERT_TRUE(format == FieldFormat::Real, "Cannot access field outside of format.");
	return as<FieldReal>().getValue();
}

const Real &Field::getReal() const {
	W_ASSERT_TRUE(format == FieldFormat::Real, "Cannot access field outside of format.");
	return as<FieldReal>().getValue();
}

void Field::setReal(Real value) {
	W_ASSERT_TRUE(format == FieldFormat::Real, "Cannot access field outside of format.");
	as<FieldReal>().setValue(value);
}

std::string &Field::getString() {
	W_ASSERT_TRUE(format == FieldFormat::String, "Cannot access field outside of format.");
	return as<FieldString>().getValue();
}

const std::string &Field::getString() const {
	W_ASSERT_TRUE(format == FieldFormat::String, "Cannot access field outside of format.");
	return as<FieldString>().getValue();
}

void Field::setString(std::string value) {
	W_ASSERT_TRUE(format == FieldFormat::String, "Cannot access field outside of format.");
	as<FieldString>().setValue(value);
}

Node &Field::getNode() {
	W_ASSERT_TRUE(format == FieldFormat::Node, "Cannot access field outside of format.");
	return as<FieldNode>().getValue();
}

const Node &Field::getNode() const {
	W_ASSERT_TRUE(format == FieldFormat::Node, "Cannot access field outside of format.");
	return as<FieldNode>().getValue();
}

void Field::setNode(Node value) {
	W_ASSERT_TRUE(format == FieldFormat::Node, "Cannot access field outside of format.");
	as<FieldNode>().setValue(value);
}

std::vector<Node> &Field::getNodeVector() {
	W_ASSERT_TRUE(format == FieldFormat::NodeVector, "Cannot access field outside of format.");
	return as<FieldNodeVector>().getValue();
}

const std::vector<Node> &Field::getNodeVector() const {
	W_ASSERT_TRUE(format == FieldFormat::NodeVector, "Cannot access field outside of format.");
	return as<FieldNodeVector>().getValue();
}

void Field::setNodeVector(std::vector<Node> value) {
	W_ASSERT_TRUE(format == FieldFormat::NodeVector, "Cannot access field outside of format.");
	as<FieldNodeVector>().getValue() = value;
}

Scope &Field::getScope() {
	W_ASSERT_TRUE(format == FieldFormat::Scope, "Cannot access field outside of format.");
	return as<FieldScope>().getValue();
}

const Scope &Field::getScope() const {
	W_ASSERT_TRUE(format == FieldFormat::Scope, "Cannot access field outside of format.");
	return as<FieldScope>().getValue();
}

void Field::printAsLiteral(std::ostream &os) const {
	onPrintAsLiteral(os);
}

bool Field::operator==(const Field &other) const {
	if (format != other.format) {
		return false;
	}

	return onCompare(other);
}

bool Field::operator!=(const Field &other) const {
	return !(*this == other);
}

void Field::print(std::ostream &os, int indent) const {
	onPrint(os, indent);
}

std::ostream &operator<<(std::ostream &os, const Field &value) {
	value.print(os);
	return os;
}
}
