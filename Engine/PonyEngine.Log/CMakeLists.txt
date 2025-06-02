message(STATUS "Configuring PonyEngine.Log")
add_library(PonyEngine.Log STATIC)

message(STATUS "Configuring headers")
target_include_directories(PonyEngine.Log PUBLIC
	"Include/Public"
)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Log PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Log/Log.cppm"
	"Source/Public/Log/Log-ILogger.cppm"
	"Source/Public/Log/Log-LogFormat.cppm"
	"Source/Public/Log/Log-LogHelper.cppm"
	"Source/Public/Log/Log-LogInput.cppm"
	"Source/Public/Log/Log-LogType.cppm"
)

message(STATUS "Configuring defines")
pony_set_log_mask(PonyEngine.Log TRUE)

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log TRUE)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log PRIVATE
	PonyEngine.Core
)
