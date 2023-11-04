set(SKVM_NAME "SKVM")
set(SKVM_DESCRIPTION "SKVM  is software that mimics the functionality of a KVM switch")
set(SKVM_PACKAGE_TYPE "deb" CACHE STRING "Linux package rpm or deb")

if(${SKVM_PACKAGE_TYPE} MATCHES "rpm")
    set(CPACK_GENERATOR "RPM")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${SKVM_NAME})
    set(CPACK_RPM_PACKAGE_NAME ${SKVM_NAME})
    set(CPACK_RPM_PACKAGE_DESCRIPTION ${SKVM_DESCRIPTION})
    set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION
       /usr/share/applications;
       /usr/share/icons;
       /usr/share/icons/hicolor;
       /usr/share/icons/hicolor/scalable;
       /usr/share/icons/hicolor/scalable/apps
    )
else()
    set(CPACK_GENERATOR "DEB")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${SKVM_NAME})
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${SKVM_DESCRIPTION})
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "gadzhilov.sergey@gmail.com")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
endif()

include(CPack)
