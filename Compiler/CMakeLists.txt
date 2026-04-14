message(VERBOSE "Configuring compiler: ${CMAKE_CXX_COMPILER_ID}")

if(MSVC)
	add_subdirectory("MSVC")
else()
	message(FATAL_ERROR "Unsupported compiler!")
endif()
