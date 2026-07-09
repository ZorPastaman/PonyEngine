# Initializes target dependent variables.

include(CheckTypeSize)

check_type_size("std::size_t" PONY_SIZEOF_SIZE_T LANGUAGE CXX)
set(PONY_SIZEOF_SIZE_T "${PONY_SIZEOF_SIZE_T}" CACHE INTERNAL "sizeof(std::size_t) of the target platform")
