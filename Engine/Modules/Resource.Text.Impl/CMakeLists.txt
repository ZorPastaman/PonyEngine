message(STATUS "Configuring PonyEngine.Resource.Text.Impl feature module")

set(PONY_ENGINE_RESOURCE_TEXT_ORDER "p" CACHE STRING "PonyEngine.Resource.Text.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Resource.Text.Impl STATIC)

target_include_directories(PonyEngine.Resource.Text.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Resource.Text.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.Text.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.Text.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Text.cppm"
	"Source/Text-CompletedResourceLoadRequest.cppm"
	"Source/Text-OngoingResourceLoadRequest.cppm"
	"Source/Text-TextLoader.cppm"
	"Source/Text-TextLoaderModule.cppm"
	"Source/Text-TextResource.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_TEXT_ORDER)
target_compile_definitions(PonyEngine.Resource.Text.Impl PUBLIC
	PONY_ENGINE_RESOURCE_TEXT_ORDER=${PONY_ENGINE_RESOURCE_TEXT_ORDER}
)

set_target_properties(PonyEngine.Resource.Text.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.Text.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.Text.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Resource
	PonyEngine.Resource.Ext
)
