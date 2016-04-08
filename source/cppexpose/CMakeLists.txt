
# 
# External dependencies
# 

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


# 
# Library name and options
# 

# Target name
set(target cppexpose)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(feature_file "include/${target}/${target}_features.h")
set(export_file  "include/${target}/${target}_api.h")
set(export_macro "${target_upper}_API")


# 
# Sources
# 

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/cppexpose.h

    ${include_path}/base/string_helpers.h
    ${include_path}/base/string_helpers.hpp
    ${include_path}/base/template_helpers.h
    ${include_path}/base/function_helpers.h
    ${include_path}/base/JSONReader.h
    ${include_path}/base/Serializer.h
    ${include_path}/base/SerializerJSON.h

    ${include_path}/typed/TypeInterface.h
    ${include_path}/typed/AbstractTyped.h
    ${include_path}/typed/AbstractTyped.hpp
    ${include_path}/typed/TypeSelector.h
    ${include_path}/typed/Typed.h
    ${include_path}/typed/Typed.hpp
    ${include_path}/typed/TypedGeneric.h
    ${include_path}/typed/TypedGeneric.hpp
    ${include_path}/typed/TypedBool.h
    ${include_path}/typed/TypedBool.hpp
    ${include_path}/typed/TypedString.h
    ${include_path}/typed/TypedString.hpp
    ${include_path}/typed/TypedNumber.h
    ${include_path}/typed/TypedNumber.hpp
    ${include_path}/typed/TypedSignedIntegral.h
    ${include_path}/typed/TypedSignedIntegral.hpp
    ${include_path}/typed/TypedUnsignedIntegral.h
    ${include_path}/typed/TypedUnsignedIntegral.hpp
    ${include_path}/typed/TypedFloatingPoint.h
    ${include_path}/typed/TypedFloatingPoint.hpp
    ${include_path}/typed/TypedEnum.h
    ${include_path}/typed/TypedEnum.hpp
    ${include_path}/typed/TypedArray.h
    ${include_path}/typed/TypedArray.h
    ${include_path}/typed/TypedVariant.hpp
    ${include_path}/typed/TypedVariant.hpp
    ${include_path}/typed/DirectValue.h
    ${include_path}/typed/DirectValue.hpp
    ${include_path}/typed/DirectValueSingle.h
    ${include_path}/typed/DirectValueSingle.hpp
    ${include_path}/typed/DirectValueArray.h
    ${include_path}/typed/DirectValueArray.hpp
    ${include_path}/typed/StoredValueSingle.h
    ${include_path}/typed/StoredValueSingle.hpp
    ${include_path}/typed/StoredValueArray.h
    ${include_path}/typed/StoredValueArray.hpp

    ${include_path}/function/AbstractFunction.h
    ${include_path}/function/Function.h
    ${include_path}/function/Function.hpp
    ${include_path}/function/Method.h
    ${include_path}/function/Method.hpp

    ${include_path}/variant/Variant.h
    ${include_path}/variant/Variant.hpp

    ${include_path}/reflection/Object.h
    ${include_path}/reflection/Named.h
    ${include_path}/reflection/AbstractProperty.h
    ${include_path}/reflection/PropertyGroup.h
    ${include_path}/reflection/Property.h
    ${include_path}/reflection/Property.hpp
)

set(sources
    ${source_path}/cppexpose.cpp

    ${source_path}/base/string_helpers.cpp
    ${source_path}/base/JSONReader.cpp
    ${source_path}/base/Serializer.cpp
    ${source_path}/base/SerializerJSON.cpp

    ${source_path}/typed/TypeInterface.cpp
    ${source_path}/typed/AbstractTyped.cpp

    ${source_path}/function/AbstractFunction.cpp

    ${source_path}/variant/Variant.cpp

    ${source_path}/reflection/Object.cpp
    ${source_path}/reflection/Named.cpp
    ${source_path}/reflection/AbstractProperty.cpp
    ${source_path}/reflection/PropertyGroup.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
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
        PREFIX ${target_upper}
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

    PUBLIC
    ${DEFAULT_LIBRARIES}

    INTERFACE
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    $<$<BOOL:${OPTION_BUILD_WITH_STD_REGEX}>:USE_STD_REGEX>

    PUBLIC
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_upper}_STATIC_DEFINE>
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
