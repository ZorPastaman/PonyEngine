message(STATUS "Configuring PonyEngine.RawInput.Mouse.Impl feature module")

add_library(PonyEngine.RawInput.Mouse.Impl STATIC)

target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Mouse.cppm"
	"Source/Mouse-MouseAxis.cppm"
	"Source/Mouse-MouseAxisMap.cppm"
	"Source/Mouse-MouseController.cppm"
)

set_target_properties(PonyEngine.RawInput.Mouse.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.RawInput.Mouse.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
)
