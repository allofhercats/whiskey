#ifndef __WHISKEY_AST_PassContext_HPP
#define __WHISKEY_AST_PassContext_HPP

namespace whiskey {
class PassContext {
public:
	typedef std::list<Node *>::size_type DepthType;

private:
	Node *node;

public:
	PassContext(Node &node, MessageContext &msgs);
	PassContext(const PassContext &parent, Node &node, MessageContext &msgs);

	Node &getNode();
	MessageContext &getMessages();

	DepthType getDepth() const;
	const Node &getParent(DepthType depth = 0) const;

	void block();
	void halt();
};
}

#endif
