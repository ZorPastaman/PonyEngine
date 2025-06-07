message(STATUS "Configuring PonyEngine.Log.Impl")
add_library(PonyEngine.Log.Impl SHARED)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Log.Impl PUBLIC
	"Source/Main.Logger.cpp"
)

message(STATUS "Configuring defines")
pony_set_log_mask(PonyEngine.Log.Impl TRUE)
target_compile_definitions(PonyEngine.Log.Impl PRIVATE PONY_DLL)

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Log.Impl PROPERTIES OUTPUT_NAME "PonyEngine.Log")

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log.Impl TRUE)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Impl PRIVATE
	PonyEngine.Core
)
pony_add_app_module(PonyEngine.Log.Impl)

message(STATUS "Installing")
get_property(PONY_APP_INSTALL_PATH_VALUE GLOBAL PROPERTY PONY_APP_INSTALL_PATH)
message(STATUS "Application destination: ${PONY_APP_INSTALL_PATH_VALUE}")
install(TARGETS PonyEngine.Log.Impl RUNTIME DESTINATION ${PONY_APP_INSTALL_PATH_VALUE})
