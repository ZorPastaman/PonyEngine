message(VERBOSE "Configuring platform: ${CMAKE_SYSTEM_NAME}")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_subdirectory("Windows")
else()
	message(FATAL_ERROR "Unsupported platform!")
endif()
