message(STATUS "Configuring PonyEngine.File.Impl for Windows")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_FILE_ORDER "p" CACHE STRING "PonyEngine.File.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.File.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.File.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.File.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.File.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-File.cppm"
	"Source/Main-FileService.cppm"
	"Source/Main-FileServiceModule.cppm"
	"Source/Main-FileUtility.cppm"
	"Source/Main-OverlappedRequest.cppm"
	"Source/Main-OverlappedUtility.cppm"
	"Source/Main-Worker.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_FILE_ORDER)
target_compile_definitions(PonyEngine.File.Impl PUBLIC
	PONY_ENGINE_FILE_ORDER=${PONY_ENGINE_FILE_ORDER}
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.File.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.File.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
)
