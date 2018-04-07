#include <whiskey-testing/IntegrationTestLoader.hpp>

#include <string.h>
#include <libgen.h>

#include <sstream>
#include <fstream>
#include <iostream>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/parse.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/AST/NodeType.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/FieldTag.hpp>
#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/FieldUInt.hpp>
#include <whiskey/AST/FieldInt.hpp>
#include <whiskey/AST/FieldReal.hpp>
#include <whiskey/AST/FieldString.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>

#include <whiskey-testing/PathUtils.hpp>
#include <whiskey-testing/IntegrationTest.hpp>

namespace whiskey {
namespace {
std::unique_ptr<Field> loadASTField(const YAML::Node &yaml, const std::string &key, NodeType nodeType) {
	FieldTag fieldTag;
	if (evalFieldTag(nodeType, key, fieldTag)) {
		if (yaml.IsSequence()) {
			for (YAML::const_iterator i = yaml.begin(); i != yaml.end(); ++i) {
				Node valueNode = loadASTNode(*i, key);
				if (valueNode.getType() == NodeType::None) {
					return nullptr;
				} else {
					return std::make_unique<FieldNode>(valueNode);
				}
			}
		} else if (yaml.IsMap()) {
			Node valueNode = loadASTNode(yaml, key);
			if (valueNode.getType() == NodeType::None) {
				return nullptr;
			} else {
				return std::make_unique<FieldNode>(valueNode);
			}
		} else {
			std::string text = yaml.as<std::string>();
			std::string::size_type index = text.find(":");
			if (index == std::string::npos) {
				std::cerr << path << ": error: field expected to be of form <format>:<value>\n";
				return nullptr;
			}

			FieldFormat format;
			std::string formatText = text.substr(0, index);
			if (formatText == "Int") {
				format = FieldFormat::Int;
			} else if (formatText == "UInt") {
				format = FieldFormat::UInt;
			} else if (formatText == "Real") {
				format = FieldFormat::Real;
			} else if (formatText == "String") {
				format = FieldFormat::String;
			} else {
				std::cerr << path << ": error: invalid field format '" << formatText << "'\n";
				return nullptr;
			}

			std::string valueText = text.substr(index+1);
			if (format == FieldFormat::Int) {
				Int64 valueInt64;
				if (evalLiteralInt(valueText, valueInt64)) {
					return std::make_unique<FieldInt>(valueInt64);
				} else {
					std::cerr << path << ": error: invalid integer literal '" << valueText << "'\n";
					return nullptr;
				}
			} else if (format == FieldFormat::UInt) {
				UInt64 valueUInt64;
				if (evalLiteralUInt(valueText, valueUInt64)) {
					return std::make_unique<FieldUInt>(valueUInt64);
				} else {
					std::cerr << path << ": error: invalid unsigned integer literal '" << valueText << "'\n";
					return nullptr;
				}
			} else if (format == FieldFormat::Real) {
				Real valueReal;
				if (evalLiteralReal(valueText, valueReal)) {
					return std::make_unique<FieldReal>(valueReal);
				} else {
					std::cerr << path << ": error: invalid real literal '" << valueText << "'\n";
					return nullptr;
				}
			} else if (format == FieldFormat::String) {
				std::string valueString;
				if (evalLiteralString(valueText, valueString, '\"', false)) {
					return std::make_unique<FieldString>(valueString);
				} else {
					std::cerr << path << ": error: invalid string literal '" << valueText << "'\n";
					return nullptr;
				}
			} else {
				W_ASSERT_UNREACHABLE("Unsupported field format.");
			}
		}
	} else {
		std::cerr << path << ": error: invalid field tag '" << key << "' for node type '" << nodeType << "'\n";
		return nullptr;
	}
}

Node loadASTNodeWithKey(const YAML::Node &yaml, const std::string &key) {
	NodeType nodeType;
	if (key == "None" || key == "List") {
		std::cerr << path << ": error: cannot load reserved node type '" << key << "'\n";
		return Node();
	} else if (evalNodeType(key, nodeType)) {
		if (!yaml.IsMap()) {
			std::cerr << path << ": error: expected ast node to be map\n";
			return Node();
		}

		Field loadASTField
	} else {
		std::cerr << path << ": error: invalid node type '" << key << "'\n";
		return Node();
	}
}
}

bool IntegrationTestLoader::load(const std::string &path, IntegrationTest &test) {
	YAML::Node yaml = YAML::LoadFile(path);

	// Load name
	if (yaml["name"]) {
		if (!yaml["name"].IsScalar()) {
			std::cerr << path << ": error: expected key 'name' to be scalar\n";
			return false;
		}

		test.setName(yaml["name"].as<std::string>());
	} else {
		std::string name, ext;
		pathutils::splitext(path, name, ext);
		test.setName(name);
	}

	// Load working path
	if (yaml["working_path"]) {
		if (!yaml["working_path"].IsScalar()) {
			std::cerr << path << ": error: expected key 'working_path' to be scalar\n";
			return false;
		}

		test.setWorkingPath(yaml["working_path"].as<std::string>());
	} else {
		test.setWorkingPath(pathutils::dirname(path));
	}

	// Load source path
	if (yaml["source_path"]) {
		if (!yaml["source_path"].IsScalar()) {
			std::cerr << path << ": error: expected key 'source_path' to be scalar\n";
			return false;
		}

		test.setSourcePath(pathutils::concat(test.getWorkingPath(), yaml["source_path"].as<std::string>()));
	} else {
		std::stringstream ss;
		ss << test.getName() << ".w";
		test.setSourcePath(pathutils::concat(test.getWorkingPath(), ss.str()));
	}

	// Load tokens
	if (!yaml["check_tokens"]) {
		std::cerr << path << ": error: missing key 'check_tokens'\n";
		return false;
	}

	try {
		test.setCheckTokens(yaml["check_tokens"].as<bool>());
	} catch (YAML::TypedBadConversion<bool> e) {
		std::cerr << path << ": error: expected key 'check_tokens' to be a bool\n";
		return false;
	}

	if (test.getCheckTokens()) {
		if (!yaml["expected_tokens"]) {
			std::cerr << path << ": error: missing key 'expected_tokens'\n";
			return false;
		}

		if (!yaml["expected_tokens"].IsSequence()) {
			std::cerr << path << ": error: expected key 'expected_tokens' to be sequence\n";
			return false;
		}

		for (YAML::const_iterator i = yaml["expected_tokens"].begin(); i != yaml["expected_tokens"].end(); ++i) {
			if (!i->IsMap()) {
				std::cerr << path << ": error: expected token to be map\n";
				return false;
			}

			Token token;

			if ((*i)["lineno"]) {
				try {
					token.setLineno((*i)["id"].as<Token::LinenoType>());
				} catch (YAML::TypedBadConversion<Token::LinenoType> e) {
					std::cerr << path << ": error: expected key 'lineno' to be an integer\n";
					return false;
				}
			}

			if ((*i)["columnno"]) {
				try {
					token.setColumnno((*i)["id"].as<Token::ColumnnoType>());
				} catch (YAML::TypedBadConversion<Token::ColumnnoType> e) {
					std::cerr << path << ": error: expected key 'columnno' to be an integer\n";
					return false;
				}
			}

			if ((*i)["length"]) {
				try {
					token.setLength((*i)["id"].as<Token::LengthType>());
				} catch (YAML::TypedBadConversion<Token::LengthType> e) {
					std::cerr << path << ": error: expected key 'length' to be an integer\n";
					return false;
				}
			}

			if ((*i)["id"]) {
				TokenID id;
				if (evalTokenID((*i)["id"].as<std::string>(), id)) {
					token.setID(id);
				} else {
					std::cerr << path << ": error: invalid token id '" << (*i)["id"].as<std::string>() << "'\n";
					return false;
				}
			}

			if ((*i)["text"]) {
				token.setText((*i)["text"].as<std::string>());
			}

			test.getExpectedTokens().push_back(token);
		}
	}

	return true;
}
}
