cmake_minimum_required(VERSION 3.20)
project(ft_ssl C)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_C_STANDARD 99)
include(CheckTypeSize)

###############################################################################
# Check for integer types
# (The following are used in check.h. Regardless if they are used in
# the project, they will need to be checked in order to use Check).
check_type_size(intmax_t INTMAX_T)
check_type_size(uintmax_t UINTMAX_T)

check_type_size(pid_t PID_T)
if(NOT HAVE_PID_T)
    if(WIN32)
        set(pid_t "int")
    else(WIN32)
        MESSAGE(FATAL_ERROR "pid_t doesn't exist on this platform?")
    endif(WIN32)
endif(NOT HAVE_PID_T)

include_directories(includes)

set(SOURCES
        srcs/usage.c
        srcs/utils.c
        srcs/parse_arg.c
        srcs/print.c
        srcs/options/parse_option_p.c
        srcs/options/parse_option_q.c
        srcs/options/parse_option_r.c
        srcs/options/parse_option_s.c
        srcs/commands/md5.c
        srcs/commands/sha224.c
        srcs/commands/sha256.c
        srcs/process_hash_md5.c
        srcs/process_hash_sha256.c
        srcs/process_hash_sha224.c
        )

set(HEADERS
        includes/ft_ssl.h
        includes/md5.h
        includes/sha256.h
        includes/ssl_types.h
        includes/sha224.h
        )
add_executable(ft_ssl
        srcs/ft_ssl.c
        ${SOURCES}
        ${HEADERS}
        )

target_compile_options(ft_ssl PRIVATE -save-temps=obj)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -O3")


find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

set(TEST_SOURCES
        tests/test.c
        )

add_executable(check_ft_ssl
        ${SOURCES}
        ${TEST_SOURCES})

target_link_libraries(check_ft_ssl ${CHECK_LIBRARIES})

enable_testing()
add_test(NAME check_ft_ssl COMMAND check_ft_ssl)