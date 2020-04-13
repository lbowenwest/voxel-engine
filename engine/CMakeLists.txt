project(engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/src/library.cpp
        ${PROJECT_SOURCE_DIR}/src/application.cpp
        ${PROJECT_SOURCE_DIR}/src/window.cpp
)

find_package(spdlog REQUIRED)
find_package(EnTT REQUIRED)
find_package(glfw3 REQUIRED)

add_library(engine SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE spdlog::spdlog EnTT::EnTT glfw
)

target_precompile_headers(${PROJECT_NAME}
        PRIVATE pch.h
)