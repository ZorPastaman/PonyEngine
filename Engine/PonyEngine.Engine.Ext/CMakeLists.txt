message(STATUS "Configuring PonyEngine.Engine.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Engine.Ext STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Engine.Ext PROPERTIES CXX_STANDARD 23)
set_target_properties(PonyEngine.Engine.Ext PROPERTIES OUTPUT_NAME "PonyEngine.Engine.Extension")

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Engine.Ext PRIVATE
	PonyEngine.Core
)
