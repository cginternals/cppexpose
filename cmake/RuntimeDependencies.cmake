
# 
# Default dependencies for the runtime-package
# 

# Install 3rd-party runtime dependencies into runtime-component
# install(FILES ... COMPONENT runtime)


# 
# Full dependencies for self-contained packages
# 

if(OPTION_SELF_CONTAINED)

    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")

        # Install 3rd-party runtime dependencies into runtime-component
        # install(FILES ... COMPONENT runtime)

        find_file(DLLS_CPPASSIST cppassist.dll)
        find_file(DLLS_CPPLCOATE cpplocate.dll)
        find_file(DLLS_CPPFS cppfs.dll)

        set(DLLS
            ${DLLS_CPPASSIST}
            ${DLLS_CPPLCOATE}
            ${DLLS_CPPFS}
        )
        set(PLATFORMS
            ${DLLS_WIN}
        )
        install(FILES ${DLLS} DESTINATION ${INSTALL_BIN} COMPONENT runtime)
        install(FILES ${PLATFORMS} DESTINATION ${INSTALL_BIN}/platforms COMPONENT runtime)

    endif()

endif()
