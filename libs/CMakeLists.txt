# Generated from libs.pro.

cmake_minimum_required(VERSION 3.16)
project(libs VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

qt_add_executable(libs WIN32 MACOSX_BUNDLE
    aux/math_aux.h
    gronsfeld.cpp gronsfeld.h
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    perms.cpp perms.h
    playfair.cpp playfair.h
    subcipher.cpp subcipher.h
    vigenere.cpp vigenere.h
)
target_link_libraries(libs PUBLIC
    Qt::Core
    Qt::Gui
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(libs PUBLIC
        Qt::Widgets
    )
endif()

install(TARGETS libs
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
