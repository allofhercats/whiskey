namespace whiskey {
template<class T>
void DebugPrinter::printHelper(std::ostream &os, const std::string &label, CRef<T> ast, unsigned int indent) {
	printNewline(os, indent+1);
	os << Color::cyan << label << ":" << Color::reset;
	print(os, ast->template as<AST>(), indent+1);
}

template<class T>
void DebugPrinter::printVectorHelper(std::ostream &os, const std::string &label, const std::vector<Container<T>> &ast, unsigned int indent) {
	printNewline(os, indent+1);
	int n = 0;
	os << Color::cyan << label << ":" << Color::reset;
	printNewline(os, indent+2);
	for (auto &i : ast) {
		if (n > 0) {
			printNewline(os, indent+2);
		}
		os << Color::greyDark << "[" << n << "] " << Color::reset;
		print(os, i->template as<AST>(), indent+2);
		n++;
	}
}
}
