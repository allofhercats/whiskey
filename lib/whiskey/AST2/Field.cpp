#include "Module.inc"

#include <whiskey/AST2/Field.hpp>

#include <whiskey/AST2/Node.hpp>

namespace whiskey {
Field::Field(Field::Kind kind) : kind(kind) {}

Field::~Field() {
	if (kind == Kind::String8) {
		delete[] dataAtomic.asString8;
	} else if (kind == Kind::String16) {
		delete[] dataAtomic.asString16;
	} else if (kind == Kind::String32) {
		delete[] dataAtomic.asString32;
	} else if (kind == Kind::Node) {
		delete dataAtomic.asNode;
	}
}

Field *Field::createInt(Int value) {
	Field *rtn = new Field(Kind::Int);
	rtn->dataAtomic.asInt = value;
	rtn->length = 0;
	return rtn;
}

Field *Field::createReal(Real value) {
	Field *rtn = new Field(Kind::Real);
	rtn->dataAtomic.asReal = value;
	rtn->length = 0;
	return rtn;
}

Field *Field::createString8(const Char8 *value, unsigned int length) {
	if (length == 0) {
		for (const Char8 *i = value; *i != 0; i++) {
			length++;
		}
	}

	Field *rtn = new Field(Kind::String8);
	rtn->dataAtomic.asString8 = new Char8[length];
	memcpy(rtn->dataAtomic.asString8, value, length);
	rtn->length = length;
	return rtn;
}

Field *Field::createString16(const Char16 *value, unsigned int length) {
	if (length == 0) {
		for (const Char16 *i = value; *i != 0; i++) {
			length++;
		}
	}

	Field *rtn = new Field(Kind::String16);
	rtn->dataAtomic.asString16 = new Char16[length];
	memcpy(rtn->dataAtomic.asString16, value, length * 2);
	rtn->length = length;
	return rtn;
}

Field *Field::createString32(const Char32 *value, unsigned int length) {
	if (length == 0) {
		for (const Char32 *i = value; *i != 0; i++) {
			length++;
		}
	}

	Field *rtn = new Field(Kind::String32);
	rtn->dataAtomic.asString32 = new Char32[length];
	memcpy(rtn->dataAtomic.asString32, value, length * 4);
	rtn->length = length;
	return rtn;
}

Field *Field::createNode(Node *value) {
	Field *rtn = new Field(Kind::Node);
	rtn->dataAtomic.asNode = value;
	rtn->length = 0;
	return rtn;
}

Field *Field::createNode(std::initializer_list<Node *> value) {
	for (std::initializer_list<Node *>::iterator i = value.begin(); i != value.end();) {
		Node *tmp = *i;
		i++;
		tmp->setNext(*i);
	}

	Field *rtn = new Field(Kind::Node);
	rtn->dataAtomic.asNode = *value.begin();
	rtn->length = 0;
	return rtn;
}

Field *Field::clone() const {
	if (kind == Kind::Int) {
		return createInt(getInt());
	} else if (kind == Kind::Real) {
		return createReal(getReal());
	} else if (kind == Kind::String8) {
		return createString8(getString8(), getLength());
	} else if (kind == Kind::String16) {
		return createString16(getString16(), getLength());
	} else if (kind == Kind::String32) {
		return createString32(getString32(), getLength());
	} else if (kind == Kind::Node) {
		if (getNode() == nullptr) {
			return createNode(nullptr);
		} else {
			return createNode(getNode()->clone());
		}
	} else {
		W_ASSERT_UNREACHABLE("Unsupported field kind.");
	}
}

Field::Kind Field::getKind() const {
	return kind;
}

Int Field::getInt() const {
	W_ASSERT_EQ(kind, Kind::Int, "Can only access int field as int.");
	return dataAtomic.asInt;
}

void Field::setInt(Int value) {
	W_ASSERT_EQ(kind, Kind::Int, "Can only access int field as int.");
	dataAtomic.asInt = value;
}

Real Field::getReal() const {
	W_ASSERT_EQ(kind, Kind::Real, "Can only access real field as real.");
	return dataAtomic.asReal;
}

void Field::setReal(Real value) {
	W_ASSERT_EQ(kind, Kind::Real, "Can only access real field as real.");
	dataAtomic.asReal = value;
}

const Char8 *Field::getString8() const {
	W_ASSERT_EQ(kind, Kind::String8, "Can only access 8-bit char width string field as 8-bit char width string.");
	return dataAtomic.asString8;
}

void Field::setString8(const Char8 *value, unsigned int length) {
	W_ASSERT_EQ(kind, Kind::String8, "Can only access 8-bit char width string field as 8-bit char width string.");

	if (length == 0) {
		for (const Char8 *i = value; *i != 0; i++) {
			length++;
		}
	}

	dataAtomic.asString8 = new Char8[length];
	memcpy(dataAtomic.asString8, value, length);
	this->length = length;
}

const Char16 *Field::getString16() const {
	W_ASSERT_EQ(kind, Kind::String16, "Can only access 16-bit char width string field as 16-bit char width string.");
	return dataAtomic.asString16;
}

void Field::setString16(const Char16 *value, unsigned int length) {
	W_ASSERT_EQ(kind, Kind::String16, "Can only access 16-bit char width string field as 16-bit char width string.");

	if (length == 0) {
		for (const Char16 *i = value; *i != 0; i++) {
			length++;
		}
	}

	dataAtomic.asString16 = new Char16[length];
	memcpy(dataAtomic.asString16, value, length * 2);
	this->length = length;
}

const Char32 *Field::getString32() const {
	W_ASSERT_EQ(kind, Kind::String32, "Can only access 32-bit char width string field as 32-bit char width string.");
	return dataAtomic.asString32;
}

void Field::setString32(const Char32 *value, unsigned int length) {
	W_ASSERT_EQ(kind, Kind::String32, "Can only access 32-bit char width string field as 32-bit char width string.");

	if (length == 0) {
		for (const Char32 *i = value; *i != 0; i++) {
			length++;
		}
	}

	dataAtomic.asString32 = new Char32[length];
	memcpy(dataAtomic.asString32, value, length * 4);
	this->length = length;
}

unsigned int Field::getLength() const {
	return length;
}

Node *Field::getNode() {
	W_ASSERT_EQ(kind, Kind::Node, "Can only access node field as node.");
	return dataAtomic.asNode;
}

const Node *Field::getNode() const {
	W_ASSERT_EQ(kind, Kind::Node, "Can only access node field as node.");
	return dataAtomic.asNode;
}

void Field::setNode(Node *value) {
	W_ASSERT_EQ(kind, Kind::Node, "Can only access node field as node.");
	dataAtomic.asNode = value;
}

bool Field::compare(const Field *other) const {
	if (kind != other->kind) {
		return false;
	}

	if (length != other->length) {
		return false;
	}

	if (kind == Kind::Int) {
		if (dataAtomic.asInt != other->dataAtomic.asInt) {
			return false;
		}
	} else if (kind == Kind::Real) {
		if (dataAtomic.asReal != other->dataAtomic.asReal) {
			return false;
		}
	} else if (kind == Kind::String8) {
		if (dataAtomic.asString8 != other->dataAtomic.asString8) {
			return memcmp(dataAtomic.asString8, other->dataAtomic.asString8, length) == 0;
		}
	} else if (kind == Kind::String16) {
		if (dataAtomic.asString16 != other->dataAtomic.asString16) {
			return memcmp(dataAtomic.asString16, other->dataAtomic.asString8, length) == 0;
		}
	} else if (kind == Kind::String32) {
		if (dataAtomic.asString32 != other->dataAtomic.asString32) {
			return memcmp(dataAtomic.asString32, other->dataAtomic.asString8, length) == 0;
		}
	} else if (kind == Kind::Node) {
		if (dataAtomic.asNode == nullptr) {
			if (other->dataAtomic.asNode != nullptr) {
				return false;
			}
		} else {
			if (other->dataAtomic.asNode == nullptr) {
				return false;
			} else if (!dataAtomic.asNode->compare(other->dataAtomic.asNode)) {
				return false;
			}
		}
	}

	return true;
}
}
