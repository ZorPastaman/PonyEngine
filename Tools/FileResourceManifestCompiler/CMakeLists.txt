message(STATUS "Configuring PonyTools.FileResourceManifestCompiler")

message(VERBOSE "Configuring target")
add_executable(PonyTools.FileResourceManifestCompiler)

message(VERBOSE "Configuring sources")
target_sources(PonyTools.FileResourceManifestCompiler PUBLIC
	"Source/Main.cpp"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyTools.FileResourceManifestCompiler PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME "ponyfrmc"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyTools.FileResourceManifestCompiler PRIVATE
	tomlplusplus::tomlplusplus
)
