/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 00:04:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/03 00:04:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void print_usage(int d) {
	ft_dprint(d, "usage: ft_ssl command [flags] [file/string]\n");
}

void err_require_arg(char c) {
	ft_dprint(2, "ft_ssl: option requires an argument -- '");
	ft_dputchar(2, c);
	ft_dprint(2, "'\n");
}

void err_invalid_option(char c) {
	ft_dprint(2, "ft_ssl: invalid option -- '");
	ft_dputchar(2, c);
	ft_dprint(2, "'\n");
}

void err_invalid_command(const char *arg) {
	ft_dprint(2, "ft_ssl: Error: '");
	ft_dprint(2, arg);
	ft_dprint(2, "' is an invalid command.\n"
				 "\n"
				 "Commands:\n"
				 "md5\n"
				 "sha256\n"
				 "sha224\n"
				 "\n"
				 "Flags:\n"
				 "-p -q -r -s\n");
}

void err_no_such_file(const char *command, const char *file) {
	ft_dprint(2, "ft_ssl: ");
	ft_dprint(2, command);
	ft_dprint(2, ": ");
	ft_dprint(2, file);
	ft_dprint(2, ": No such file or directory\n");
}

