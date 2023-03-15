QT += testlib
QT -= gui

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

SOURCES += \
    test_perms.cpp \
    test_subcipher.cpp \
    ../subcipher.cpp \
    ../perms.cpp


HEADERS += \
    test_perms.h \
    test_subcipher.h \
    ../subcipher.h \
    ../perms.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


