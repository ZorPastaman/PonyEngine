message(STATUS "Configuring PonyEngine.MessagePump.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.MessagePump.Impl STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.MessagePump.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.MessagePump)
	message(FATAL_ERROR "PonyEngine.MessagePump wasn't configured")
endif()
target_link_libraries(PonyEngine.MessagePump.Impl PRIVATE
	PonyEngine.MessagePump
)
