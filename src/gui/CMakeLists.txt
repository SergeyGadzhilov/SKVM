cmake_minimum_required (VERSION 3.4)

find_package (QT NAMES Qt6 Qt5 REQUIRED)
find_package (Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Network LinguistTools REQUIRED)
# If Qt6 is in use, also link to Core5Compat
if (Qt6_FOUND)
    find_package (Qt6 REQUIRED COMPONENTS Core5Compat)
endif()

message(STATUS "Using Qt" ${QT_VERSION_MAJOR})


set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# files that are used both in tests and the app
set(GUI_COMMON_SOURCE_FILES
    src/Action.cpp
    src/Hotkey.cpp
    src/KeySequence.cpp
)

set(GUI_COMMON_HEADER_FILES
    src/Action.h
    src/Hotkey.h
    src/KeySequence.h
)

set(GUI_SOURCE_FILES
    src/AboutDialog.cpp
    src/ActionDialog.cpp
    src/AddClientDialog.cpp
    src/AppConfig.cpp
    src/AppLocale.cpp
    src/BaseConfig.cpp
    src/CommandProcess.cpp
    src/DisplayIsValid.cpp
    src/FingerprintAcceptDialog.cpp
    src/HotkeyDialog.cpp
    src/IpcClient.cpp
    src/Ipc.cpp
    src/IpcReader.cpp
    src/KeySequenceWidget.cpp
    src/LogWindow.cpp
    src/main.cpp
    src/MainWindow.cpp
    src/NewScreenWidget.cpp
    src/QSKVMApplication.cpp
    src/QUtility.cpp
    src/Screen.cpp
    src/ScreenSettingsDialog.cpp
    src/ScreenSetupModel.cpp
    src/ScreenSetupView.cpp
    src/ServerConfig.cpp
    src/ServerConfigDialog.cpp
    src/SettingsDialog.cpp
    src/SslCertificate.cpp
    src/TrashScreenWidget.cpp
    src/widgets/Sidebar.cpp
    src/updater/Version.cpp
    src/updater/Updater.cpp
    src/widgets/StatusBar.cpp
    src/widgets/Notifications.cpp
    src/widgets/notifications/Title.cpp
    src/widgets/notifications/NewVersionNotification.cpp
)

set(GUI_HEADER_FILES
    src/AboutDialog.h
    src/ActionDialog.h
    src/AddClientDialog.h
    src/AppConfig.h
    src/AppConnectionState.h
    src/AppLocale.h
    src/BaseConfig.h
    src/CommandProcess.h
    src/DisplayIsValid.h
    src/ElevateMode.h
    src/HotkeyDialog.h
    src/IpcClient.h
    src/Ipc.h
    src/IpcReader.h
    src/KeySequenceWidget.h
    src/LogWindow.h
    src/MainWindow.h
    src/NewScreenWidget.h
    src/ProcessorArch.h
    src/QSKVMApplication.h
    src/QUtility.h
    src/Screen.h
    src/ScreenSettingsDialog.h
    src/ScreenSetupModel.h
    src/ScreenSetupView.h
    src/ServerConfigDialog.h
    src/ServerConfig.h
    src/SettingsDialog.h
    src/SslCertificate.h
    src/TrashScreenWidget.h
    src/widgets/Sidebar.h
    src/updater/Version.h
    src/updater/Updater.h
    src/widgets/StatusBar.h
    src/widgets/Notifications.h
    src/widgets/notifications/Title.h
    src/widgets/notifications/NewVersionNotification.h
)

set(GUI_UI_FILES
    src/AboutDialogBase.ui
    src/ActionDialogBase.ui
    src/AddClientDialogBase.ui
    src/FingerprintAcceptDialog.ui
    src/HotkeyDialogBase.ui
    src/LogWindowBase.ui
    src/MainWindowBase.ui
    src/ScreenSettingsDialogBase.ui
    src/ServerConfigDialogBase.ui
    src/SettingsDialogBase.ui
)

set(TS_FILES
    res/lang/gui_af-ZA.ts
    res/lang/gui_ar.ts
    res/lang/gui_bg-BG.ts
    res/lang/gui_ca-AD.ts
    res/lang/gui_cs-CZ.ts
    res/lang/gui_cy.ts
    res/lang/gui_da.ts
    res/lang/gui_de.ts
    res/lang/gui_es.ts
    res/lang/gui_et-EE.ts
    res/lang/gui_fi.ts
    res/lang/gui_fr.ts
    res/lang/gui_gl.ts
    res/lang/gui_grk.ts
    res/lang/gui_he.ts
    res/lang/gui_hi.ts
    res/lang/gui_hr-HR.ts
    res/lang/gui_hu-HU.ts
    res/lang/gui_id.ts
    res/lang/gui_is-IS.ts
    res/lang/gui_it.ts
    res/lang/gui_ja-JP.ts
    res/lang/gui_ko.ts
    res/lang/gui_lt.ts
    res/lang/gui_lv.ts
    res/lang/gui_mr.ts
    res/lang/gui_nl-NL.ts
    res/lang/gui_no.ts
    res/lang/gui_pes-IR.ts
    res/lang/gui_pl-PL.ts
    res/lang/gui_pt-BR.ts
    res/lang/gui_pt-PT.ts
    res/lang/gui_ro.ts
    res/lang/gui_ru.ts
    res/lang/gui_si.ts
    res/lang/gui_sk-SK.ts
    res/lang/gui_sl-SI.ts
    res/lang/gui_sq-AL.ts
    res/lang/gui_sr.ts
    res/lang/gui_sv.ts
    res/lang/gui_th-TH.ts
    res/lang/gui_tr-TR.ts
    res/lang/gui_uk.ts
    res/lang/gui_ur.ts
    res/lang/gui_vi.ts
    res/lang/gui_zh-CN.ts
    res/lang/gui_zh-TW.ts
)

set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/res/lang")
if (Qt5_FOUND)
    qt5_add_translation(QM_FILES ${TS_FILES} OPTIONS -silent)
else()
    qt_add_translation(QM_FILES ${TS_FILES} OPTIONS -silent)
endif()

# The following file includes X11 headers that later break Qt headers.
set_source_files_properties("src/DisplayIsValid.cpp" PROPERTIES SKIP_UNITY_BUILD_INCLUSION TRUE)

if (WIN32)
    set (GUI_RC_FILES res/win/SKVM.rc)
    set_property(SOURCE res/win/SKVM.rc PROPERTY COMPILE_FLAGS /nologo)
endif()

add_executable (skvm WIN32
    ${GUI_COMMON_SOURCE_FILES}
    ${GUI_COMMON_HEADER_FILES}
    ${GUI_SOURCE_FILES}
    ${GUI_HEADER_FILES}
    ${GUI_UI_FILES}
    ${GUI_RC_FILES}
    res/SKVM.qrc
)

include_directories (./src)
include_directories (./src/widgets)

target_link_libraries(skvm
    net
    arch
    base
    io
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

if (Qt6_FOUND)
    target_link_libraries(skvm Qt6::Core5Compat)
endif()
target_link_libraries(skvm ${OPENSSL_LIBS})
target_compile_definitions (skvm PRIVATE -DSKVM_REVISION="${SKVM_REVISION}")
target_link_libraries (skvm common)

if(SKVM_BUILD_TESTS)
    set(GUI_TEST_SOURCE_FILES
        test/KeySequenceTests.cpp
        test/HotkeyTests.cpp
        test/main.cpp
    )

    add_executable(guiunittests
        ${GUI_TEST_SOURCE_FILES}
        ${GUI_COMMON_SOURCE_FILES}
        ${GUI_COMMON_HEADER_FILES}
    )

    add_test(NAME guiunittests
             COMMAND guiunittests
             WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    target_include_directories(guiunittests PUBLIC ../../ext)
    target_link_libraries(guiunittests gtest gmock Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ${libs})
endif()
