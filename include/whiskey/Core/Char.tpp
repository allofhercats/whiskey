namespace whiskey {
template<typename T>
Char32 readCharUTF(const T *src, CharOffset &pos, CharOffset length) {
	if (sizeof(T) == 1) {
		return readCharUTF8((const Char8 *)src, pos, length);
	} else if (sizeof(T) == 2) {
		return readCharUTF16((const Char16 *)src, pos, length);
	} else if (sizeof(T) == 4) {
		return readCharUTF32((const Char32 *)src, pos, length);
	} else {
		W_ASSERT_UNREACHABLE("Unsupported ")
	}
}
}
