message(STATUS "Configuring PonyEngine.Display.Impl.WinAPI modification module")

set(PONY_ENGINE_DISPLAY_ORDER "p" CACHE STRING "PonyEngine.Display.Impl module initialization order. Its first character must be in range [b-y].")

target_include_directories(PonyEngine.Display.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Display.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Display.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Display.Impl PUBLIC FILE_SET CXX_MODULES FILES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Display.cppm"
	"Source/Display-DisplayService.cppm"
	"Source/Display-DisplayServiceModule.cppm"
)

pony_add_winapi_manifest("Manifests/DPIAwareness.manifest")

pony_validate_module_order(PONY_ENGINE_DISPLAY_ORDER)
target_compile_definitions(PonyEngine.Display.Impl PUBLIC
	PONY_ENGINE_DISPLAY_ORDER=${PONY_ENGINE_DISPLAY_ORDER}
)

target_link_libraries(PonyEngine.Display.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Display.Impl PRIVATE
	PonyEngine.Log
)
