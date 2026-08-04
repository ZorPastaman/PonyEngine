message(STATUS "Configuring PonyEngine.WinAPIInput.Impl")

if(NOT TARGET PonyEngine.WinAPIInput)
	message(FATAL_ERROR "PonyEngine.WinAPIInput wasn't configured")
endif()

add_library(PonyEngine.WinAPIInput.Impl STATIC)

set_target_properties(PonyEngine.WinAPIInput.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.WinAPIInput.Impl PRIVATE
	PonyEngine.WinAPIInput
)
