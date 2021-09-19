/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:00:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/10 18:00:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_SSL_SHA256_H
# define FT_SSL_SHA256_H

#include "ssl_types.h"
#include <stddef.h>

typedef struct	s_sha_context {
	t_u32 h[8];
	union {
		t_u32 chunks[16];
		unsigned char buf[64];
	};
	t_u64 length;
	int available;
} t_sha256_context;

void sha256_final(unsigned char *digest, t_sha256_context *context);
void sha256_update(t_sha256_context *context, const char *buf, size_t size);
void sha256_init(t_sha256_context *context);

#endif