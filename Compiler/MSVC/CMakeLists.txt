message(STATUS "Configuring PonyEngine.Core for MSVC-compatible compiler")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_COMPILER_INCLUDE="PonyEngine/Macro/MSVC/Compiler.h"
	PONY_MSVC
)
