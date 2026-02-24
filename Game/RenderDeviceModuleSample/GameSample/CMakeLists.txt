# Set module.
add_library(GameSample STATIC)

# Set includes and sources.
target_include_directories(GameSample PUBLIC
	"Include/Public"
)
target_sources(GameSample PUBLIC
	"Source/Main.cpp"
)
target_sources(GameSample PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(GameSample PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Game.cppm"
	"Source/Private/Game-GameService.cppm"
	"Source/Private/Game-GameServiceModule.cppm"
)

# Set properties. CXX_STANDARD must be at least 23. POSITION_INDEPENDENT_CODE TRUE is required to build shared library groups consisting of this static lib.
set_target_properties(GameSample PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

# Set dependencies.
target_link_libraries(GameSample PUBLIC 
	PonyEngine.Application.Ext
)
target_link_libraries(GameSample PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.RenderDevice
	PonyEngine.Shader
)

# Add data.
set(DATA "Data")

# Add shaders.
get_target_property(PONY_ENGINE_SHADER_LIB PonyEngine.Shader PONY_ENGINE_SHADER_INCLUDE)
set(SHADER_REGISTRY "")
macro(compile_shader)
	cmake_parse_arguments(
		SHADER
		""
		"INPUT;OUTPUT;PROFILE"
		""
		${ARGN}
	)

	compile_shader_with_dxc("${SHADER_INPUT}" "${SHADER_OUTPUT}" "${SHADER_PROFILE}"
		PDB
		INCLUDES ${PONY_ENGINE_SHADER_LIB} "${CMAKE_CURRENT_LIST_DIR}/ShaderInclude"
	)
	list(APPEND SHADER_REGISTRY "${SHADER_OUTPUT}")
endmacro()
set(TRIANGLE_SHADER "${DATA}/Shaders/Mesh/Triangle.cso")
set(PIXEL_SHADER "${DATA}/Shaders/Pixel/Pixel.cso")
set(FULLSCREEN_QUAD_SHADER "${DATA}/Shaders/Mesh/FullscreenQuad.cso")
set(TEXTURE_SHADER "${DATA}/Shaders/Pixel/Texture.cso")
compile_shader(INPUT "Assets/Shaders/Mesh/Triangle.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${TRIANGLE_SHADER}" PROFILE ms_6_6)
compile_shader(INPUT "Assets/Shaders/Pixel/Pixel.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${PIXEL_SHADER}" PROFILE ps_6_6)
compile_shader(INPUT "Assets/Shaders/Mesh/FullscreenQuad.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${FULLSCREEN_QUAD_SHADER}" PROFILE ms_6_6)
compile_shader(INPUT "Assets/Shaders/Pixel/Texture.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${TEXTURE_SHADER}" PROFILE ps_6_6)
add_custom_target(Shaders ALL DEPENDS ${SHADER_REGISTRY})

message(VERBOSE "Configuring defines")
target_compile_definitions(GameSample PRIVATE
	TRIANGLE_SHADER="${TRIANGLE_SHADER}"
	PIXEL_SHADER="${PIXEL_SHADER}"
	FULLSCREEN_QUAD_SHADER="${FULLSCREEN_QUAD_SHADER}"
	TEXTURE_SHADER="${TEXTURE_SHADER}"
)

install(DIRECTORY "${CMAKE_BINARY_DIR}/${DATA}" DESTINATION . FILES_MATCHING PATTERN "*.cso")
