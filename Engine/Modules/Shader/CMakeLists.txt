message(STATUS "Configuring PonyEngine.Shader")

add_library(PonyEngine.Shader STATIC)

target_sources(PonyEngine.Shader PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-Bool.cppm"
	"Source/Main-Meshlet.cppm"
)

set_target_properties(PonyEngine.Shader PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
	PONY_ENGINE_SHADER_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/ShaderInclude"
)

target_link_libraries(PonyEngine.Shader PUBLIC
	PonyEngine.Core
)
