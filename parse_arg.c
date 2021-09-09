/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 21:42:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/05/21 21:42:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <stddef.h>

static const t_arg_function g_arg_functions[] = {
	{'p', parse_option_p, "echo STDIN to STDOUT and append the checksum to STDOUT"},
	{'q', parse_option_q, "quiet mode"},
	{'r', parse_option_r, "reverse the format of the output"},
	{'s', parse_option_s, "print the sum of the given string"},
};

static const t_handler g_ssl_functions[] = {
	{"md5", md5},
	{"sha256", sha256},
};

char	*parse_joined_option(t_parse_option *option)
{
	char	arg_symbol;
	char	*arg;

	arg = option->arg;
	arg_symbol = *arg++;
	if (*arg == 0)
	{
		if (option->i < option->argc)
			arg = option->argv[option->i++];
		else {
		    err_require_arg(arg_symbol);
		    arg = NULL;
		}
	}
	else
	{
		while (ft_isspace(*arg))
			arg++;
	}
	return (arg);
}

static int	parse_options(t_ft_ssl *ft_ssl, t_parse_option *option)
{
	unsigned long c;

	option->arg++;
	c = 0;
	while (c < sizeof(g_arg_functions) / sizeof(g_arg_functions[0]))
	{
		if (*option->arg == g_arg_functions[c].arg)
			return (g_arg_functions[c].parse_function(ft_ssl, option));
		c++;
	}
	if (*option->arg != 0)
	{
		err_invalid_option(*option->arg);
		print_usage(2);
		return (ERROR);
	}
	return (OK);
}

static int parse_command(t_ft_ssl_handler *ft_ssl_handler, t_parse_option *option)
{
	unsigned long	c;
    char			*arg;

    if (option->argc < 2) {
		print_usage(2);
        return (ERROR);
    }
    arg = option->argv[option->i++];
    c = 0;
    while (c < (sizeof(g_ssl_functions) / sizeof(g_ssl_functions[0])))
    {
    	if (ft_strcmp(arg, g_ssl_functions[c].name) == 0)
		{
    		ft_ssl_handler->handler = &g_ssl_functions[c];
			return (OK);
		}
    	c++;
    }
	err_invalid_command(arg);
	return (ERROR);
}

int	parse_argv(t_ft_ssl_handler *ft_ssl_handler, int argc, char *argv[])
{
	t_parse_option	option;
	char			*arg;
	int             res;

	option.i = 1;
	option.argc = argc;
	option.argv = argv;
	if (parse_command(ft_ssl_handler, &option) == ERROR) {
	    return (ERROR);
	}
	while (option.i < argc)
	{
		arg = argv[option.i];
		option.i++;
		if (*arg == '-')
		{
			option.arg = arg;
			while ((res = parse_options(&ft_ssl_handler->ft_ssl, &option)) != OK)
			{
			    if (res == ERROR) {
                    return (ERROR);
			    }
			}
		}
		else
		{
			ft_ssl_handler->ft_ssl.args = argv + option.i - 1;
			ft_ssl_handler->ft_ssl.arg_size = argc - (option.i - 1);
			break;
		}
	}
	return (OK);
}
