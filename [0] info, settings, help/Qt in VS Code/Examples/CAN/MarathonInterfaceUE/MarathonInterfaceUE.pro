QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../include
INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

#begin connecting MarathonInterface
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/ -lMarathonInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/ -lMarathonInterfaced
#end connecting MarathonInterface

#begin connecting chai
LIBS += -L$$PWD/../bin/ -lchai
#end connecting chai
