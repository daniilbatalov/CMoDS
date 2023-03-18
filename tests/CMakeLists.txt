# Generated from tests.pro.

cmake_minimum_required(VERSION 3.16)
project(tests VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

qt_add_executable(tests WIN32 MACOSX_BUNDLE
    ../libs/aux/math_aux.h
    ../libs/gronsfeld.cpp ../libs/gronsfeld.h
    ../libs/perms.cpp ../libs/perms.h
    ../libs/subcipher.cpp ../libs/subcipher.h
    ../libs/vigenere.cpp ../libs/vigenere.h
    Gronsfeld/tst_gronsfeld.cpp Gronsfeld/tst_gronsfeld.h
    MathAux/tst_mathaux.cpp MathAux/tst_mathaux.h
    Perms/tst_perms.cpp Perms/tst_perms.h
    Subcipher/tst_subcipher.cpp Subcipher/tst_subcipher.h
    Vigenere/tst_vigenere.cpp Vigenere/tst_vigenere.h
    tst_tests.cpp
)
target_link_libraries(tests PUBLIC
    Qt::Core
    Qt::Test
)

#target_compile_options(tests
#    --coverage
#    -fprofile-arcs
#    -ftest-coverage
#)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -fprofile-arcs -ftest-coverage")

install(TARGETS tests
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
