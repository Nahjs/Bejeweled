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
        chatroom.h
        Client/chatclient.h
        propshop.h
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
        signup.cpp
        Verification.cpp
        sliderpuzzlewidget.cpp
        puzzlewidget.cpp
        start.cpp
        chatroom.cpp
        Client/chatclient.cpp
        propshop.cpp
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
        chatroom.ui
        propshop.ui
)

# 添加资源文件
set(QRC
        res/res.qrc
)

# Add executable
add_executable(Jewels ${HEADERS} ${SOURCES} ${UIS} ${QRC})

# Link Qt6 libraries
target_link_libraries(Jewels PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::Network
        Qt6::Sql
)