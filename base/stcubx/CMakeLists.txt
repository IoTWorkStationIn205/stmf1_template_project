
# 传递源文件
file(GLOB_RECURSE SOURCES_CORE "Core/*.*")

set(SOURCES ${SOURCES};${SOURCES_CORE})
set(SOURCES "${SOURCES}" PARENT_SCOPE)

# 头文件
set(INCLUDE_CORE "${CMAKE_SOURCE_DIR}/base/stcubx/Core/Inc")

set(INCLUDE ${INCLUDE};${INCLUDE_CORE})
set(INCLUDE "${INCLUDE}" PARENT_SCOPE)