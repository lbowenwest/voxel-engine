project(glad)

add_library(${PROJECT_NAME} SHARED "${PROJECT_SOURCE_DIR}/src/glad.c")

set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} PRIVATE
  "${PROJECT_SOURCE_DIR}/include")

