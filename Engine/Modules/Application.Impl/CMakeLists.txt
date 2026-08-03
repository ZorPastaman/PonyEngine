message(STATUS "Configuring PonyEngine.Application.Impl")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()

message(VERBOSE "Configuring environment")
include("CMake/Module.cmake")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_APPLICATION_ROOT_PATH "" CACHE STRING "Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid.")
set(PONY_ENGINE_APPLICATION_TARGET_FRAME_PERIOD "0.0" CACHE STRING "Application target frame period in seconds. Must be double.")

message(VERBOSE "Configuring target")
add_executable(PonyEngine.Application.Impl)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-App.cppm"
	"Source/Main-Buffer.cppm"
	"Source/Main-IdentityUtility.cppm"
	"Source/Main-PathUtility.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_path(PONY_ENGINE_APPLICATION_ROOT_PATH CAN_BE_RELATIVE CAN_BE_EMPTY)
target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	PONY_ENGINE_NAME=${PONY_ENGINE_NAME}
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
	PONY_ENGINE_TITLE=${PONY_ENGINE_TITLE}
	PONY_COMPANY_NAME=${PONY_COMPANY_NAME} 
	PONY_PROJECT_NAME=${PONY_PROJECT_NAME} 
	PONY_PROJECT_VERSION_MAJOR=${PONY_PROJECT_VERSION_MAJOR}
	PONY_PROJECT_VERSION_MINOR=${PONY_PROJECT_VERSION_MINOR}
	PONY_PROJECT_VERSION_PATCH=${PONY_PROJECT_VERSION_PATCH}
	PONY_PROJECT_VERSION_TWEAK=${PONY_PROJECT_VERSION_TWEAK}
	PONY_COMPANY_TITLE=${PONY_COMPANY_TITLE} 
	PONY_PROJECT_TITLE=${PONY_PROJECT_TITLE}
	PONY_ENGINE_APPLICATION_ROOT_PATH=${PONY_ENGINE_APPLICATION_ROOT_PATH}
	PONY_ENGINE_APPLICATION_TARGET_FRAME_PERIOD=${PONY_ENGINE_APPLICATION_TARGET_FRAME_PERIOD}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Impl PROPERTIES
	OUTPUT_NAME "${PONY_PROJECT_NAME}"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application.Impl PRIVATE
	PonyEngine.Application
	PonyEngine.Core
	PonyEngine.Log
)
