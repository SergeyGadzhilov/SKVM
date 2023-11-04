#
# Installers
#
if(APPLE)
    include(dist/mac/install.cmake)
endif()

if(WIN32)
   install(TARGETS skvm skvmc skvms
        BUNDLE DESTINATION . COMPONENT "SKVM"
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
    )
   install(FILES ${OPENSSL_COMPONENTS} DESTINATION bin COMPONENT "SKVM")
   install(TARGETS skvmd COMPONENT "SKVM")
   include(dist/win/win.cmake)
endif()

if(UNIX AND NOT APPLE)
    install(TARGETS skvm skvmc skvms
        BUNDLE DESTINATION . COMPONENT "SKVM"
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
    )
    include(dist/linux/linux.cmake)
endif()
