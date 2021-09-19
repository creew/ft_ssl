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
#ifndef MD5_H
# define MD5_H

# include "ssl_types.h"
# include <stddef.h>

typedef struct s_md5_context {
	t_u32			a;
	t_u32			b;
	t_u32			c;
	t_u32			d;
	unsigned char	buf[64];
	t_u64			length;
	int				available;
}				t_md5_context;

void	md5_final(unsigned char *digest, t_md5_context *context);
void	md5_update(t_md5_context *context, const char *buf, size_t size);
void	md5_init(t_md5_context *context);
#endif