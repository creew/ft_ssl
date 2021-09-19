/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:00:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/10 18:00:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHA224_H
# define SHA224_H

# include "ssl_types.h"
# include <stddef.h>

typedef struct s_sha224_context {
	t_u32	h[8];
	union {
		t_u32			chunks[16];
		unsigned char	buf[64];
	};
	t_u64	length;
	int		available;
}				t_sha224_context;

void	sha224_final(unsigned char *digest, t_sha224_context *context);
void	sha224_update(t_sha224_context *context, const char *buf, size_t size);
void	sha224_init(t_sha224_context *context);

#endif