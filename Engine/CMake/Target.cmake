# Initializes target dependent variables.

include(CheckTypeSize)
include(TestBigEndian)

check_type_size("std::size_t" PONY_SIZEOF_SIZE_T LANGUAGE CXX)
set(PONY_SIZEOF_SIZE_T ${PONY_SIZEOF_SIZE_T} CACHE INTERNAL "sizeof(std::size_t) of the target platform")

test_big_endian(PONY_IS_BIG_ENDIAN)
set(PONY_IS_BIG_ENDIAN ${PONY_IS_BIG_ENDIAN} CACHE INTERNAL "Is target platform big-endian?")
