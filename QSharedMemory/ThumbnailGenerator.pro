QT += gui widgets winextras

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
    ../include/PlatformDependent.cpp \
	main.cpp

HEADERS += \
    ../include/PlatformDependent.h \
    main.h

INCLUDEPATH += \
    ../include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -luuid # для создания превью; -lshell32 и -lole32 не понадобились, хотя ИИ писал, что нужны
