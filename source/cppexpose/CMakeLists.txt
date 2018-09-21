
#
# External dependencies
#

find_package(cpplocate REQUIRED)
find_package(cppassist REQUIRED)

set(ADDITIONAL_LIBRARIES)
set(ADDITIONAL_INCLUDES)

if(NOT OPTION_BUILD_WITH_STD_REGEX)
    find_package(Boost COMPONENTS regex REQUIRED)

    if (Boost_FOUND)
        message(STATUS "Use Boost for regex.")

        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} ${Boost_LIBRARIES})
        set(ADDITIONAL_INCLUDES ${ADDITIONAL_INCLUDES} ${Boost_INCLUDE_DIRS})
    else()
        message(WARNING "OPTION_BUILD_WITH_STD_REGEX is set to Off: Boost not found.")
        message(WARNING "Defaulting to C++11 regex.")
    endif()
endif()

if(UNIX)
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} dl)
endif()


#
# Library name and options
#

# Target name
set(target cppexpose)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(MAKE_C_IDENTIFIER ${target} target_id)
string(TOUPPER ${target_id} target_id)
set(feature_file         "include/${target}/${target}_features.h")
set(export_file          "include/${target}/${target}_export.h")
set(template_export_file "include/${target}/${target}_api.h")
set(export_macro         "${target_id}_API")


#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/cppexpose.h
    ${include_path}/ordered_includes.h

    ${include_path}/function_helpers.h
    ${include_path}/template_helpers.h
    ${include_path}/GetTyped.h

    ${include_path}/AbstractTyped.h
    ${include_path}/AbstractTyped.hh
    ${include_path}/AbstractTyped.inl
    ${include_path}/AbstractTypedNumber.h
    ${include_path}/AbstractTypedNumber.hh
    ${include_path}/AbstractTypedNumber.inl
    ${include_path}/AbstractVar.h
    ${include_path}/AbstractVar.hh
    ${include_path}/Array.h
    ${include_path}/Array.hh
    ${include_path}/Array.inl
    ${include_path}/Object.h
    ${include_path}/Object.hh
    ${include_path}/Object.inl
    ${include_path}/PropertyContainer.h
    ${include_path}/PropertyContainer.hh
    ${include_path}/TypedArray.h
    ${include_path}/TypedArray.hh
    ${include_path}/TypedArray.inl
    ${include_path}/TypedArrayPointer.h
    ${include_path}/TypedArrayPointer.hh
    ${include_path}/TypedArrayPointer.inl
    ${include_path}/TypedBool.h
    ${include_path}/TypedBool.hh
    ${include_path}/TypedBool.inl
    ${include_path}/TypedEnum.h
    ${include_path}/TypedEnum.hh
    ${include_path}/TypedEnum.inl
    ${include_path}/TypedFloatingPoint.h
    ${include_path}/TypedFloatingPoint.hh
    ${include_path}/TypedFloatingPoint.inl
    ${include_path}/TypedFunction.h
    ${include_path}/TypedFunction.hh
    ${include_path}/TypedFunction.inl
    ${include_path}/TypedGeneric.h
    ${include_path}/TypedGeneric.hh
    ${include_path}/TypedGeneric.inl
    ${include_path}/TypedObjectPointer.h
    ${include_path}/TypedObjectPointer.hh
    ${include_path}/TypedObjectPointer.inl
    ${include_path}/TypedPointer.h
    ${include_path}/TypedPointer.hh
    ${include_path}/TypedPointer.inl
    ${include_path}/TypedSignedIntegral.h
    ${include_path}/TypedSignedIntegral.hh
    ${include_path}/TypedSignedIntegral.inl
    ${include_path}/TypedString.h
    ${include_path}/TypedString.hh
    ${include_path}/TypedString.inl
    ${include_path}/TypedUnsignedIntegral.h
    ${include_path}/TypedUnsignedIntegral.hh
    ${include_path}/TypedUnsignedIntegral.inl
    ${include_path}/ValueStorage.h
    ${include_path}/ValueStorage.hh
    ${include_path}/ValueStorage.inl
    ${include_path}/Var.h
    ${include_path}/Var.hh
    ${include_path}/Var.inl
    ${include_path}/Variant.h
    ${include_path}/Variant.hh
    ${include_path}/Variant.inl
    ${include_path}/VarType.h

    ${include_path}/Function.h
    ${include_path}/AbstractFunction.h
    ${include_path}/StaticFunction.h
    ${include_path}/StaticFunction.inl
    ${include_path}/MemberFunction.h
    ${include_path}/MemberFunction.inl
    ${include_path}/ConstMemberFunction.h
    ${include_path}/ConstMemberFunction.inl

    ${include_path}/AbstractSignal.h
    ${include_path}/Connection.h
    ${include_path}/ScopedConnection.h
    ${include_path}/Signal.h
    ${include_path}/Signal.inl

    ${include_path}/JSON.h
)

set(sources
    ${source_path}/cppexpose.cpp

    ${source_path}/AbstractVar.cpp
    ${source_path}/Array.cpp
    ${source_path}/Object.cpp
    ${source_path}/PropertyContainer.cpp
    ${source_path}/Variant.cpp

    ${source_path}/Function.cpp
    ${source_path}/AbstractFunction.cpp

    ${source_path}/AbstractSignal.cpp
    ${source_path}/Connection.cpp
    ${source_path}/ScopedConnection.cpp

    ${source_path}/JSON.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hh$|\\\\.inl$"
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.inl$"
    ${source_group} ${sources})


#
# Create library
#

# Build library
add_library(${target}
    ${sources}
    ${headers}
)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create feature detection header
# Compilers: https://cmake.org/cmake/help/v3.1/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE_%3CLANG%3E_COMPILER_ID
# Feature: https://cmake.org/cmake/help/v3.1/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html

# Check for availability of module; use pre-generated version if not found
if (WriterCompilerDetectionHeaderFound)
    write_compiler_detection_header(
        FILE ${feature_file}
        PREFIX ${target_id}
        COMPILERS AppleClang Clang GNU MSVC
        FEATURES cxx_alignas cxx_alignof cxx_constexpr cxx_final cxx_noexcept cxx_nullptr cxx_sizeof_member cxx_thread_local
        VERSION 3.2
    )
else()
    file(
        COPY ${PROJECT_SOURCE_DIR}/codegeneration/${target}_features.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/${target}
        USE_SOURCE_PERMISSIONS
    )
endif()

# Create API export header
generate_export_header(${target}
    EXPORT_FILE_NAME  ${export_file}
    EXPORT_MACRO_NAME ${export_macro}
)

generate_template_export_header(${target}
    ${target_id}
    ${template_export_file}
)


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
    VERSION ${META_VERSION}
    SOVERSION ${META_VERSION_MAJOR}
)


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${ADDITIONAL_INCLUDES}

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE
    ${ADDITIONAL_LIBRARIES}
    cpplocate::cpplocate

    PUBLIC
    ${DEFAULT_LIBRARIES}
    cppassist::cppassist

    INTERFACE
)


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE
    $<$<BOOL:${OPTION_BUILD_WITH_STD_REGEX}>:USE_STD_REGEX>

    PUBLIC
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_id}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


#
# Compile options
#

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)


#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
    ${headers}
)


#
# Deployment
#

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
