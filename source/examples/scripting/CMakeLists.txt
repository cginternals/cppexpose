
#
# External dependencies
#

find_package(cppassist REQUIRED)


#
# Executable name and options
#

# Target name
set(target scripting-example)

# Exit here if required dependencies are not met
message(STATUS "Example ${target}")


#
# Sources
#

set(sources
    linenoise-ng/ConvertUTF.h
    linenoise-ng/ConvertUTF.cpp
    linenoise-ng/wcwidth.cpp
    linenoise-ng/linenoise.h
    linenoise-ng/linenoise.cpp

    main.cpp
    MyObject.cpp
    MyObject.h
    TreeNode.cpp
    TreeNode.h
)


#
# Create executable
#

# Build executable
add_executable(${target}
    MACOSX_BUNDLE
    ${sources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/source/include
)


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    cppassist::cppassist
    ${META_PROJECT_NAME}::cppexpose
    ${META_PROJECT_NAME}::cppexpose-script
    ${META_PROJECT_NAME}::cppexpose-js
)


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


#
# Compile options
#

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)


#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
)


#
# Deployment
#

# Executable
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT examples
    BUNDLE  DESTINATION ${INSTALL_BIN} COMPONENT examples
)
