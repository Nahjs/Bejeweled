cmake_minimum_required(VERSION 3.29)
project(Jewels)

# Enable automatic moc, uic, and rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 设置源文件编码为 UTF-8
set_source_files_properties(src/*.cpp PROPERTIES COMPILE_FLAGS "-finput-charset=UTF-8 -fexec-charset=UTF-8")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets Network Sql)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/include)

# Add header files
set(HEADERS
        mainwindow.h
        numMatrix.h
        prop.h
        about.h
        start.h
        help.h
        rank.h
        setup.h
        login.h
        signup.h
        Verification.h
        sliderpuzzlewidget.h
        puzzlewidget.h
        propshop.h
        levelmanager.h
        battle.h
        battlegame.h
        Client/chatroom.h
        Client/client.h
)

# Add source files
set(SOURCES
        mainwindow.cpp
        numMatrix.cpp
        main.cpp
        prop.cpp
        about.cpp
        start.cpp
        help.cpp
        rank.cpp
        setup.cpp
        login.cpp
        Client/client.cpp
        signup.cpp
        Verification.cpp
        sliderpuzzlewidget.cpp
        puzzlewidget.cpp
        start.cpp
        Client/chatroom.cpp
        propshop.cpp
        levelmanager.cpp
        common/src/textmessage.cpp
        battle.cpp
        battlegame.cpp
)

# Add UI files
set(UIS
        mainwindow.ui
        about.ui
        start.ui
        help.ui
        rank.ui
        setup.ui
        login.ui
        signup.ui
        Client/chatroom.ui
        propshop.ui
        levelmanager.ui
        battle.ui
)

# 添加资源文件
set(QRC
        res/res.qrc
)

# Add subdirectories
add_subdirectory(Server)
add_subdirectory(test)  # 添加这一行

# Add executable for client
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${UIS} ${QRC})

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    Qt6::Network
    Qt6::Sql
)