project(kernel)

file(GLOB_RECURSE rtthread-nano
    "rtthread-nano/Src/*.*" "rtthread-nano/libcpu/arm/cortex-m3/*.*"
    )

add_library(${PROJECT_NAME} ${rtthread-nano})
#add_library(vendor::stmF1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC rtthread-nano/include
    PRIVATE rtthread-nano/include/libc
    )