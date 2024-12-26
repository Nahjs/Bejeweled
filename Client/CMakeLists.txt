cmake_minimum_required(VERSION 3.29)
project(Client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets Test)

# 添加源文件
set(SOURCES
    main.cpp
    client.cpp
    client.h
    chatroom.cpp
    chatroom.h
    chatroom.ui
    chatroom_test.cpp
)

# 添加包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Client ${SOURCES})

target_link_libraries(Client PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Widgets
    Qt6::Test
)

# 设置工作目录
set_target_properties(Client PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
