cmake_minimum_required(VERSION 3.16)
project(sandbox)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog REQUIRED)

add_executable(sandbox main.cpp)

target_link_libraries(${PROJECT_NAME}
        engine
        spdlog::spdlog
    )
