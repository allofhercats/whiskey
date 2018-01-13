#include <whiskey/Unicode/StringRef.hpp>

namespace whiskey {
StringRef::StringRef() : String() {}

StringRef::StringRef(Encoding encoding) : String(encoding) {}

StringRef::StringRef(const Char8 *value) : String(value) {}

StringRef::StringRef(const Char8 *value, size_t length) : String(value, length) {}

StringRef::StringRef(const Char16 *value) : String(value) {}

StringRef::StringRef(const Char16 *value, size_t length) : String(value, length) {}

StringRef::StringRef(const Char32 *value) : String(value) {}

StringRef::StringRef(const Char32 *value, size_t length) : String(value, length) {}

StringRef::StringRef(const std::string &value) : String(value) {}

StringRef::StringRef(const std::string &value, size_t length) : String(value, length) {}

StringRef::StringRef(const std::u16string &value) : String(value) {}

StringRef::StringRef(const std::u16string &value, size_t length) : String(value, length) {}

StringRef::StringRef(const std::u32string &value) : String(value) {}

StringRef::StringRef(const std::u32string &value, size_t length) : String(value, length) {}
}
