message(STATUS "Configuring PonyEngine.Surface.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface.Impl STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.Surface.Impl PRIVATE
	PonyEngine.Surface
)
