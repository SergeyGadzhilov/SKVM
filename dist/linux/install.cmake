install(TARGETS skvm skvmc skvms
    BUNDLE DESTINATION . COMPONENT "SKVM"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT "SKVM"
)

install(FILES dist/linux/skvm.desktop DESTINATION share/applications)
install(FILES dist/linux/skvm.svg DESTINATION share/icons/hicolor/scalable/apps)
