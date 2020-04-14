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
find_package(glm REQUIRED)

add_subdirectory(external)

add_library(engine SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        fmt
        spdlog::spdlog
        EnTT::EnTT
        glfw
        glm
        glad
        ${CMAKE_DL_LIBS}
)

target_precompile_headers(${PROJECT_NAME}
        PRIVATE pch.h
)
