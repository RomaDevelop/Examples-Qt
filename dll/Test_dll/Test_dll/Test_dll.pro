QT -= gui

TEMPLATE = lib
DEFINES += TEST_DLL_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    test_dll.cpp

HEADERS += \
    Test_dll_global.h \
    test_dll.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

#TEMPLATE = lib
#DESTDIR = dist

#unix: {
#    CONFIG(debug, debug|release) {
#        TARGET = test_dll_d
#        }
#        else {
#            TARGET = test_dll
#            }
#    }
#    else {
#        TARGET = $$qtLibraryTarget(test_dll)
#        }

#VERSION = 1.0.0

#CONFIG += debug_and_release build_all

#CONFIG(debug, debug|release) {
#    OBJECTS_DIR = build/debug
#    }
#    else {
#        OBJECTS_DIR = build/release
#        }

#HEADERS += \
#    Test_dll_global.h \
#    test_dll.h

#DEFINES += TEST_DLL_LIBRARY
