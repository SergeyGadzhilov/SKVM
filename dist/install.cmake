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
    include(dist/linux/install.cmake)
endif()
