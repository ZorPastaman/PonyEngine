include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
	#include <climits>

	static_assert(CHAR_BIT == 8);

	int main() { return 0; }
" PONY_COMPATIBLE_CHAR)
if(NOT PONY_COMPATIBLE_CHAR)
	message(FATAL_ERROR "Unsupported char type on target platform")
endif()

check_cxx_source_compiles("
	#include <limits>

	static_assert(sizeof(float) == 4);
	static_assert(std::numeric_limits<float>::is_iec559);

	int main() { return 0; }
" PONY_COMPATIBLE_FLOAT)
if(NOT PONY_COMPATIBLE_FLOAT)
	message(FATAL_ERROR "Unsupported float type on target platform")
endif()

check_cxx_source_compiles("
	#include <limits>

	static_assert(sizeof(double) == 8);
	static_assert(std::numeric_limits<double>::is_iec559);

	int main() { return 0; }
" PONY_COMPATIBLE_DOUBLE)
if(NOT PONY_COMPATIBLE_DOUBLE)
	message(FATAL_ERROR "Unsupported double type on target platform")
endif()
