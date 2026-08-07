message(STATUS "Configuring PonyEngine.File.Impl for Windows")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()

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
	"Source/Main.cppm"
	"Source/Main-File.cppm"
	"Source/Main-FileContext.cppm"
	"Source/Main-FileService.cppm"
	"Source/Main-FileServiceModule.cppm"
	"Source/Main-FileUtility.cppm"
	"Source/Main-OverlappedRequest.cppm"
	"Source/Main-OverlappedUtility.cppm"
	"Source/Main-ServiceContext.cppm"
	"Source/Main-Worker.cppm"
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
