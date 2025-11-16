QT       += core gui widgets charts

CONFIG += c++17

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

INCLUDEPATH += ../include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
