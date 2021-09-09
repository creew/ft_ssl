/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 00:05:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/03 00:05:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H

#include <stddef.h>

enum e_errors {
    ERROR = -1,
    OK = 0,
    CONTINUE
};

enum e_input {
    STDIN,
    STRING,
    FILE
};

typedef struct	s_ft_ssl {
	char echo_stdin;
	char quiet;
	char reverse;
	char print_string;
	char **args;
	int arg_size;
	char *string;
}				t_ft_ssl;

typedef struct	s_handler {
    char *name;
    int (*function)(t_ft_ssl *);
}				t_handler;

typedef struct s_ft_ssl_handler {
    t_ft_ssl ft_ssl;
    const t_handler *handler;
} t_ft_ssl_handler;

typedef struct	s_parse_option {
	int argc;
	char **argv;
	char *arg;
	int i;
}				t_parse_option;

typedef struct	s_arg_function{
	char arg;
	int (*parse_function)(t_ft_ssl *, t_parse_option *);
	char *desc;
}				t_arg_function;

int ft_strlen(const char *s);
void ft_print(const char *s);
void ft_putchar(char c);
void ft_dprint(int d, const char *s);
void ft_dprint_endl(int d, const char *s);
void ft_dputchar(int d, char c);
int ft_strcmp(const char *s1, const char *s2);
int ft_isspace(char c);
void ft_memset(void *buf, char c, size_t size);
void ft_memcpy(void *dst, const void *src, size_t size);
void ft_print_hex(const unsigned char *buf, size_t length);

void print_usage();
void err_require_arg(char c);
void err_invalid_option(char c);
void err_invalid_command(const char *arg);
void err_no_such_file(const char *command, const char *file);

int	parse_argv(t_ft_ssl_handler *ft_ssl_handler, int argc, char *argv[]);
char *parse_joined_option(t_parse_option *option);
int	parse_option_p(t_ft_ssl *ft_ssl, t_parse_option *option);
int	parse_option_q(t_ft_ssl *ft_ssl, t_parse_option *option);
int	parse_option_r(t_ft_ssl *ft_ssl, t_parse_option *option);
int	parse_option_s(t_ft_ssl *ft_ssl, t_parse_option *option);

int md5(t_ft_ssl *ft_ssl);
int sha256(t_ft_ssl *ft_ssl);

void print_md5(char *type, t_ft_ssl *ft_ssl, enum e_input input, char *src, unsigned char *digest);
#endif