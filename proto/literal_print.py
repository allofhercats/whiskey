def get_n_digits(value, base):
	n = 0
	if value == 0:
		return 1
	else:
		while value > 0:
			value //= base
			n += 1
	return n

def literal_int_to_string(value, base, width = 0, pad = '0', prefix = True):
	rtn = ""

	if base == 2 and prefix:
		rtn = "0b"
	elif base == 8 and prefix:
		rtn = "0"
	elif base == 16 and prefix:
		rtn = "0x"

	n_digits = get_n_digits(value, base)

	if width > 0 and width > n_digits:
		i = 0
		while i < width - n_digits:
			rtn += pad
			i += 1

	fac = base ** (n_digits - 1)
	i = 0
	while i < n_digits:
		digit = (value // fac) % base
		
		if base == 2:
			rtn += "01"[digit]
		elif base == 8:
			rtn += "01234567"[digit]
		elif base == 10:
			rtn += "0123456789"[digit]
		elif base == 16:
			rtn += "0123456789abcdef"[digit]
		else:
			raise NotImplementedError()

		fac //= base
		i += 1

	return rtn

def literal_float_to_string(value, precision = 5, strip = True):
	if value < 0.0:
		return "-" + literal_float_to_string(-value, precision, strip)

	rtn = literal_int_to_string(int(value), 10)
	rtn += "."

	value1 = value - int(value)
	n_stripped = 0
	i = 0
	while i < precision:
		value1 *= 10.0
		digit = int(value1) % 10
		if digit == 0:
			n_stripped += 1
		else:
			n_stripped = 0
		if not strip:
			rtn += "0123456789"[digit]
		i += 1

	if strip:
		value1 = value - int(value)
		i = 0
		while i < precision - n_stripped:
			value1 *= 10.0
			digit = int(value1) % 10
			rtn += "0123456789"[digit]
			i += 1

	return rtn

if __name__ == "__main__":
	print(literal_float_to_string(3.1400000000001, 20))
