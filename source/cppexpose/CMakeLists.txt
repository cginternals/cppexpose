
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

    ${include_path}/base/template_helpers.h
    ${include_path}/base/function_helpers.h
    ${include_path}/base/Tokenizer.h

    ${include_path}/json/JSON.h

    ${include_path}/signal/AbstractSignal.h
    ${include_path}/signal/Connection.h
    ${include_path}/signal/ScopedConnection.h
    ${include_path}/signal/Signal.h
    ${include_path}/signal/Signal.inl

    ${include_path}/type/AbstractBaseType.h
    ${include_path}/type/AbstractBaseType.hh
    ${include_path}/type/AbstractTyped.h
    ${include_path}/type/AbstractTyped.hh
    ${include_path}/type/AbstractTyped.inl
    ${include_path}/type/BaseType.h
    ${include_path}/type/BaseType.hh
    ${include_path}/type/BaseType.inl
    ${include_path}/type/BaseTypeImpl.h
    ${include_path}/type/BaseTypeImpl.hh
    ${include_path}/type/BaseTypeImpl.inl
    ${include_path}/type/BaseTypeImplArray.h
    ${include_path}/type/BaseTypeImplArray.hh
    ${include_path}/type/BaseTypeImplArray.inl
    ${include_path}/type/BaseTypeImplMap.h
    ${include_path}/type/BaseTypeImplMap.hh
    ${include_path}/type/BaseTypeImplMap.inl
    ${include_path}/type/BaseTypeImplBool.h
    ${include_path}/type/BaseTypeImplBool.hh
    ${include_path}/type/BaseTypeImplBool.inl
    ${include_path}/type/BaseTypeImplEnum.h
    ${include_path}/type/BaseTypeImplEnum.hh
    ${include_path}/type/BaseTypeImplEnum.inl
    ${include_path}/type/BaseTypeImplFloatingPoint.h
    ${include_path}/type/BaseTypeImplFloatingPoint.hh
    ${include_path}/type/BaseTypeImplFloatingPoint.inl
    ${include_path}/type/BaseTypeImplGeneric.h
    ${include_path}/type/BaseTypeImplGeneric.hh
    ${include_path}/type/BaseTypeImplGeneric.inl
    ${include_path}/type/BaseTypeImplNumber.h
    ${include_path}/type/BaseTypeImplNumber.hh
    ${include_path}/type/BaseTypeImplNumber.inl
    ${include_path}/type/BaseTypeImplPointer.h
    ${include_path}/type/BaseTypeImplPointer.hh
    ${include_path}/type/BaseTypeImplPointer.inl
    ${include_path}/type/BaseTypeImplSignedIntegral.h
    ${include_path}/type/BaseTypeImplSignedIntegral.hh
    ${include_path}/type/BaseTypeImplSignedIntegral.inl
    ${include_path}/type/BaseTypeImplString.h
    ${include_path}/type/BaseTypeImplString.hh
    ${include_path}/type/BaseTypeImplString.inl
    ${include_path}/type/BaseTypeImplUnsignedIntegral.h
    ${include_path}/type/BaseTypeImplUnsignedIntegral.hh
    ${include_path}/type/BaseTypeImplUnsignedIntegral.inl
    ${include_path}/type/BaseTypeImplVector.h
    ${include_path}/type/BaseTypeImplVector.hh
    ${include_path}/type/BaseTypeImplVector.inl
    ${include_path}/type/Converter.h
    ${include_path}/type/Converter.hh
    ${include_path}/type/Converter.inl
    ${include_path}/type/ConcreteType.h
    ${include_path}/type/ConcreteType.hh
    ${include_path}/type/ConcreteType.inl
    ${include_path}/type/EnumValues.h
    ${include_path}/type/EnumValues.hh
    ${include_path}/type/EnumValues.inl
    ${include_path}/type/GetType.h
    ${include_path}/type/GetType.hh
    ${include_path}/type/MetaType.h
    ${include_path}/type/MetaType.hh
    ${include_path}/type/NullType.h
    ${include_path}/type/NullType.hh
    ${include_path}/type/ObjectType.h
    ${include_path}/type/ObjectType.hh
    ${include_path}/type/Type.h
    ${include_path}/type/Type.hh
    ${include_path}/type/type_system.h

    ${include_path}/value/AbstractValueContainer.h
    ${include_path}/value/AbstractValueContainer.hh
    ${include_path}/value/AbstractValueContainer.inl
    ${include_path}/value/ValueContainer.h
    ${include_path}/value/ValueContainer.hh
    ${include_path}/value/ValueContainer.inl
    ${include_path}/value/ExternalValue.h
    ${include_path}/value/ExternalValue.hh
    ${include_path}/value/ExternalValue.inl
    ${include_path}/value/InternalValue.h
    ${include_path}/value/InternalValue.hh
    ${include_path}/value/InternalValue.inl

    ${include_path}/function/Function.h
    ${include_path}/function/AbstractFunction.h
    ${include_path}/function/StaticFunction.h
    ${include_path}/function/StaticFunction.inl
    ${include_path}/function/MemberFunction.h
    ${include_path}/function/MemberFunction.inl
    ${include_path}/function/ConstMemberFunction.h
    ${include_path}/function/ConstMemberFunction.inl

    ${include_path}/reflection/AbstractProperty.h
    ${include_path}/reflection/AbstractProperty.hh
    ${include_path}/reflection/Object.h
    ${include_path}/reflection/Object.hh
    ${include_path}/reflection/Object.inl
    ${include_path}/reflection/Property.h
    ${include_path}/reflection/Property.hh
    ${include_path}/reflection/Property.inl
    ${include_path}/reflection/Method.h
    ${include_path}/reflection/Variant.h
    ${include_path}/reflection/Variant.hh
    ${include_path}/reflection/Variant.inl
    ${include_path}/reflection/variant_helpers.h
    ${include_path}/reflection/variant_helpers.hh
    ${include_path}/reflection/variant_helpers.inl

    ${include_path}/scripting/ScriptContext.h
    ${include_path}/scripting/AbstractScriptBackend.h
#    ${include_path}/scripting/example/TreeNode.h

    ${include_path}/plugin/ComponentManager.h
    ${include_path}/plugin/ComponentManager.inl
    ${include_path}/plugin/ComponentRegistry.h
    ${include_path}/plugin/AbstractComponent.h
    ${include_path}/plugin/AbstractGenericComponent.h
    ${include_path}/plugin/AbstractGenericComponent.inl
    ${include_path}/plugin/GenericComponent.h
    ${include_path}/plugin/GenericComponent.inl
    ${include_path}/plugin/Component.h
    ${include_path}/plugin/Component.inl
    ${include_path}/plugin/PluginLibrary.h
#    ${include_path}/plugin/Example.h
)

set(sources
    ${source_path}/cppexpose.cpp

    ${source_path}/base/Tokenizer.cpp

    ${source_path}/json/JSON.cpp

    ${source_path}/signal/AbstractSignal.cpp
    ${source_path}/signal/Connection.cpp
    ${source_path}/signal/ScopedConnection.cpp

    ${source_path}/type/AbstractBaseType.cpp
    ${source_path}/type/AbstractTyped.cpp
    ${source_path}/type/Converter.cpp
    ${source_path}/type/MetaType.cpp
    ${source_path}/type/NullType.cpp
    ${source_path}/type/ObjectType.cpp
    ${source_path}/type/Type.cpp

    ${source_path}/value/AbstractValueContainer.cpp

    ${source_path}/function/Function.cpp
    ${source_path}/function/AbstractFunction.cpp

    ${source_path}/reflection/AbstractProperty.cpp
    ${source_path}/reflection/Object.cpp
    ${source_path}/reflection/Method.cpp
    ${source_path}/reflection/Variant.cpp

    ${source_path}/scripting/duktape-1.4.0/duktape.c
    ${source_path}/scripting/duktape-1.4.0/duktape.h
    ${source_path}/scripting/duktape-1.4.0/duk_config.h
#    ${source_path}/scripting/example/TreeNode.cpp
    ${source_path}/scripting/ScriptContext.cpp
    ${source_path}/scripting/AbstractScriptBackend.cpp
    ${source_path}/scripting/DuktapeScriptBackend.cpp
    ${source_path}/scripting/DuktapeScriptBackend.h
    ${source_path}/scripting/DuktapeScriptFunction.cpp
    ${source_path}/scripting/DuktapeScriptFunction.h
    ${source_path}/scripting/DuktapeObjectWrapper.cpp
    ${source_path}/scripting/DuktapeObjectWrapper.h

    ${source_path}/plugin/ComponentManager.cpp
    ${source_path}/plugin/ComponentRegistry.cpp
    ${source_path}/plugin/AbstractComponent.cpp
    ${source_path}/plugin/PluginLibrary.cpp
    ${source_path}/plugin/Example.cpp
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
