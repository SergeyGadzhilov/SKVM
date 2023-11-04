#
# Installers
#
if(APPLE)
    include(dist/mac/install.cmake)
endif()

if(WIN32)
   include(dist/win/install.cmake)
endif()

if(UNIX AND NOT APPLE)
    install(TARGETS skvm skvmc skvms
        BUNDLE DESTINATION . COMPONENT "SKVM"
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
    )
    include(dist/linux/install.cmake)
endif()
