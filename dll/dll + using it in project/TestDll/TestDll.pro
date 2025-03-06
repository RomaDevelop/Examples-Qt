QT -= gui

TEMPLATE = lib
DEFINES += TESTDLL_LIBRARY

CONFIG += c++17 build_all

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    testdll.cpp

HEADERS += \
    TestDll_global.h \
    testdll.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = ..\bin
win32:CONFIG(release, debug|release): TARGET = TestDLL
else:win32:CONFIG(debug, debug|release): TARGET = TestDLLd
