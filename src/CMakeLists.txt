set(PROJECT_NAME ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "-g -O2")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(server basic.cpp)

add_executable(client advanced.cpp)
