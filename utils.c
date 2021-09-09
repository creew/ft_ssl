/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 00:04:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/03 00:04:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int ft_strlen(const char *s)
{
	int length;

	length = 0;
	while (*s++)
	{
		length++;
	}
	return (length);
}

int ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v');
}

void ft_print(char *s)
{
	write(1, s, ft_strlen(s));
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_dprint(int d, const char *s)
{
	write(d, s, ft_strlen(s));
}

void ft_dprint_endl(int d, const char *s)
{
	ft_dprint(d, s);
	ft_dprint(d, "\n");
}

void ft_dputchar(int d, char c)
{
	write(d, &c, 1);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 - *s2) == 0) {
		if (*s1 == 0 || *s2 == 0)
			break;
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void ft_memset(void *buf, char c, size_t size) {
	char *s;

	s = (char *)buf;
	while (size != 0) {
		*s++ = c;
		size--;
	}
}

void ft_memcpy(void *dst, const void *src, size_t size) {
	unsigned char *d;
	const unsigned char *s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (size) {
		*d++ = *s++;
		size--;
	}
}
