# Adds a manifest to the application
# path - path to a manifest.
function(pony_add_winapi_manifest path)
	target_sources(PonyEngine.Application.Impl PRIVATE "${path}")
endfunction()
