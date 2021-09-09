cmake_minimum_required(VERSION 3.20)
project(ft_ssl C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)

add_executable(ft_ssl
        usage.c
        utils.c
        parse_arg.c
        options/parse_option_p.c
        options/parse_option_q.c
        options/parse_option_r.c
        options/parse_option_s.c
        includes/ft_ssl.h
        ft_ssl.c
        commands/md5.c
        commands/sha256.c
        includes/md5.h print.c)
