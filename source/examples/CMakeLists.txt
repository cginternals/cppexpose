
# Check if examples are enabled
if(NOT OPTION_BUILD_EXAMPLES)
    return()
endif()

# Example plugins
add_subdirectory(example-plugins)

# Example applications
add_subdirectory(property)
add_subdirectory(scripting)
add_subdirectory(plugin)
add_subdirectory(parser)
add_subdirectory(type)
