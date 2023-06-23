project(vendor)

set(BASE_PATH STM32CubeF1/Drivers)

file(GLOB_RECURSE SOURCES_Vendor_st_f1
    "${BASE_PATH}/STM32F1xx_HAL_Driver/Src/*.*"
    )

add_library(${PROJECT_NAME} ${SOURCES_Vendor_st_f1})
add_library(vendor::stmF1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${BASE_PATH}/CMSIS/Include
    PUBLIC ${BASE_PATH}/CMSIS/Device/ST/STM32F1xx/Include
    PUBLIC ${BASE_PATH}/STM32F1xx_HAL_Driver/Inc
    PUBLIC ${BASE_PATH}/STM32F1xx_HAL_Driver/Inc/Legacy
    )

get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${include_dirs})
  message("Include Directory1: ${dir}")
endforeach()