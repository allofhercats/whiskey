#include <whiskey/AST/Requires.hpp>

#include <algorithm>

#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/AST/Node.hpp>

namespace whiskey {
bool requireFieldWithFormat(const Node &node, MessageContext &msgs, FieldTag fieldTag, std::initializer_list<FieldFormat> formats, bool optional) {
	bool ok = true;

	if (optional || (!node.hasField(fieldTag))) {
		msgs.describe() << "node of type '" << node.getType() << "' is missing field '" << fieldTag << "'";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		
		ok = false;
	} else if (std::find(formats.begin(), formats.end(), node.getField(fieldTag).getFormat()) == formats.end()) {
		for (FieldFormat i : formats) {
			msgs.describe() << "expected " << i;
			msgs.emitChild(node.getToken(), Message::Severity::Note);
		}

		msgs.describe() << "node of type '" << node.getType() << "' has field '" << fieldTag << "' of unexpected format";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		
		ok = false;
	}

	return ok;
}

bool requireNodeFieldWithCategory(const Node &node, MessageContext &msgs, FieldTag fieldTag, std::initializer_list<NodeTypeCategory> categories, bool optional) {
	bool ok = true;

	if (optional || !node.hasField(fieldTag)) {
		msgs.describe() << "node of type '" << node.getType() << "' is missing field '" << fieldTag << "'";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);
		
		ok = false;
	} else if (node.getField(fieldTag).getFormat() != FieldFormat::Node) {
		msgs.describe() << "expected " << FieldFormat::Node;
		msgs.emitChild(node.getToken(), Message::Severity::Note);

		msgs.describe() << "node of type '" << node.getType() << "' has field '" << fieldTag << "' of unexpected format";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);

		ok = false;
	} else if ((optional && node.getField(fieldTag).getNode().getType() == NodeType::None) || std::find(categories.begin(), categories.end(), NodeTypeInfo::get(node.getField(fieldTag).getNode().getType()).getCategory()) == categories.end()) {
		for (NodeTypeCategory i : categories) {
			msgs.describe() << "expected " << i;
			msgs.emitChild(node.getToken(), Message::Severity::Note);
		}

		msgs.describe() << "node of type '" << node.getType() << "' has node field '" << fieldTag << "' with unexpected category";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);

		ok = false;
	}

	return ok;
}

bool requireNodeVectorFieldWithCategory(const Node &node, MessageContext &msgs, FieldTag fieldTag, std::initializer_list<NodeTypeCategory> categories) {
	bool ok = true;

	if (!node.hasField(fieldTag)) {
		msgs.describe() << "node of type '" << node.getType() << "' is missing field '" << fieldTag << "'";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);

		ok = false;
	} else if (node.getField(fieldTag).getFormat() != FieldFormat::NodeVector) {
		msgs.describe() << "expected " << FieldFormat::NodeVector;
		msgs.emitChild(node.getToken(), Message::Severity::Note);

		msgs.describe() << "node of type '" << node.getType() << "' has field '" << fieldTag << "' of unexpected format";
		msgs.emit(node.getToken(), Message::Severity::InternalCompilerError);

		ok = false;
	} else {
		for (const Node &i : node.getField(fieldTag).getNodeVector()) {
			if (std::find(categories.begin(), categories.end(), NodeTypeInfo::get(i.getType()).getCategory()) == categories.end()) {
				for (NodeTypeCategory j : categories) {
					msgs.describe() << "expected " << j;
					msgs.emitChild(node.getToken(), Message::Severity::Note);
				}

				msgs.describe() << "node of type '" << node.getType() << "' has node vector field '" << fieldTag << "' with element of unexpected category";
				msgs.emit(i.getToken(), Message::Severity::InternalCompilerError);

				ok = false;
			}
		}
	}

	return ok;
}
}
