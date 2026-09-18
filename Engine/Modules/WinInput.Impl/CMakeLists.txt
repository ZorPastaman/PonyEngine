message(STATUS "Configuring PonyEngine.WinInput.Impl feature module")

set(PONY_ENGINE_WININPUT_ORDER "p" CACHE STRING "PonyEngine.WinInput.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.WinInput.Impl STATIC)

target_include_directories(PonyEngine.WinInput.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.WinInput.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.WinInput.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.WinInput.Impl PUBLIC FILE_SET CXX_MODULES FILES
	"Source/WinInput.cppm"
	"Source/WinInput-InputDispatcher.cppm"
	"Source/WinInput-InputDispatcherModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_WININPUT_ORDER)
target_compile_definitions(PonyEngine.WinInput.Impl PUBLIC
	PONY_ENGINE_WININPUT_ORDER=${PONY_ENGINE_WININPUT_ORDER}
)

set_target_properties(PonyEngine.WinInput.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.WinInput.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.WinInput.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.WinInput
)
