message(STATUS "Configuring PonyEngine.Application.MSVC modification module")

target_include_directories(PonyEngine.Application PUBLIC 
	"Include/Public"
)

target_compile_definitions(PonyEngine.Application PUBLIC
	PONY_ENGINE_APPLICATION_COMPILER_INCLUDE="PonyEngine/Application/MSVC/Compiler.h"
)
