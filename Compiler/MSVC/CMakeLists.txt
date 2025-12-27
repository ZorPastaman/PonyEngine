message(STATUS "Configuring MSVC support")

message(VERBOSE "Configuring PonyEngine.Core headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

message(VERBOSE "Configuring PonyEngine.Core defines")
target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_COMPILER_INCLUDE="PonyEngine/Macro/MSVC/Compiler.h"
)
