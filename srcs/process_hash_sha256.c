/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:42:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/12 16:42:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

#include <sys/fcntl.h>
#include <unistd.h>

static void process_buf(char *buf, size_t len, unsigned char *digest) {
	t_sha256_context context;

	sha256_init(&context);
	sha256_update(&context, buf, len);
	sha256_final(digest, &context);
}

static int process_fd(t_ft_ssl *ft_ssl, int fd, unsigned char *digest) {
	t_sha256_context context;
	char buf[64];
	ssize_t res;

	sha256_init(&context);
	while ((res = read(fd, buf, sizeof(buf))) != 0) {
		if (res < 0) {
			return (ERROR);
		}
		if (fd == 0) {
			if (ft_ssl->echo_stdin) {
				write(1, buf, res);
			}
		}
		sha256_update(&context, buf, res);
	}
	sha256_final(digest, &context);
	return (OK);
}

static int process_file(t_ft_ssl *ft_ssl, char *file, unsigned char *digest) {
	int fd;
	int res;

	fd = open(file, O_RDONLY);
	if (fd < 0) {
		err_no_such_file("sha256", file);
		return (ERROR);
	}
	res = process_fd(ft_ssl, fd, digest) == ERROR;
	if (res == ERROR) {
		err_no_such_file("sha256", file);
	}
	if (fd != 0) {
		close(fd);
	}
	return (res);
}

int process_hash_sha256(t_ft_ssl *ft_ssl) {
	int i;
	int res;
	unsigned char digest[32];

	if ((ft_ssl->arg_size < 1 && !ft_ssl->print_string) || ft_ssl->echo_stdin) {
		process_fd(ft_ssl, 0, digest);
		print_hash("SHA256", ft_ssl, STDIN, "", digest, 32);
	}
	if (ft_ssl->print_string) {
		process_buf(ft_ssl->string, ft_strlen(ft_ssl->string), digest);
		print_hash("SHA256", ft_ssl, STRING, ft_ssl->string, digest, 32);
	}
	i = 0;
	while (i < ft_ssl->arg_size) {
		res = process_file(ft_ssl, ft_ssl->args[i], digest);
		if (res == OK) {
			print_hash("SHA256", ft_ssl, FILE, ft_ssl->args[i], digest, 32);
		}
		i++;
	}
	return (OK);
}