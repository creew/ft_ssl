/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 21:39:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/05 21:39:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

typedef unsigned int t_u32;
typedef unsigned long t_u64;

typedef struct	s_md5_context {
	t_u32 a;
	t_u32 b;
	t_u32 c;
	t_u32 d;
    unsigned char buf[64];
	t_u64 length;
	int available;
}				t_md5_context;

#endif