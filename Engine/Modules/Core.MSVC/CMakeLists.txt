message(STATUS "Configuring PonyEngine.Core.MSVC modification module")

target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_ENGINE_CORE_COMPILER_INCLUDE="PonyEngine/Core/MSVC/Compiler.h"
)
