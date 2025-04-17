cmake_minimum_required(VERSION 3.30)
project(HSITesting C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab3 main.c)

include_directories("C:\\Program Files (x86)\\LabJack\\Drivers")
target_link_libraries(Lab3 "C:\\Program Files (x86)\\LabJack\\Drivers\\LabJackUD.lib")
