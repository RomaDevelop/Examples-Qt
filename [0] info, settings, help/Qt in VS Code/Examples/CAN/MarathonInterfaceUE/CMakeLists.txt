cmake_minimum_required(VERSION 3.10)

project(MarathonProjectUE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск компонентов Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Пути к заголовочным файлам
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Список исходных файлов
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

if(WIN32)
    #add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})    # Для Windows: чтобы консоль не выводилась в выпуске вместе с окном
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}) 
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

# Пути поиска библиотек
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../bin/)

# Подключение библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets
    debug MarathonInterfaced
    optimized MarathonInterface
    chai
)

# Правила установки (INSTALLS)
if(QNX)
    set(INSTALL_PATH /tmp/${PROJECT_NAME}/bin)
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    set(INSTALL_PATH /opt/${PROJECT_NAME}/bin)
endif()

if(INSTALL_PATH)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_PATH})
endif()