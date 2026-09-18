message(STATUS "Configuring PonyEngine.File.Impl.WinAPI modification module")

set(PONY_ENGINE_FILE_ORDER "p" CACHE STRING "PonyEngine.File.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_FILE_THREAD_ROLE "IO" CACHE STRING "PonyEngine.File.Impl io thread role.")

target_include_directories(PonyEngine.File.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.File.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.File.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.File.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/File.cppm"
	"Source/File-File.cppm"
	"Source/File-FileService.cppm"
	"Source/File-FileServiceModule.cppm"
	"Source/File-FileUtility.cppm"
	"Source/File-OverlappedReadRequest.cppm"
	"Source/File-OverlappedRequest.cppm"
	"Source/File-OverlappedUtility.cppm"
	"Source/File-OverlappedWriteRequest.cppm"
	"Source/File-Worker.cppm"
)

pony_validate_module_order(PONY_ENGINE_FILE_ORDER)
target_compile_definitions(PonyEngine.File.Impl PUBLIC
	PONY_ENGINE_FILE_ORDER=${PONY_ENGINE_FILE_ORDER}
	PONY_ENGINE_FILE_THREAD_ROLE=${PONY_ENGINE_FILE_THREAD_ROLE}
)

target_link_libraries(PonyEngine.File.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.File.Impl PRIVATE
	PonyEngine.Log
)
