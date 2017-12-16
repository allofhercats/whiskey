namespace whiskey {
template<class ValueType>
bool AST::compare(const Container<ValueType> &lhs, const Container<ValueType> &rhs) {
	if (lhs) {
		if (rhs) {
			return lhs->compare(rhs);
		} else {
			return false;
		}
	} else {
		if (rhs) {
			return false;
		} else {
			return true;
		}
	}
}

template<class ValueType>
bool AST::compare(const Ref<ValueType> &lhs, const Ref<ValueType> &rhs) {
	if (lhs) {
		if (rhs) {
			return lhs->compare(rhs);
		} else {
			return false;
		}
	} else {
		if (rhs) {
			return false;
		} else {
			return true;
		}
	}
}

template<class ValueType>
bool AST::compare(const CRef<ValueType> &lhs, const CRef<ValueType> &rhs) {
	if (lhs) {
		if (rhs) {
			return lhs->compare(rhs);
		} else {
			return false;
		}
	} else {
		if (rhs) {
			return false;
		} else {
			return true;
		}
	}
}

template<class ValueType>
bool AST::compare(const std::vector<Container<ValueType>> &lhs, const std::vector<Container<ValueType>> &rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	auto li = lhs.begin();
	auto ri = rhs.begin();
	
	while (li != lhs.end()) {
		if (!compare(*li, *ri)) {
			return false;
		}

		++li;
		++ri;
	}

	return true;
}

template<class ValueType>
bool AST::compare(const std::vector<Ref<ValueType>> &lhs, const std::vector<Ref<ValueType>> &rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	auto li = lhs.begin();
	auto ri = rhs.begin();
	
	while (li != lhs.end()) {
		if (!compare(*li, *ri)) {
			return false;
		}

		++li;
		++ri;
	}

	return true;
}

template<class ValueType>
bool AST::compare(const std::vector<CRef<ValueType>> &lhs, const std::vector<CRef<ValueType>> &rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	auto li = lhs.begin();
	auto ri = rhs.begin();
	
	while (li != lhs.end()) {
		if (!compare(*li, *ri)) {
			return false;
		}

		++li;
		++ri;
	}

	return true;
}

template<class ValueType>
Ref<ValueType> AST::as() {
	return Ref<ValueType>(static_cast<ValueType *>(this));
}

template<class ValueType>
CRef<ValueType> AST::as() const {
	return CRef<ValueType>(static_cast<const ValueType *>(this));
}

template<class ValueType>
bool AST::compare(const Ref<ValueType> &other) const {
	return compare(*other);
}

template<class ValueType>
bool AST::compare(const CRef<ValueType> &other) const {
	return compare(*other);
}

template<class ValueType>
bool AST::compare(const Container<ValueType> &other) const {
	return compare(*other);
}
}
