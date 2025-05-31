message(STATUS "Configuring PonyEngine.Core.Impl")
add_library(PonyEngine.Core.Impl SHARED)
add_compile_definitions(PONY_DLL)

target_include_directories(PonyEngine.Core.Impl PUBLIC "Include/Public")

message(STATUS "Configuring sources")
target_sources(PonyEngine.Core.Impl PUBLIC
	"Source/Public/Core/Core.cpp"
)
 target_sources(PonyEngine.Core.Impl PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Private/Write.cppm"
 )

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Core.Impl PRIVATE
	PonyEngine.Core
)

message(STATUS "Setting build options")
set_build_options(PonyEngine.Core.Impl TRUE)

message(STATUS "Setting globals")
set_property(GLOBAL APPEND PROPERTY PONY_APP_MODULES PonyEngine.Core.Impl)
set_property(GLOBAL APPEND PROPERTY PONY_INSTALL PonyEngine.Core.Impl)
