// #include <whiskey/Core/StringRef.hpp>

// #include <whiskey/Core/Assert.hpp>

namespace whiskey {
// StringRef::StringRef() : String() {
// }

// StringRef::StringRef(const char *value, size_t length) : String() {
//   width = 1;
//   data.asChar8 = (Char8 *)value;
//   this->_length = length == String::npos ? getStringLength(value) : length;
// }

// StringRef::StringRef(const char16_t *value, size_t length)
//     : String() {
//   width = 2;
//   data.asChar16 = (Char16 *)value;
//   this->_length = length == String::npos ? getStringLength(value) : length;
// }

// StringRef::StringRef(const char32_t *value, size_t length)
//     : String() {
//   width = 4;
//   data.asChar32 = (Char32 *)value;
//   this->_length = length == String::npos ? getStringLength(value) : length;
// }

// StringRef::StringRef(const wchar_t *value, size_t length)
//     : String() {
//   if (sizeof(wchar_t) == 1) {
//     width = 1;
//     data.asChar8 = (Char8 *)value;
//   } else if (sizeof(wchar_t) == 2) {
//     width = 2;
//     data.asChar16 = (Char16 *)value;
//   } else if (sizeof(wchar_t) == 4) {
//     width = 4;
//     data.asChar32 = (Char32 *)value;
//   } else {
//     W_ASSERT_UNREACHABLE("Unsupported char width " << sizeof(wchar_t) <<
//     ".");
//   }
//   this->_length = length == String::npos ? getStringLength(value) : length;
// }

// StringRef::StringRef(const std::string &value)
//     : StringRef(value.c_str(), value.size()) {
// }

// StringRef::StringRef(const std::u16string &value)
//     : StringRef(value.c_str(), value.size()) {
// }

// StringRef::StringRef(const std::u32string &value)
//     : StringRef(value.c_str(), value.size()) {
// }

// StringRef::StringRef(const std::wstring &value)
//     : StringRef(value.c_str(), value.size()) {
// }

// void StringRef::resize(size_t value) {
//   W_ASSERT_LE(value, _length, "Cannot increase length of string reference.");
//   _length = value;
// }
} // namespace whiskey
