QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SUBDIRS += tests


SOURCES += \
    gronsfeld.cpp \
    main.cpp \
    mainwindow.cpp \
    perms.cpp \
    playfair.cpp \
    subcipher.cpp \
    vigenere.cpp

HEADERS += \
    aux/math_aux.h \
    gronsfeld.h \
    mainwindow.h \
    perms.h \
    playfair.h \
    subcipher.h \
    vigenere.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target