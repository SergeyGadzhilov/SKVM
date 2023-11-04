#
# Packages
#
SET(CPACK_PACKAGE_VERSION_MAJOR ${SKVM_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${SKVM_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${SKVM_VERSION_PATCH})

if(APPLE)
    include(dist/mac/pack.cmake)
endif()

if(WIN32)
   include(dist/win/pack.cmake)
endif()

if(UNIX AND NOT APPLE)
    include(dist/linux/pack.cmake)
endif()
