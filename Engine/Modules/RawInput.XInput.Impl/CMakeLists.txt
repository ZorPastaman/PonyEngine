message(STATUS "Configuring PonyEngine.RawInput.XInput.Impl")

if(NOT TARGET PonyEngine.RawInput)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()
if(NOT TARGET PonyEngine.RawInput.Ext)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()

add_library(PonyEngine.RawInput.XInput.Impl STATIC)

set_target_properties(PonyEngine.RawInput.XInput.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.RawInput.XInput.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
)
