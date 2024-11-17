cmake_minimum_required(VERSION 3.29)
project(Formal_Brmal_Bejeweled)

# Enable automatic moc, uic, and rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets Network)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add header files
set(HEADERS
        caboutdlg.h
        capptool.h
        cbejeweleddlg.h
        cconfig.h
        cconfigdao.h
        cconfiglogic.h
        cgamedlg.h
        cgamelogic.h
        chelpdlg.h
        cmenudlg.h
        cmusicdlg.h
        cmusicplayer.h
        cnamedlg.h
        crankdao.h
        crankdlg.h
        cranklogic.h
        csetdlg.h
        cthemedlg.h
        Global.h
)

# Add source files
set(SOURCES
        caboutdlg.cpp
        capptool.cpp
        cbejeweleddlg.cpp
        cconfig.cpp
        cconfigdao.cpp
        cconfiglogic.cpp
        cgamedlg.cpp
        cgamelogic.cpp
        chelpdlg.cpp
        cmenudlg.cpp
        cmusicdlg.cpp
        cmusicplayer.cpp
        cnamedlg.cpp
        crankdao.cpp
        crankdlg.cpp
        cranklogic.cpp
        csetdlg.cpp
        cthemedlg.cpp
        Global.cpp
        main.cpp
)

# Add UI files
set(UIS
        caboutdlg.ui
        cbejeweleddlg.ui
        cgamedlg.ui
        chelpdlg.ui
        cmenudlg.ui
        cmusicdlg.ui
        cnamedlg.ui
        crankdlg.ui
        csetdlg.ui
        cthemedlg.ui
)

# Add executable
add_executable(Formal_Brmal_Bejeweled ${HEADERS} ${SOURCES} ${UIS})

# Link Qt6 libraries
target_link_libraries(Formal_Brmal_Bejeweled PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::Network
)