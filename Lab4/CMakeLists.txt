cmake_minimum_required(VERSION 3.30)
project(Lab4 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab4 main.c)

include_directories("C:\\Program Files (x86)\\LabJack\\Drivers")
target_link_libraries(Lab4 "C:\\Program Files (x86)\\LabJack\\Drivers\\LabJackUD.lib")