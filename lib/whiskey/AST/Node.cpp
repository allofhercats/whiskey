#include <whiskey/AST/Node.hpp>

#include <whiskey/AST/FieldInt.hpp>
#include <whiskey/AST/FieldUInt.hpp>
#include <whiskey/AST/FieldReal.hpp>
#include <whiskey/AST/FieldString.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/AST/FieldScope.hpp>

namespace whiskey {
Node::Node() : type(NodeType::None) {}

Node::Node(NodeType type) : type(type) {}

Node::Node(Token token) : type(NodeType::None), token(token) {}

Node::Node(NodeType type, Token token) : type(type), token(token) {}

Node::Node(const Node &other) {
	type = other.type;
	token = other.token;
	for (const std::unique_ptr<Field> &i : other.fields) {
		if (i) {
			if (i->getFormat() == FieldFormat::Int) {
				fields.push_back(static_cast<const FieldInt &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::UInt) {
				fields.push_back(static_cast<const FieldUInt &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::Real) {
				fields.push_back(static_cast<const FieldReal &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::String) {
				fields.push_back(static_cast<const FieldString &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::Node) {
				fields.push_back(static_cast<const FieldNode &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::NodeVector) {
				fields.push_back(static_cast<const FieldNodeVector &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::Scope) {
				fields.push_back(static_cast<const FieldScope &>(*i).clone());
			} else {
				W_ASSERT_UNREACHABLE("Unsupported field format " << static_cast<int>(i->getFormat()) << ".");
			}
		} else {
			fields.push_back(std::unique_ptr<Field>());
		}
	}
}

Node::Node(Node &&other) {
	type = other.type;
	token = other.token;
	fields = std::move(other.fields);
}

Node &Node::operator=(const Node &other) {
	type = other.type;
	token = other.token;
	fields.clear();
	for (const std::unique_ptr<Field> &i : other.fields) {
		if (i) {
			if (i->getFormat() == FieldFormat::Int) {
				fields.push_back(static_cast<const FieldInt &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::UInt) {
				fields.push_back(static_cast<const FieldUInt &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::Real) {
				fields.push_back(static_cast<const FieldReal &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::String) {
				fields.push_back(static_cast<const FieldString &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::Node) {
				fields.push_back(static_cast<const FieldNode &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::NodeVector) {
				fields.push_back(static_cast<const FieldNodeVector &>(*i).clone());
			} else if (i->getFormat() == FieldFormat::Scope) {
				fields.push_back(static_cast<const FieldScope &>(*i).clone());
			} else {
				W_ASSERT_UNREACHABLE("Unsupported field format " << static_cast<int>(i->getFormat()) << ".");
			}
		} else {
			fields.push_back(std::unique_ptr<Field>());
		}
	}
	return *this;
}

Node &Node::operator=(Node &&other) {
	type = other.type;
	token = other.token;
	fields = std::move(other.fields);
	return *this;
}

Token &Node::getToken() {
	return token;
}

const Token &Node::getToken() const {
	return token;
}

void Node::setToken(Token value) {
	token = value;
}

NodeType Node::getType() const {
	return type;
}

void Node::setType(NodeType value) {
	type = value;
}

std::vector<std::unique_ptr<Field>>::size_type Node::getNFields() const {
	return fields.size();
}

bool Node::hasField(FieldTag fieldTag) const {
	return hasField(FieldTagInfo::get(fieldTag).getIndex());
}

bool Node::hasField(std::vector<std::unique_ptr<Field>>::size_type index) const {
	return index < fields.size() && static_cast<bool>(fields[index]);
}

void Node::setField(FieldTag fieldTag, std::unique_ptr<Field> value) {
	while (!(FieldTagInfo::get(fieldTag).getIndex() < fields.size())) {
		fields.push_back(std::unique_ptr<Field>());
	}

	fields[FieldTagInfo::get(fieldTag).getIndex()] = std::move(value);
}

Field &Node::getField(FieldTag fieldTag) {
	return getField(FieldTagInfo::get(fieldTag).getIndex());
}

Field &Node::getField(std::vector<std::unique_ptr<Field>>::size_type index) {
	return *fields[index];
}

const Field &Node::getField(FieldTag fieldTag) const {
	return getField(FieldTagInfo::get(fieldTag).getIndex());
}

const Field &Node::getField(std::vector<std::unique_ptr<Field>>::size_type index) const {
	return *fields[index];
}

void Node::removeField(std::vector<std::unique_ptr<Field>>::size_type index) {
	fields[index].reset();
}

void Node::removeField(FieldTag fieldTag) {
	return removeField(FieldTagInfo::get(fieldTag).getIndex());
}

UInt64 &Node::getFieldUInt(FieldTag fieldTag) {
	return getField(fieldTag).getUInt();
}

const UInt64 &Node::getFieldUInt(FieldTag fieldTag) const {
	return getField(fieldTag).getUInt();
}

Node &Node::setFieldUInt(FieldTag fieldTag, UInt64 value) {
	setField(fieldTag, std::make_unique<FieldUInt>(value));
	return *this;
}

Int64 &Node::getFieldInt(FieldTag fieldTag) {
	return getField(fieldTag).getInt();
}

const Int64 &Node::getFieldInt(FieldTag fieldTag) const {
	return getField(fieldTag).getInt();
}

Node &Node::setFieldInt(FieldTag fieldTag, Int64 value) {
	setField(fieldTag, std::make_unique<FieldInt>(value));
	return *this;
}

Real &Node::getFieldReal(FieldTag fieldTag) {
	return getField(fieldTag).getReal();
}

const Real &Node::getFieldReal(FieldTag fieldTag) const {
	return getField(fieldTag).getReal();
}

Node &Node::setFieldReal(FieldTag fieldTag, Real value) {
	setField(fieldTag, std::make_unique<FieldReal>(value));
	return *this;
}

std::string &Node::getFieldString(FieldTag fieldTag) {
	return getField(fieldTag).getString();
}

const std::string &Node::getFieldString(FieldTag fieldTag) const {
	return getField(fieldTag).getString();
}

Node &Node::setFieldString(FieldTag fieldTag, std::string value) {
	setField(fieldTag, std::make_unique<FieldString>(value));
	return *this;
}

Node &Node::getFieldNode(FieldTag fieldTag) {
	return getField(fieldTag).getNode();
}

const Node &Node::getFieldNode(FieldTag fieldTag) const {
	return getField(fieldTag).getNode();
}

Node &Node::setFieldNode(FieldTag fieldTag, Node value) {
	setField(fieldTag, std::make_unique<FieldNode>(value));
	return *this;
}

std::vector<Node> &Node::getFieldNodeVector(FieldTag fieldTag) {
	return getField(fieldTag).getNodeVector();
}

const std::vector<Node> &Node::getFieldNodeVector(FieldTag fieldTag) const {
	return getField(fieldTag).getNodeVector();
}

Node &Node::setFieldNodeVector(FieldTag fieldTag, std::vector<Node> value) {
	setField(fieldTag, std::make_unique<FieldNodeVector>(value));
	return *this;
}

Scope &Node::getFieldScope(FieldTag fieldTag) {
	return getField(fieldTag).getScope();
}

const Scope &Node::getFieldScope(FieldTag fieldTag) const {
	return getField(fieldTag).getScope();
}

Node &Node::setFieldScope(FieldTag fieldTag) {
	setField(fieldTag, std::make_unique<FieldScope>());
	return *this;
}

bool Node::operator==(const Node &other) const {
	if (type != other.type) {
		return false;
	}

	std::vector<std::unique_ptr<Field>>::const_iterator ia = fields.cbegin();
	std::vector<std::unique_ptr<Field>>::const_iterator ib = other.fields.cbegin();

	while (ia != fields.cend() && ib != other.fields.cend()) {
		if (*ia) {
			if (*ib) {
				if (**ia != **ib) {
					return false;
				}
			} else {
				return false;
			}
		} else {
			if (*ib) {
				return false;
			}
		}

		++ia;
		++ib;
	}

	if ((ia == fields.cend()) != (ib == other.fields.cend())) {
		return false;
	}

	return true;
}

bool Node::operator!=(const Node &other) const {
	return !this->operator==(other);
}

void Node::print(std::ostream &os, int indent) const {
	os << type;

	std::vector<FieldTag>::size_type index = 0;
	for (const std::unique_ptr<Field> &i : fields) {
		if (i) {
			os << '\n';

			for (int j = 0; j < indent+2; j++) {
				os << ' ';
			}
		
			os << FieldTagInfo::get(NodeTypeInfo::get(type).getFields()[index]).getName() << ":";
			i->print(os, indent+2);
		}

		index++;
	}
}

std::ostream &operator<<(std::ostream &os, const Node &value) {
	value.print(os);
	return os;
}
}
