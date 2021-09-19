/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:04:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/09 23:04:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <stddef.h>

static int to_hex(int i)
{
	if (i < 10)	{
		return (i + '0');
	}
	return ((i - 10) + 'a');
}

void ft_print_hex(const unsigned char *buf, size_t length)
{
	size_t i;

	i = 0;
	while (i < length) {
		ft_dputchar(1, to_hex(buf[i] >> 4));
		ft_dputchar(1, to_hex(buf[i] & 0xF));
		i++;
	}
}

void print_in_brackets(char *s) {
	ft_print("(");
	ft_print(s);
	ft_print(")");
}

void print_in_qbrackets(char *s) {
	ft_print("(\"");
	ft_print(s);
	ft_print("\")");
}

void print_in_quotes(char *s) {
	ft_print("\"");
	ft_print(s);
	ft_print("\"");
}

void print_hash(char *type, t_ft_ssl *ft_ssl, enum e_input input, char *src, unsigned char *digest, size_t length)
{
	if (ft_ssl->quiet) {
		ft_print_hex(digest, length);
		ft_print("\n");
	} else {
		if (input == STDIN) {
			ft_print_hex(digest, length);
			ft_print("\n");
		} else {
			if (ft_ssl->reverse) {
				ft_print_hex(digest, length);
				ft_print(" ");
				if (input == STRING)
					print_in_quotes(src);
				else
					ft_print(src);
				ft_print("\n");
			} else {
				ft_print_upper(type);
				ft_print(" ");
				if (input == STRING) {
					print_in_qbrackets(src);
				} else {
					print_in_brackets(src);
				}
				ft_print(" = ");
				ft_print_hex(digest, length);
				ft_print("\n");
			}
		}
	}
}