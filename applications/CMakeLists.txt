project(applications)

file(GLOB_RECURSE SOURCES_APP "app1/*.*")

add_library(${PROJECT_NAME} ${SOURCES_APP})
add_library(applications::app1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC app1/Inc
)