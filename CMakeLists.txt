cmake_minimum_required(VERSION 3.28)
project(IMGASCII CXX)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Операционная система: Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "Операционная система: Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "Операционная система: macOS")
else()
    message(STATUS "Неизвестная операционная система")
endif()

find_package(OpenCV REQUIRED PATHS "D:/Projects/Soft/opencv/build")
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(IMGASCII
    main.cpp
    src/imgasciic.cpp
    src/imgasciic.h
)

target_link_libraries(IMGASCII ${OpenCV_LIBS})