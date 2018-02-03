#include <whiskey/AST/Field.hpp>

#include <string.h>

#include <whiskey/AST/Node.hpp>
#include <whiskey/Core/LiteralPrinterBool.hpp>
#include <whiskey/Core/LiteralPrinterChar.hpp>
#include <whiskey/Core/LiteralPrinterReal.hpp>
#include <whiskey/Core/LiteralPrinterString.hpp>
#include <whiskey/Core/LiteralPrinterUInt.hpp>

namespace whiskey {
Field::Field(Field::Kind kind) : kind(kind) {
}

Field::~Field() {
}

Field *Field::createInt(Int64 value) {
  Field *rtn = new Field(Kind::Int);
  rtn->dataAtomic.asInt = value;
  return rtn;
}

Field *Field::createUInt(UInt64 value) {
  Field *rtn = new Field(Kind::UInt);
  rtn->dataAtomic.asUInt = value;
  return rtn;
}

Field *Field::createReal(Real value) {
  Field *rtn = new Field(Kind::Real);
  rtn->dataAtomic.asReal = value;
  return rtn;
}

Field *Field::createString(std::string value) {
  Field *rtn = new Field(Kind::String);
  rtn->asString = value;
  return rtn;
}

Field *Field::createNode(Node *value) {
  Field *rtn = new Field(Kind::Node);
  if (value != nullptr) {
    value->setNext(nullptr);
  }
  rtn->dataAtomic.asNode = value;
  return rtn;
}

Field *Field::createNode(std::initializer_list<Node *> value) {
  Node *first = nullptr;
  Node *last = nullptr;
  for (std::initializer_list<Node *>::iterator i = value.begin();
       i != value.end();) {
    Node *tmp = *i;
    if (tmp == nullptr) {
      break;
    }
    if (first == nullptr) {
      first = tmp;
    }
    if (last != nullptr) {
      last->setNext(tmp);
    }
    last = tmp;
    i++;
  }

  Field *rtn = new Field(Kind::Node);
  rtn->dataAtomic.asNode = first;
  return rtn;
}

Field *Field::clone() const {
  if (kind == Kind::Int) {
    return createInt(getInt());
  } else if (kind == Kind::UInt) {
    return createInt(getUInt());
  } else if (kind == Kind::Real) {
    return createReal(getReal());
  } else if (kind == Kind::String) {
    return createString(getString());
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

Int64 Field::getInt() const {
  W_ASSERT_EQ(kind, Kind::Int, "Can only access int field as int.");
  return dataAtomic.asInt;
}

void Field::setInt(Int64 value) {
  W_ASSERT_EQ(kind, Kind::Int, "Can only access int field as int.");
  dataAtomic.asInt = value;
}

UInt64 Field::getUInt() const {
  W_ASSERT_EQ(
      kind, Kind::UInt, "Can only access unsigned int field as unsigned int.");
  return dataAtomic.asInt;
}

void Field::setUInt(UInt64 value) {
  W_ASSERT_EQ(
      kind, Kind::UInt, "Can only access unsigned int field as unsigned int.");
  dataAtomic.asUInt = value;
}

Real Field::getReal() const {
  W_ASSERT_EQ(kind, Kind::Real, "Can only access real field as real.");
  return dataAtomic.asReal;
}

void Field::setReal(Real value) {
  W_ASSERT_EQ(kind, Kind::Real, "Can only access real field as real.");
  dataAtomic.asReal = value;
}

std::string &Field::getString() {
  W_ASSERT_EQ(kind, Kind::String, "Can only access string field as string.");
  return asString;
}

const std::string &Field::getString() const {
  W_ASSERT_EQ(kind, Kind::String, "Can only access string field as string.");
  return asString;
}

void Field::setString(std::string value) {
  W_ASSERT_EQ(kind, Kind::String, "Can only access string field as string.");
  asString = value;
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

  if (kind == Kind::Int) {
    if (dataAtomic.asInt != other->dataAtomic.asInt) {
      return false;
    }
  } else if (kind == Kind::UInt) {
    if (dataAtomic.asUInt != other->dataAtomic.asUInt) {
      return false;
    }
  } else if (kind == Kind::Real) {
    if (dataAtomic.asReal != other->dataAtomic.asReal) {
      return false;
    }
  } else if (kind == Kind::String) {
    if (asString != other->asString) {
      return false;
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

void Field::printLiteral(std::ostream &os) const {
  if (kind == Field::Kind::Int) {
    if (dataAtomic.asInt < 0) {
      os << "-";
      LiteralPrinterUInt(-dataAtomic.asInt).print(os);
    } else {
      LiteralPrinterUInt(dataAtomic.asInt).print(os);
    }
  } else if (kind == Field::Kind::UInt) {
    LiteralPrinterUInt(dataAtomic.asUInt).print(os);
  } else if (kind == Field::Kind::Real) {
    LiteralPrinterReal(dataAtomic.asReal).print(os);
  } else if (kind == Field::Kind::String) {
    LiteralPrinterString(asString).print(os);
  } else {
    W_ASSERT_UNREACHABLE("Cannot print field as literal.");
  }
}
} // namespace whiskey
