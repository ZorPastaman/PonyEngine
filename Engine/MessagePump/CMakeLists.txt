message(STATUS "Configuring PonyEngine.MessagePump")

message(VERBOSE "Configuring target")
add_library(PonyEngine.MessagePump STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.MessagePump PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/MessagePump.cppm"
	"Source/Public/MessagePump-IPumpService.cppm"
	"Source/Public/MessagePump-PumpFeature.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.MessagePump PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.MessagePump PRIVATE
	PonyEngine.Core
)
