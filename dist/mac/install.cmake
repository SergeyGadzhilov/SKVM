set_target_properties(skvm PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.github.skvm
    MACOSX_BUNDLE_ICON_FILE skvm.icns
    MACOSX_BUNDLE TRUE
)

install(TARGETS skvm
    BUNDLE DESTINATION . COMPONENT "SKVM"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
    RUNTIME DESTINATION . COMPONENT "SKVM"
)

install(TARGETS skvmc skvms DESTINATION ./skvm.app/Contents/MacOS COMPONENT "SKVM")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/dist/mac/skvm.icns" DESTINATION ./skvm.app/Contents/Resources COMPONENT "SKVM")

include(dist/mac/pack.cmake)
