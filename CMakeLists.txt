cmake_minimum_required(VERSION 3.16)
project(saolei)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(saolei 
    main.cpp 
    myCanvas.cpp 
    myCanvas.h
    table.cpp
    table.h
    grid.cpp
    grid.h
)

target_link_libraries(saolei Qt6::Core Qt6::Widgets)