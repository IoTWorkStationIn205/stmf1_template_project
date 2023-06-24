project(drivers)

file(GLOB_RECURSE SOURCES_DRIVERS "LedSmg/*.*")

add_library(${PROJECT_NAME} ${SOURCES_DRIVERS})
add_library(drivers::V1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC LedSmg/Inc
    )