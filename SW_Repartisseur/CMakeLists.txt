cmake_minimum_required(VERSION 3.1)

project(versionOne)
set (CMAKE_CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ./bin)

include_directories(/usr/include)
include_directories(/usr/include/c++/9)
include_directories(/usr/include/c++/9/backward)
include_directories(/usr/include/oscpack)
include_directories(/usr/include/x86_64-linux-gnu)
include_directories(/usr/include/x86_64-linux-gnu/c++/9)
include_directories(/usr/lib/gcc/x86_64-linux-gnu/9/include)
include_directories(/usr/local/include)
include_directories(/usr/local/include/oscpack)
include_directories("serialib")

link_directories(/usr/local/lib)
  
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_C_FLAGS "-g -Wall")

include_directories(./inc)

add_executable(versionOne src/main.cpp src/sendosc.cpp src/slmx4_vcom.cpp src/serialib.cpp)
target_link_libraries(versionOne oscpack ${LIBS})

INSTALL(TARGETS versionOne RUNTIME DESTINATION bin)

