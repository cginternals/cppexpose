
# 
# Executable name and options
# 

# Target name
set(target cppexpose-test)
message(STATUS "Test ${target}")


# Generate Property Instanciation Tests
set(testdir ${CMAKE_SOURCE_DIR}/source/tests/cppexpose-test)
set(filelist ${testdir}/instanciationTestsFiles.txt)
add_custom_target("generatePropertyTests" COMMAND python ${testdir}/generateInstanciationTests.py ${testdir} ${filelist})


# 
# Sources
# 

set(sources
    main.cpp
    variantTest.cpp
)

#
# Add generated instanciation tests to sources
#
if(EXISTS ${filelist})
    FILE(READ ${filelist} contents)
    STRING(REGEX REPLACE ";" "\\\\;" contents "${contents}")
    STRING(REGEX REPLACE "\n" ";" contents "${contents}")
    set(sources
        ${sources}
        ${contents}
    )
endif()


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
    ${META_PROJECT_NAME}::cppexpose
    gmock-dev
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
