project(engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/src/library.cpp
        ${PROJECT_SOURCE_DIR}/src/application.cpp
)

find_package(spdlog REQUIRED)

add_library(engine SHARED ${SOURCES})

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE spdlog::spdlog
)