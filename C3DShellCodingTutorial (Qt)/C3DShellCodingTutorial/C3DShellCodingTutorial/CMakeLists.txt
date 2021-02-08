cmake_minimum_required(VERSION 3.15)
project(C3DShellCodingTutorial)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-DQSCINTILLA_DLL)
# Setup AUTO UI Compile
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FILES_UI
  ./mainwindow/ui
  ./textedit/ui
)
set( CMAKE_AUTOUIC_SEARCH_PATHS ${FILES_UI})

set(CPPCODEBUILDER_SRC
  ./cppcodebuilder/worker.cpp
  ./cppcodebuilder/cppcodebuilder.cpp
  ./cppcodebuilder/consoletext.cpp
  ./cppcodebuilder/worker.h
  ./cppcodebuilder/cppcodebuilder.h
  ./cppcodebuilder/consoletext.h
)

set(DOCUMENTATION_SRC
  ./documentation/documentationwidget.cpp
  ./documentation/documentationwidget.h
  ./documentation/documentationpackage.cpp
  ./documentation/documentationpackage.h
)

set(MAINWINDOW_SRC
  ./mainwindow/mainwindow.cpp
  ./mainwindow/welcomewidget.cpp
  ./mainwindow/compilersearch.cpp
  ./mainwindow/mainwindow.h
  ./mainwindow/welcomewidget.h
  ./mainwindow/compilersearch.h
  ./mainwindow/ui/mainwindow.ui
  ./mainwindow/ui/welcomewidget.ui
  ./mainwindow/ui/compilersearch.ui
  ./mainwindow/storagelocation.cpp
  ./mainwindow/storagelocation.h
)

set(SCENE_SRC
  ./scene/visionscene.cpp
  ./scene/colorbutton.cpp
  ./scene/visionscene.h
  ./scene/colorbutton.h
)

set(TEXTEDIT_SRC
  ./textedit/lexercxx.cpp
  ./textedit/findtextwidget.cpp
  ./textedit/texteditwidget.cpp
  ./textedit/texteditmanager.cpp
  ./textedit/texteditor.cpp
  ./textedit/lexercxx.h
  ./textedit/findtextwidget.h
  ./textedit/texteditwidget.h
  ./textedit/texteditmanager.h
  ./textedit/texteditor.h

  ./textedit/ui/findtextwidget.ui
  ./textedit/ui/texteditwidget.ui
)

set(TUTORIAL_SRC
  ./tutorial/tutorialloader.cpp
  ./tutorial/tutorialloader.h
  ./tutorial/tutorialgallerywidget.cpp
  ./tutorial/tutorialgallerywidget.h
  ./tutorial/tutorialwidget.cpp
  ./tutorial/tutorialwidget.h
  ./tutorial/tutorialpackage.cpp
  ./tutorial/tutorialpackage.h
  ./tutorial/tutorialwebpage.cpp
  ./tutorial/tutorialwebpage.h
)

set(WEBVIEWER_SRC 
  ./webviewer/webviewwidget.cpp
  ./webviewer/webpage.cpp
  ./webviewer/webview.cpp
  ./webviewer/webviewwidget.h
  ./webviewer/webpage.h
  ./webviewer/webview.h
)

set(PDFREADER_SRC
  ./pdfreader/pdfreaderwidget.cpp
  ./pdfreader/pdfreaderwidget.h
  ./pdfreader/pdfpackage.cpp
  ./pdfreader/pdfpackage.h
  ./pdfreader/pdflistwidget.cpp
  ./pdfreader/pdflistwidget.h
)
set (MAIN_SRC
  ./main.cpp
  ./globaldef.h
)

file(GLOB_RECURSE RESOURCE_FILES ./res/*)


set(SRC_C3DShellCodingTutorial
  ${WEBVIEWER_SRC}
  ${TUTORIAL_SRC}
  ${TEXTEDIT_SRC}
  ${SCENE_SRC}
  ${MAINWINDOW_SRC}
  ${DOCUMENTATION_SRC}
  ${CPPCODEBUILDER_SRC}
  ${PDFREADER_SRC}
  ${MAIN_SRC}


  ./res/resources.qrc
  ./res/themes/breeze_themes.qrc
)
 
#set(TS_FILES
#  ./translations/english.ts
#  ./translations/russian.ts
#)

#qt5_create_translation(QM_FILES ${SRC_C3DShellCodingTutorial} ${TS_FILES})

add_executable(
    ${C3DShellCodingTutorial_OUTPUT}
    WIN32
    ${SRC_C3DShellCodingTutorial}
#    ${QM_FILES}
)
 
target_link_libraries( ${C3DShellCodingTutorial_OUTPUT}
  ${Vision_OUTPUT}
  ${QtVision_OUTPUT}
  ${Math_OUTPUT}
  ${QScintilla_OUTPUT}
  ${QtAdvancedDocking_OUTPUT}
  Qt5::Core
  Qt5::Gui
  Qt5::OpenGL
  Qt5::Widgets
  Qt5::WebEngineWidgets
  Qt5::Xml
)

include_directories(
  ${Math_SOURCE_DIR}/Include
  ${Vision_SOURCE_DIR}/Include
  ${QtVision_SOURCE_DIR}/Include
  ${QScintilla_SOURCE_DIR}/Include
  ${QtAdvancedDocking_SOURCE_DIR}/Include
  ./cppcodebuilder
  ./documentation
  ./mainwindow
  ./scene
  ./textedit
  ./tutorial
  ./webviewer
  ./pdfreader
)

#set(QT5_DLLS "Qt5::Core Qt5::Gui Qt5::OpenGL Qt5::Widgets Qt5::WebEngineWidgets Qt5::Xml")
#add_custom_command(
#  TARGET ${C3DSandbox_OUTPUT}
#  POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different
#  $<TARGET_FILES:${QT5_DLLS}>
#  $<TARGET_FILE_DIR:${C3DSandbox_OUTPUT}>
# )

#set_target_properties(${C3DSandbox_OUTPUT} PROPERTIES
#  RESOURCE "${RESOURCE_FILES}"
#)

# For IDE
source_group("" FILES ${CPPCODEBUILDER_SRC})
source_group("" FILES ${DOCUMENTATION_SRC})
source_group("" FILES ${MAINWINDOW_SRC})
source_group("" FILES ${SCENE_SRC})
source_group("" FILES ${TEXTEDIT_SRC})
source_group("" FILES ${TUTORIAL_SRC})
source_group("" FILES ${WEBVIEWER_SRC})
source_group("" FILES ${PDFREADER_SRC})
source_group("" FILES ${MAIN_SRC})
source_group("" FILES ${RESOURCE_FILES})