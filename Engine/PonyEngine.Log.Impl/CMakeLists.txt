message(STATUS "Configuring PonyEngine.Log.Impl")
if(PONY_FORCE_STATIC)
	add_library(PonyEngine.Log.Impl STATIC)
else()
	add_library(PonyEngine.Log.Impl SHARED)
endif()

message(STATUS "Configuring headers")
target_include_directories(PonyEngine.Log.Impl PUBLIC
	"Include/Public"
)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Log.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE
	"Source/Main.Logger.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Core/Core.cppm"
	"Source/Private/Core/Core-Logger.cppm"
	"Source/Private/Core/Core-LoggerFactory.cppm"
	"Source/Private/Core/Core-LoggerModule.cppm"
)

message(STATUS "Configuring defines")
pony_set_log_mask(PonyEngine.Log.Impl TRUE)
if(NOT PONY_FORCE_STATIC)
	target_compile_definitions(PonyEngine.Log.Impl PRIVATE PONY_DLL)
endif()

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Log.Impl PROPERTIES OUTPUT_NAME "PonyEngine.Log")

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log.Impl TRUE)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Impl PRIVATE
	PonyEngine.Core
)
pony_add_app_module(PonyEngine.Log.Impl)

if(NOT PONY_FORCE_STATIC)
	message(STATUS "Installing")
	get_property(PONY_APP_INSTALL_PATH_VALUE GLOBAL PROPERTY PONY_APP_INSTALL_PATH)
	message(STATUS "Application destination: ${PONY_APP_INSTALL_PATH_VALUE}")
	install(TARGETS PonyEngine.Log.Impl 
		RUNTIME DESTINATION ${PONY_APP_INSTALL_PATH_VALUE}
		LIBRARY DESTINATION
	)
endif()
