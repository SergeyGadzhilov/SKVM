#
# Installers
#
install(TARGETS skvm skvmc skvms
    BUNDLE DESTINATION . COMPONENT "SKVM"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM")

install(FILES ${OPENSSL_COMPONENTS} DESTINATION bin COMPONENT "SKVM")

if(APPLE)
    include(dist/mac/mac.cmake)
endif()

if(WIN32)
   install(TARGETS skvmd COMPONENT "SKVM")
   include(dist/win/win.cmake)
endif()

if(UNIX AND NOT APPLE)
    include(dist/linux/linux.cmake)
endif()
