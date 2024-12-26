cmake_minimum_required(VERSION 3.29)
project(GameServer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

# 添加源文件
set(SOURCES
    main.cpp
    server.cpp
    server.h
    ../common/src/textmessage.cpp
    ../common/include/textmessage.h
    ../common/include/messagetypes.h
    ../common/include/messagedata.h
    ../numMatrix.cpp
    ../numMatrix.h
    ../prop.cpp
    ../prop.h
)

# 添加包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..        # 添加上级目录以找到 numMatrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include  # 确保这个路径正确
)

add_executable(GameServer ${SOURCES})

target_link_libraries(GameServer PRIVATE
    Qt6::Core
    Qt6::Network
)

# 设置工作目录
set_target_properties(GameServer PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
