message(STATUS "Configuring PonyEngine.MSVC")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_COMPILER_DIR="PonyEngine/Macro/MSVC/Compiler.h"
)
