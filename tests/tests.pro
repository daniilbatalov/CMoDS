QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_tests.cpp \
    Perms/tst_perms.cpp \
    Subcipher/tst_subcipher.cpp \
    ../libs/subcipher.cpp \
    ../libs/perms.cpp

HEADERS += \
    Perms/tst_perms.h \
    Subcipher/tst_subcipher.h \
    ../libs/subcipher.h \
    ../libs/perms.h


