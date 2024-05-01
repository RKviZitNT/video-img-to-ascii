cmake_minimum_required(VERSION 3.28)
project(asciiconverter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Операционная система: Windows")
    set(OpenCV_DIR "D:/Projects/Soft/opencv/build/x64/vc16/lib")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "Операционная система: Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "Операционная система: macOS")
else()
    message(STATUS "Неизвестная операционная система")
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(asciic
    main.cpp
    src/asciic.cpp
    src/asciic.h
)
target_link_libraries(asciic ${OpenCV_LIBS})