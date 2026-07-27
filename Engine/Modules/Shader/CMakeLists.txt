message(STATUS "Configuring PonyEngine.Shader")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Shader STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Shader PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-Bool.cppm"
	"Source/Main-Meshlet.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Shader PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
	PONY_ENGINE_SHADER_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/ShaderInclude"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Shader PUBLIC
	PonyEngine.Core
)
