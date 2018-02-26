namespace whiskey {
template<typename T>
void printAssertValue(const char *label, const char *text, const T value) {
	getAssertOStream() << "  " << label << ": " << text << "\n";
	getAssertOStream() << "    = " << value << "\n";
}

template<typename T, typename U>
int compareOnAssert(const T lhs, const U rhs) {
	if (lhs < rhs) {
		return -1;
	} else if (lhs == rhs) {
		return 0;
	} else {
		return 1;
	}
}
}
