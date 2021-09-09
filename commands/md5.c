/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 17:47:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/05 17:47:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include <sys/fcntl.h>
#include <unistd.h>

uint32_t g_koefficients[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

t_u32 func_f(t_u32 x, t_u32 y, t_u32 z) {
	return ((x & y) | (~x & z));
}

t_u32 func_g(t_u32 x, t_u32 y, t_u32 z) {
	return ((x & z) | (~z & y));
}

t_u32 func_h(t_u32 x, t_u32 y, t_u32 z) {
	return (x ^ y ^ z);
}

t_u32 func_i(t_u32 x, t_u32 y, t_u32 z) {
	return (y ^ (~z | x));
}

t_u32 cycle_rotate_left(t_u32 value, t_u32 shift) {
	return ((value << shift) | (value >> (32 - shift)));
}

/* [abcd k s i] a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). */
int stage1(t_u32 *a, t_u32 b, t_u32 c, t_u32 d, t_u32 k, t_u32 s, int i) {
	*a = (b + cycle_rotate_left(*a + func_f(b, c, d) + k + g_koefficients[i], s));
	return i + 1;
}

/* [abcd k s i] a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s). */
int stage2(t_u32 *a, t_u32 b, t_u32 c, t_u32 d, t_u32 k, t_u32 s, int i) {
	*a = (b + cycle_rotate_left(*a + func_g(b, c, d) + k + g_koefficients[i], s));
	return i + 1;
}

/* [abcd k s i] a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s). */
int stage3(t_u32 *a, t_u32 b, t_u32 c, t_u32 d, t_u32 k, t_u32 s, int i) {
	*a = (b + cycle_rotate_left(*a + func_h(b, c, d) + k + g_koefficients[i], s));
	return i + 1;
}

/* [abcd k s i] a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s). */
int stage4(t_u32 *a, t_u32 b, t_u32 c, t_u32 d, t_u32 k, t_u32 s, int i) {
	*a = (b + cycle_rotate_left(*a + func_i(b, c, d) + k + g_koefficients[i], s));
	return i + 1;
}

void process_body(t_md5_context *context)
{
	t_u32 a;
	t_u32 b;
	t_u32 c;
	t_u32 d;
	int i;
	t_u32 *chunks;

	a = context->a;
	b = context->b;
	c = context->c;
	d = context->d;
	chunks = (t_u32 *)context->buf;

	i = 0;
	while (i < 16) {
		i = stage1(&a, b, c, d, chunks[i], 7, i);
		i = stage1(&d, a, b, c, chunks[i], 12, i);
		i = stage1(&c, d, a, b, chunks[i], 17, i);
		i = stage1(&b, c, d, a, chunks[i], 22, i);
	}
	while (i < 32) {
		i = stage2(&a, b, c, d, chunks[((5 * i) + 1) % 16], 5, i);
		i = stage2(&d, a, b, c, chunks[((5 * i) + 1) % 16], 9, i);
		i = stage2(&c, d, a, b, chunks[((5 * i) + 1) % 16], 14, i);
		i = stage2(&b, c, d, a, chunks[((5 * i) + 1) % 16], 20, i);
	}
	while (i < 48) {
		i = stage3(&a, b, c, d, chunks[((3 * i) + 5) % 16], 4, i);
		i = stage3(&d, a, b, c, chunks[((3 * i) + 5) % 16], 11, i);
		i = stage3(&c, d, a, b, chunks[((3 * i) + 5) % 16], 16, i);
		i = stage3(&b, c, d, a, chunks[((3 * i) + 5) % 16], 23, i);
	}
	while (i < 64) {
		i = stage4(&a, b, c, d, chunks[(7 * i) % 16], 6, i);
		i = stage4(&d, a, b, c, chunks[(7 * i) % 16], 10, i);
		i = stage4(&c, d, a, b, chunks[(7 * i) % 16], 15, i);
		i = stage4(&b, c, d, a, chunks[(7 * i) % 16], 21, i);
	}
	context->a += a;
	context->b += b;
	context->c += c;
	context->d += d;
}

void transform(unsigned char *digest, const t_md5_context *context)
{
	digest[0] = context->a;
	digest[1] = context->a >> 8;
	digest[2] = context->a >> 16;
	digest[3] = context->a >> 24;
	digest[4] = context->b;
	digest[5] = context->b >> 8;
	digest[6] = context->b >> 16;
	digest[7] = context->b >> 24;
	digest[8] = context->c;
	digest[9] = context->c >> 8;
	digest[10] = context->c >> 16;
	digest[11] = context->c >> 24;
	digest[12] = context->d;
	digest[13] = context->d >> 8;
	digest[14] = context->d >> 16;
	digest[15] = context->d >> 24;
}

void md5_final(unsigned char *digest, t_md5_context *context) {
	t_u32 *chunks;

	chunks = (t_u32 *)context->buf;
	context->buf[context->available++] = 0x80;
	if (context->available > 56) {
		while (context->available < 64) {
			context->buf[context->available++] = 0;
		}
		process_body(context);
		context->available = 0;
	}
	while (context->available < 56) {
		context->buf[context->available++] = 0;
	}
	context->length <<= 3;
	chunks[14] = context->length;
	chunks[15] = context->length >> 32;
	process_body(context);
	transform(digest, context);
}

void md5_update(t_md5_context *context, const char *buf, size_t size) {
	context->length += size;
	while (size) {
		context->buf[context->available++] = *buf++;
		if (context->available == 64) {
			process_body(context);
			context->available = 0;
		}
		size--;
	}
}

void md5_init(t_md5_context *context) {
	context->a = 0x67452301;
	context->b = 0xefcdab89;
	context->c = 0x98badcfe;
	context->d = 0x10325476;
	context->available = 0;
	context->length = 0;
}

void process_buf(char *buf, size_t len, unsigned char *digest) {
	t_md5_context context;

	md5_init(&context);
	md5_update(&context, buf, len);
	md5_final(digest, &context);
}

int process_fd(t_ft_ssl *ft_ssl, int fd, unsigned char *digest) {
	t_md5_context context;
	char buf[64];
	ssize_t res;
	ssize_t out;

	if (fd == 0) {
		if (!ft_ssl->quiet) {
			ft_print("(");
			if (!ft_ssl->echo_stdin) {
				ft_print("stdin");
			}
		}
	}
	md5_init(&context);
	while ((res = read(fd, buf, sizeof(buf))) != 0) {
		if (res < 0) {
			return (ERROR);
		}
		if (fd == 0) {
			if (ft_ssl->echo_stdin) {
				out = res;
				while (out > 0 && buf[out - 1] == '\n') {
					out--;
				}
				write(1, buf, out);
			}
		}
		md5_update(&context, buf, res);
	}
	if (fd == 0) {
		if (!ft_ssl->quiet) {
			ft_print(")= ");
		} else {
			if (ft_ssl->echo_stdin)
				ft_print("\n");
		}
	}
	md5_final(digest, &context);
	return (OK);
}

int process_file(t_ft_ssl *ft_ssl, char *file, unsigned char *digest) {
	int fd;
	int res;

	fd = open(file, O_RDONLY);
	if (fd < 0) {
		err_no_such_file("md5", file);
		return (ERROR);
	}
	res = process_fd(ft_ssl, fd, digest) == ERROR;
	if (res == ERROR) {
		err_no_such_file("md5", file);
	}
	close(fd);
	return (res);
}

int md5(t_ft_ssl *ft_ssl) {
	int i;
	int res;
	unsigned char digest[16];

	if ((ft_ssl->arg_size < 1 && !ft_ssl->print_string) || ft_ssl->echo_stdin) {
		process_fd(ft_ssl, 0, digest);
		print_md5("MD5", ft_ssl, STDIN, "", digest);
	}
	if (ft_ssl->print_string) {
		process_buf(ft_ssl->string, ft_strlen(ft_ssl->string), digest);
		print_md5("MD5", ft_ssl, STRING, ft_ssl->string, digest);
	}
	i = 0;
	while (i < ft_ssl->arg_size) {
		res = process_file(ft_ssl, ft_ssl->args[i], digest);
		if (res == OK) {
			print_md5("MD5", ft_ssl, FILE, ft_ssl->args[i], digest);
		}
		i++;
	}
	return (OK);
}