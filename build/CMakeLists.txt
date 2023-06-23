cmake_minimum_required(VERSION 3.0)

project(build)

# Set the project name
project(device)

file(GLOB_RECURSE SOURCES_Device "Core/*.*" "Drivers/*.*")

include_directories(
    ${PROJECT_SOURCE_DIR}/../device/it/Inc
)

#add_executable(${PROJECT_NAME} ../device/it/stm32f1xx_it.c)

# Add a library with the above sources
add_executable(${PROJECT_NAME}.elf ../device/it/stm32f1xx_it.c ${LINKER_SCRIPT})



