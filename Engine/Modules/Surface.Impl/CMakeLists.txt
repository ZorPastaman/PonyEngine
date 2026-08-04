message(STATUS "Configuring PonyEngine.Surface.Impl")

add_library(PonyEngine.Surface.Impl STATIC)

set_target_properties(PonyEngine.Surface.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.Surface.Impl PRIVATE
	PonyEngine.Surface
)
