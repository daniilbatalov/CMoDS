QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tests.cpp \
    Gronsfeld/tst_gronsfeld.cpp \
    MathAux/tst_mathaux.cpp \
    Perms/tst_perms.cpp \
    Subcipher/tst_subcipher.cpp \
    ../libs/subcipher.cpp \
    ../libs/perms.cpp \
    ../libs/gronsfeld.cpp

HEADERS += \
    Gronsfeld/tst_gronsfeld.h \
    MathAux/tst_mathaux.h \
    Perms/tst_perms.h \
    Subcipher/tst_subcipher.h \
    ../libs/subcipher.h \
    ../libs/perms.h \
    ../lib/gronsfeld.h \
    ../libs/aux/math_aux.h


