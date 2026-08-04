message(STATUS "Configuring PonyEngine.Core for MSVC")

target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_COMPILER_INCLUDE="PonyEngine/Macro/MSVC/Compiler.h"
	PONY_MSVC
)
