message(STATUS "Configuring PonyEngine.Application.Impl feature module")

include("CMake/Module.cmake")

set(PONY_ENGINE_APPLICATION_ROOT_PATH "" CACHE STRING "Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid.")
set(PONY_ENGINE_APPLICATION_TARGET_FRAME_PERIOD "0.002" CACHE STRING "Application target frame period in seconds. Must be double.")

add_executable(PonyEngine.Application.Impl)

target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Application.cppm"
	"Source/Application-App.cppm"
	"Source/Application-Buffer.cppm"
	"Source/Application-IdentityUtility.cppm"
	"Source/Application-IProcess.cppm"
	"Source/Application-PathUtility.cppm"
)

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

set_target_properties(PonyEngine.Application.Impl PROPERTIES
	OUTPUT_NAME "${PONY_PROJECT_NAME}"
)

target_link_libraries(PonyEngine.Application.Impl PRIVATE
	PonyEngine.Application
	PonyEngine.Core
	PonyEngine.Log
)
