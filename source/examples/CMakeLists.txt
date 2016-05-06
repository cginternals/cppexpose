
# Check if examples are enabled
if(NOT OPTION_BUILD_EXAMPLES)
    return()
endif()

# Example applications
add_subdirectory(types)
add_subdirectory(property)
add_subdirectory(scripting)
add_subdirectory(plugins)
add_subdirectory(example-plugins)
