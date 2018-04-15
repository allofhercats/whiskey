namespace whiskey {
template<typename T>
void printAssertValue(AssertMode mode, const char *label, const char *text, const T value) {
	getAssertOStream(mode) << "  " << label << ": " << text << "\n";
	getAssertOStream(mode) << "    = " << value << "\n";
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
