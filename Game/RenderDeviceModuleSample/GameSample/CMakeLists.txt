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
)

set(PONY_ENGINE_SHADER_ASSETS "${PONY_ENGINE_ASSETS}/Shaders")
set(DATA "${CMAKE_BINARY_DIR}/Data")
set(DATA_SHADERS "${DATA}/Shaders")

set(SHADER_REGISTRY "")
macro(compile_shader)
	cmake_parse_arguments(
		SHADER
		""
		"INPUT;OUTPUT;PROFILE"
		""
		${ARGN}
	)

	compile_shader_with_dxc("${SHADER_INPUT}" "${SHADER_OUTPUT}" 
		PROFILE ${SHADER_PROFILE} 
		INCLUDES ${PONY_ENGINE_SHADER_LIB}
	)
	list(APPEND SHADER_REGISTRY "${SHADER_OUTPUT}")
endmacro()
compile_shader(INPUT "${PONY_ENGINE_SHADER_ASSETS}/Mesh/DefaultTriangle.hlsl" OUTPUT "${DATA_SHADERS}/Mesh/DefaultTriangle.cso" PROFILE ms_6_6)
compile_shader(INPUT "${PONY_ENGINE_SHADER_ASSETS}/Pixel/DefaultPixel.hlsl" OUTPUT "${DATA_SHADERS}/Pixel/DefaultPixel.cso" PROFILE ps_6_6)
add_custom_target(Shaders ALL DEPENDS ${SHADER_REGISTRY})

install(DIRECTORY ${DATA} DESTINATION . FILES_MATCHING PATTERN "*.cso")
