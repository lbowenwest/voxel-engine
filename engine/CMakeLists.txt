project(engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/src/library.cpp
        ${PROJECT_SOURCE_DIR}/src/application.cpp
)

add_library(engine SHARED ${SOURCES})

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)