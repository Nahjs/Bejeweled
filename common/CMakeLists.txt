add_library(common
    src/textmessage.cpp
    src/messageprocessor.cpp
    src/messagehandler.cpp
)

target_include_directories(common
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(common
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
)
