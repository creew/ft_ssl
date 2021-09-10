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

typedef unsigned int t_u32;
typedef unsigned long t_u64;

typedef struct	s_sha_context {
	t_u32 h0;
	t_u32 h1;
	t_u32 h2;
	t_u32 h3;
	t_u32 h4;
	t_u32 h5;
	t_u32 h6;
	t_u32 h7;

	union {
		t_u32 chunks[16];
		unsigned char buf[64];
	};
	t_u64 length;
	int available;
} t_sha256_context;

#endif