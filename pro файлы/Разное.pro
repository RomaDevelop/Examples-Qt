
# если некоторые .h файлы лежат не в каталоге с .pro то нужно это
INCLUDEPATH += $$PWD/add
DEPENDPATH += $$PWD/add

# указание исходников
SOURCES += \
    add\icanphisic.cpp		# если исходник лежит не в папке с .pro то нужно указывать путь к нему

HEADERS += \
    add\icanphisic.h		# если исходник лежит не в папке с .pro то нужно указывать путь к нему
	
# подключение dll (библиотека chai.dll)
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/add/ -lchai			# release библиотека
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/add/ -lchaid		# debug библиотека
# необходимо указать точный путь где лежит
# внимание! -lchai и -lchaid это два файла библиотеки для релиз и дебаг конфигурации
# если у нас всего один файл или не хотим замарачиваться - во второй строке вместо lchaid пишем lchai


# добавление дефайнов через про файл
DEFINES += APP_VERSION=\\\"1.0.0\\\"