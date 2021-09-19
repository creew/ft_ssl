/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:35:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/09/05 16:35:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int main(int ac, char *av[]) {
	t_ft_ssl_handler ft_ssl_handler;

	ft_memset(&ft_ssl_handler, 0, sizeof(t_ft_ssl_handler));
	if (parse_argv(&ft_ssl_handler, ac, av) == ERROR) {
		return (1);
	}
	if (ft_ssl_handler.handler->function(&ft_ssl_handler.ft_ssl, ft_ssl_handler.handler->name) == ERROR) {
		return (1);
	}
    return 0;
}
