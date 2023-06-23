# Set the project name
project(device)

file(GLOB_RECURSE SOURCES_Vendor_st_f1 "Core/*.*" "Drivers/*.*")

# Add a library with the above sources
add_library(${PROJECT_NAME} ${SOURCES_Vendor_st_f1})
add_library(vendor::stmF1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/Core/Inc
    PUBLIC ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc
    PUBLIC ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    PUBLIC ${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    PUBLIC ${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Include
    )