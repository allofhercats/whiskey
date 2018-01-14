namespace whiskey {
template<typename T>
void StringContainer::assign(const T *data) {
	assign(data, getStringLength<T>(data));
}

template<typename T>
void StringContainer::assign(const T *data, size_t length) {
	W_ASSERT_NONNULL(data, "Cannot assign null to string container.");

	if (this->data.asChar8 != nullptr) {
		delete[] this->data.asChar8;
	}

	if (length == 0) {
		this->data.asChar8 = nullptr;
		this->length = 0;
		capacity = 0;
	} else {
		capacity = getNextPowOf2(length);
		this->data.asChar8 = new Char8[capacity * sizeof(T)];
		memcpy(this->data.asChar8, data, length * sizeof(T));
		this->length = length;
	}
}
}
