cmake_minimum_required(VERSION 3.0.0)
project(powtest VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

aux_source_directory(src DIR_SRCS)
aux_source_directory(src/util DIR_SRCS_UTIL)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    aux_source_directory(src/win32 DIR_SRCS_WIN32)
    ADD_DEFINITIONS(-D ISWIN32)
ENDIF()
add_executable(powtest  ${DIR_SRCS_UTIL}  ${DIR_SRCS_WIN32} ${DIR_SRCS})