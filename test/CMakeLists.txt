cmake_minimum_required(VERSION 3.29)
project(BattleGameTest LANGUAGES CXX)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${CMAKE_SOURCE_DIR}/../common/include)

# Add source files
set(TEST_SOURCES
    battlegame_test.cpp
    ../battlegame.cpp
    ../numMatrix.cpp
    ../prop.cpp
    ../Client/chatclient.cpp
    ../common/src/textmessage.cpp
)

# Add header files
set(TEST_HEADERS
    ../battlegame.h
    ../numMatrix.h
    ../Client/chatclient.h
    ../common/include/textmessage.h
    ../common/include/messagetypes.h
)

# Create test executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${TEST_HEADERS})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Client
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
)
