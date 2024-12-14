cmake_minimum_required(VERSION 3.29)
project(ChatServer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(ChatServer
    main.cpp
    chatserver.cpp
    chatserver.h
)

target_link_libraries(ChatServer PRIVATE
    Qt6::Core
    Qt6::Network
)
