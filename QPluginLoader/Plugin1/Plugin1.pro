QT +=core
QT -= gui

TEMPLATE = lib
DEFINES += PLUGIN1_LIBRARY
DESTDIR=../bin/Plugins/
CONFIG += plugin
#CONFIG +=c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    plugin1.cpp

HEADERS += \
    ../include/plugininteface.h \
    Plugin1_global.h \
    plugin1.h
INCLUDEPATH +=../include/
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
