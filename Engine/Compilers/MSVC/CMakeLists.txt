message(STATUS "Configuring PonyCompiler for MSVC")

add_library(PonyCompiler INTERFACE)

target_include_directories(PonyCompiler INTERFACE 
	"Include/Public"
)
