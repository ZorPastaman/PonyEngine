message(STATUS "Configuring PonyEngine.Core for MSVC")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_COMPILER_INCLUDE="PonyEngine/Macro/MSVC/Compiler.h"
)
