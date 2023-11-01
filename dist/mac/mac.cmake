find_program(DEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")

set(INSTALL_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/dist/mac)
set(CPACK_GENERATOR "DragNDrop")

set_target_properties(skvm PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.github.skvm
    MACOSX_BUNDLE_ICON_FILE skvm.icns
    MACOSX_BUNDLE TRUE
)

configure_file("${INSTALL_SCRIPTS}/dependencies.cmake.in" "${INSTALL_SCRIPTS}/dependencies.cmake" @ONLY)
set(CPACK_PRE_BUILD_SCRIPTS ${INSTALL_SCRIPTS}/dependencies.cmake)
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/pack")
set(CPACK_BUNDLE_ICON ${APP_ICON_MACOSX})

include(CPACK)
