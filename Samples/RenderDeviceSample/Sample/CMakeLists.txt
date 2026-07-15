# Set module.
add_library(Sample STATIC)

# Set includes and sources.
target_include_directories(Sample PUBLIC
	"Include/Public"
)
target_sources(Sample PUBLIC
	"Source/Launch.cpp"
)
target_sources(Sample PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(Sample PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Game.cppm"
	"Source/Game-GameService.cppm"
	"Source/Game-GameServiceModule.cppm"
)

# Set properties. CXX_STANDARD must be at least 23. POSITION_INDEPENDENT_CODE TRUE is required to build shared library groups consisting of this static lib.
set_target_properties(Sample PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

# Set dependencies.
target_link_libraries(Sample PUBLIC 
	PonyEngine.Application
)
target_link_libraries(Sample PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Resource
	PonyEngine.RawInput
	PonyEngine.RenderDevice
	PonyEngine.Shader
	PonyEngine.Surface
	PonyEngine.Time
)

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

	pony_compile_shader_with_dxc("${SHADER_INPUT}" "${SHADER_OUTPUT}" "${SHADER_PROFILE}"
		PDB
		INCLUDES ${PONY_ENGINE_SHADER_LIB} "${CMAKE_CURRENT_LIST_DIR}/ShaderInclude"
	)
	list(APPEND SHADER_REGISTRY "${SHADER_OUTPUT}")
endmacro()
set(OBJECT_SHADER "Data/Shaders/Mesh/Object.cso")
set(PIXEL_SHADER "Data/Shaders/Pixel/Pixel.cso")
set(FULLSCREEN_QUAD_SHADER "Data/Shaders/Mesh/FullscreenQuad.cso")
set(TEXTURE_SHADER "Data/Shaders/Pixel/Texture.cso")
compile_shader(INPUT "Assets/Shaders/Mesh/Object.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${OBJECT_SHADER}" PROFILE ms_6_6)
compile_shader(INPUT "Assets/Shaders/Pixel/Pixel.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${PIXEL_SHADER}" PROFILE ps_6_6)
compile_shader(INPUT "Assets/Shaders/Mesh/FullscreenQuad.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${FULLSCREEN_QUAD_SHADER}" PROFILE ms_6_6)
compile_shader(INPUT "Assets/Shaders/Pixel/Texture.hlsl" OUTPUT "${CMAKE_BINARY_DIR}/${TEXTURE_SHADER}" PROFILE ps_6_6)
add_custom_target(Shaders ALL DEPENDS ${SHADER_REGISTRY})

# Make shader manifest
set(SHADER_MANIFEST "Manifests/Resource/Pack/ShaderManifest")
set(SHADER_MANIFEST_SOURCE "${CMAKE_BINARY_DIR}/Intermediate/${SHADER_MANIFEST}.toml")
set(SHADER_PACK "Data/Packs/Shaders.bin")
pony_create_pack_resource_manifest(${SHADER_MANIFEST_SOURCE} ${SHADER_PACK})
set(OBJECT_SHADER_RESOURCE_ID "Object")
set(PIXEL_SHADER_RESOURCE_ID "Pixel")
set(FULLSCREEN_QUAD_SHADER_RESOURCE_ID "FullscreenQuad")
set(TEXTURE_SHADER_RESOURCE_ID "Texture")
set(PONY_SHADER_TYPE "PonyShader")
set(OBJECT_SHADER_RESOURCE "")
set(PIXEL_SHADER_RESOURCE "")
set(FULLSCREEN_QUAD_SHADER_RESOURCE "")
set(TEXTURE_SHADER_RESOURCE "")
pony_make_resource_for_pack_resource_manifest(${OBJECT_SHADER_RESOURCE_ID} ${PONY_SHADER_TYPE} ${OBJECT_SHADER} OBJECT_SHADER_RESOURCE)
pony_make_resource_for_pack_resource_manifest(${PIXEL_SHADER_RESOURCE_ID} ${PONY_SHADER_TYPE} ${PIXEL_SHADER} PIXEL_SHADER_RESOURCE)
pony_make_resource_for_pack_resource_manifest(${FULLSCREEN_QUAD_SHADER_RESOURCE_ID} ${PONY_SHADER_TYPE} ${FULLSCREEN_QUAD_SHADER} FULLSCREEN_QUAD_SHADER_RESOURCE)
pony_make_resource_for_pack_resource_manifest(${TEXTURE_SHADER_RESOURCE_ID} ${PONY_SHADER_TYPE} ${TEXTURE_SHADER} TEXTURE_SHADER_RESOURCE)
set(SHADER_RESOURCE_LIST ${OBJECT_SHADER_RESOURCE} ${PIXEL_SHADER_RESOURCE} ${FULLSCREEN_QUAD_SHADER_RESOURCE} ${TEXTURE_SHADER_RESOURCE})
pony_add_to_pack_resource_manifest(${SHADER_MANIFEST_SOURCE} RESOURCES ${SHADER_RESOURCE_LIST})
set(SHADER_MANIFEST "${SHADER_MANIFEST}.pprm")
pony_compile_pack_resource_manifest(${SHADER_MANIFEST_SOURCE} "${CMAKE_BINARY_DIR}/${SHADER_PACK}" "${CMAKE_BINARY_DIR}/${SHADER_MANIFEST}"
	ROOT "${CMAKE_BINARY_DIR}")
add_custom_target(Manifests ALL DEPENDS "${CMAKE_BINARY_DIR}/${SHADER_PACK}" "${CMAKE_BINARY_DIR}/${SHADER_MANIFEST}")

# Set defines.
target_compile_definitions(Sample PRIVATE
	OBJECT_SHADER_RESOURCE_ID=${OBJECT_SHADER_RESOURCE_ID}
	PIXEL_SHADER_RESOURCE_ID=${PIXEL_SHADER_RESOURCE_ID}
	FULLSCREEN_QUAD_SHADER_RESOURCE_ID=${FULLSCREEN_QUAD_SHADER_RESOURCE_ID}
	TEXTURE_SHADER_RESOURCE_ID=${TEXTURE_SHADER_RESOURCE_ID}
)

install(DIRECTORY "${CMAKE_BINARY_DIR}/Data" DESTINATION . FILES_MATCHING PATTERN "*.bin")
install(DIRECTORY "${CMAKE_BINARY_DIR}/Manifests" DESTINATION . FILES_MATCHING PATTERN "*.pprm")
