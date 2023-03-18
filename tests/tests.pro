QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += --coverage -fprofile-arcs -ftest-coverage
QMAKE_LFLAGS += --coverage -fprofile-arcs -ftest-coverage

SOURCES +=  tst_tests.cpp \
    Gronsfeld/tst_gronsfeld.cpp \
    MathAux/tst_mathaux.cpp \
    Perms/tst_perms.cpp \
    Subcipher/tst_subcipher.cpp \
    Vigenere/tst_vigenere.cpp \
    ../libs/subcipher.cpp \
    ../libs/perms.cpp \
    ../libs/gronsfeld.cpp \
    ../libs/vigenere.cpp


HEADERS += \
    Gronsfeld/tst_gronsfeld.h \
    MathAux/tst_mathaux.h \
    Perms/tst_perms.h \
    Subcipher/tst_subcipher.h \
    Vigenere/tst_vigenere.h \
    ../libs/subcipher.h \
    ../libs/perms.h \
    ../libs/gronsfeld.h \
    ../libs/aux/math_aux.h \
    ../libs/vigenere.h



