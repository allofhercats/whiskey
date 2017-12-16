namespace whiskey {
template<class T>
void DebugPrinter::printVectorHelper(std::ostream &os, const std::vector<Container<T>> &ast, unsigned int indent) {
	int n = 0;
	for (auto &i : ast) {
		os << "[" << n << "] ";
		print(os, i->template as<AST>(), indent);
		printNewline(os, indent);
	}
}
}
