QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tests.cpp \
    Subcipher/tst_subcipher.cpp \
    ../libs/subcipher.cpp


HEADERS += \
    Subcipher/tst_subcipher.h \
    ../libs/subcipher.h

