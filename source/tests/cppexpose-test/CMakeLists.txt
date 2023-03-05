
#
# External dependencies
#

find_package(cppassist REQUIRED)
find_package(${META_PROJECT_NAME} REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../")


# 
# Executable name and options
# 

# Target name
set(target cppexpose-test)
message(STATUS "Test ${target}")


# 
# Sources
# 

set(sources
    main.cpp
    VariantTest.cpp
    PropertyInstantiationTest.cpp
    PropertyTest.cpp
    DirectValueInstantiationTest.cpp
    DirectValueTest.cpp
    StoredValueInstantiationTest.cpp
    StoredValueTest.cpp
)

# 
# Create executable
# 

# Build executable
add_executable(${target}
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
    googletest::googletest
    cppassist::cppassist
    ${META_PROJECT_NAME}::cppexpose
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

# MSVC compiler options
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    set(TARGET_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
    PRIVATE
        /bigobj

    PUBLIC
    )
endif ()

target_compile_options(${target}
    PRIVATE
    ${TARGET_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
