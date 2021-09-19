/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:00:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/10 18:00:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHA512_H
# define SHA512_H

# include "ssl_types.h"
# include <stddef.h>

typedef struct s_sha512_context {
	t_u64	h[8];
	union {
		t_u64			chunks[16];
		unsigned char	buf[128];
	};
	t_u64	length[2];
	int		available;
}				t_sha512_context;

void	sha512_final(unsigned char *digest, t_sha512_context *context);
void	sha512_update(t_sha512_context *context, const char *buf, size_t size);
void	sha512_init(t_sha512_context *context);

#endif