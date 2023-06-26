set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.0)

# 导入工具链
include(cmake/tool.cmake)

project(template_project C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

#Uncomment for hardware floating point
#add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
#add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
#add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

#Uncomment for software floating point
add_compile_options(-mfloat-abi=soft)

add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

# 编译等级
include(cmake/compilationLevelSelection.cmake)

# Device define
add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB)

# 链接文件
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/build/ld/STM32F103RBTX_FLASH.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

# 源文件
set(SOURCES "")

# 头文件路径
set(INCLUDE "")

add_subdirectory(base/stcubx)
include_directories(
    ${INCLUDE}
)
# Lib
add_subdirectory(vendor)
get_target_property(VENDOR_INCLUDE_DIRS vendor::stmF1 INCLUDE_DIRECTORIES)
include_directories(
    ${VENDOR_INCLUDE_DIRS}
)

add_subdirectory(drivers)
get_target_property(DRIVERS_INCLUDE_DIRS drivers::V1 INCLUDE_DIRECTORIES)
include_directories(
    ${DRIVERS_INCLUDE_DIRS}
)

add_subdirectory(base)
include_directories(
    ${INCLUDE}
)

add_subdirectory(kernel)
get_target_property(DRIVERS_INCLUDE_DIRS kernel INCLUDE_DIRECTORIES)
include_directories(
    ${DRIVERS_INCLUDE_DIRS}
)

add_subdirectory(applications)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

target_link_libraries(${PROJECT_NAME}.elf
    vendor::stmF1
    applications::app1
    drivers::V1
    kernel
)

# 获取当前目录路径
get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${include_dirs})
  message("Include Directory: ${dir}")
endforeach()

