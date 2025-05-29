message(STATUS "Configuring PonyEngine.Core.Impl")
add_library(PonyEngine.Core.Impl STATIC)
#add_compile_definitions(PONY_DLL)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Core.Impl PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Core/Core.cppm"
)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Core.Impl PRIVATE
	PonyEngine.Core
)

message(STATUS "Setting build options")
set_build_options(PonyEngine.Core.Impl TRUE)

message(STATUS "Setting globals")
set_property(GLOBAL APPEND PROPERTY PONY_APP_MODULES PonyEngine.Core.Impl)
