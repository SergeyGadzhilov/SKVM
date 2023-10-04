#
# Installers
#
install(TARGETS skvm skvmc skvms skvmd
    BUNDLE DESTINATION . COMPONENT "SKVM"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM")

if(APPLE)
    include(dist/mac/mac.cmake)
endif()

if(WIN32)
    include(dist/win/win.cmake)
endif()

if(UNIX AND NOT APPLE)
    include(dist/linux/linux.cmake)
endif()
