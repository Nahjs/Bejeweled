cmake_minimum_required(VERSION 3.29)
project(Bejeweled)

# Enable automatic moc, uic, and rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 设置源文件编码为 UTF-8
set_source_files_properties(src/*.cpp PROPERTIES COMPILE_FLAGS "-finput-charset=UTF-8 -fexec-charset=UTF-8")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets Network)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add header files
set(HEADERS
        cgamedlg.h
        cgamelogic.h
        Global.h
)

# Add source files
set(SOURCES
        cgamedlg.cpp
        cgamelogic.cpp
        main.cpp
        Global.cpp
)

# Add UI files
set(UIS
        cgamedlg.ui
)

# 添加资源文件
set(QRC
        res/res.qrc
)

# Add executable
add_executable(Bejeweled ${HEADERS} ${SOURCES} ${UIS} ${QRC})

# Link Qt6 libraries
target_link_libraries(Bejeweled PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::Network
)