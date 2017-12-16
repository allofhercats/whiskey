#ifndef __WHISKEY_Core_Assert_HPP
#define __WHISKEY_Core_Assert_HPP

#include <whiskey/Core/Module.inc>

#define _W_ASSERT_STREAM (::std::cerr)
#define _W_ASSERT_BOOL bool
#define _W_ASSERT_POINTER void *
#define _W_ASSERT_INT int64_t
#define _W_ASSERT_UINT uint64_t

#define _W_ASSERT_PRINT_MSG(desc) { \
	_W_ASSERT_STREAM << __FILE__ << ":" << __LINE__ << ": assert failed: " << desc << "\n"; \
}

#define _W_ASSERT_PRINT_REASON(reason) { \
	_W_ASSERT_STREAM << "  reason: "; \
	_W_ASSERT_STREAM << reason; \
	_W_ASSERT_STREAM << "\n"; \
}

#define _W_ASSERT_DIE() { \
	abort(); \
}

#define W_ASSERT_UNREACHABLE(reason) { \
	_W_ASSERT_PRINT_MSG("code is unreachable"); \
	_W_ASSERT_PRINT_REASON(reason); \
	_W_ASSERT_DIE(); \
}

#define W_ASSERT_TRUE(arg0, reason) { \
	_W_ASSERT_BOOL _w_arg0Value = (_W_ASSERT_BOOL)(arg0); \
	if (!_w_arg0Value) { \
		_W_ASSERT_PRINT_MSG("expected to be true"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  actual: " << #arg0 << " (false)\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_FALSE(arg0, reason) { \
	_W_ASSERT_BOOL _w_arg0Value = (_W_ASSERT_BOOL)(arg0); \
	if (_w_arg0Value) { \
		_W_ASSERT_PRINT_MSG("expected to be false"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  actual: " << #arg0 << " (true)\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_NULL(arg0, reason) { \
	_W_ASSERT_POINTER _w_arg0Value = (_W_ASSERT_POINTER)(arg0); \
	if (_w_arg0Value != nullptr) { \
		_W_ASSERT_PRINT_MSG("expected to be null"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  actual: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_NONNULL(arg0, reason) { \
	_W_ASSERT_POINTER _w_arg0Value = (_W_ASSERT_POINTER)(arg0); \
	if (_w_arg0Value == nullptr) { \
		_W_ASSERT_PRINT_MSG("expected to not be null"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  actual: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_LT(arg0, arg1, reason) { \
	_W_ASSERT_INT _w_arg0Value = (_W_ASSERT_INT)(arg0); \
	_W_ASSERT_INT _w_arg1Value = (_W_ASSERT_INT)(arg1); \
	if (!(_w_arg0Value < _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be less than"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_LE(arg0, arg1, reason) { \
	_W_ASSERT_INT _w_arg0Value = (_W_ASSERT_INT)(arg0); \
	_W_ASSERT_INT _w_arg1Value = (_W_ASSERT_INT)(arg1); \
	if (!(_w_arg0Value <= _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be less than or equal to"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_GT(arg0, arg1, reason) { \
	_W_ASSERT_INT _w_arg0Value = (_W_ASSERT_INT)(arg0); \
	_W_ASSERT_INT _w_arg1Value = (_W_ASSERT_INT)(arg1); \
	if (!(_w_arg0Value > _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be greater than"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_GE(arg0, arg1, reason) { \
	_W_ASSERT_INT _w_arg0Value = (_W_ASSERT_INT)(arg0); \
	_W_ASSERT_INT _w_arg1Value = (_W_ASSERT_INT)(arg1); \
	if (!(_w_arg0Value >= _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be greater than or equal to"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_ULT(arg0, arg1, reason) { \
	_W_ASSERT_UINT _w_arg0Value = (_W_ASSERT_UINT)(arg0); \
	_W_ASSERT_UINT _w_arg1Value = (_W_ASSERT_UINT)(arg1); \
	if (!(_w_arg0Value < _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be less than"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_ULE(arg0, arg1, reason) { \
	_W_ASSERT_UINT _w_arg0Value = (_W_ASSERT_UINT)(arg0); \
	_W_ASSERT_UINT _w_arg1Value = (_W_ASSERT_UINT)(arg1); \
	if (!(_w_arg0Value <= _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be less than or equal to"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_UGT(arg0, arg1, reason) { \
	_W_ASSERT_UINT _w_arg0Value = (_W_ASSERT_UINT)(arg0); \
	_W_ASSERT_UINT _w_arg1Value = (_W_ASSERT_UINT)(arg1); \
	if (!(_w_arg0Value > _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be greater than"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_UGE(arg0, arg1, reason) { \
	_W_ASSERT_UINT _w_arg0Value = (_W_ASSERT_UINT)(arg0); \
	_W_ASSERT_UINT _w_arg1Value = (_W_ASSERT_UINT)(arg1); \
	if (!(_w_arg0Value >= _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be greater than or equal to"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_NE(arg0, arg1, reason) { \
	_W_ASSERT_INT _w_arg0Value = (_W_ASSERT_INT)(arg0); \
	_W_ASSERT_INT _w_arg1Value = (_W_ASSERT_INT)(arg1); \
	if (!(_w_arg0Value != _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to not be equal to"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#define W_ASSERT_EQ(arg0, arg1, reason) { \
	_W_ASSERT_INT _w_arg0Value = (_W_ASSERT_INT)(arg0); \
	_W_ASSERT_INT _w_arg1Value = (_W_ASSERT_INT)(arg1); \
	if (!(_w_arg0Value == _w_arg1Value)) { \
		_W_ASSERT_PRINT_MSG("expected to be equal to"); \
		_W_ASSERT_PRINT_REASON(reason); \
		_W_ASSERT_STREAM << "  lhs: " << #arg0 << " (" << _w_arg0Value << ")\n"; \
		_W_ASSERT_STREAM << "  rhs: " << #arg1 << " (" << _w_arg1Value << ")\n"; \
		_W_ASSERT_DIE(); \
	} \
}

#endif
