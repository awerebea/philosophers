/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:36:48 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/27 22:47:31 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				ret_msg(char *str, int errcode)
{
	int			fd;

	fd = (!errcode) ? 1 : 2;
	if (str)
		ft_putstr_fd(str, fd);
	return (errcode);
}

int				is_positive_dec_int(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!((i && ft_isdigit(str[i])) \
			|| (!i && (str[i] == '+' || ft_isdigit(str[i])))))
			return (1);
		i++;
	}
	return (0);
}

int				check_arguments(int argc, char **argv)
{
	int			i;
	int			flag;

	i = 1;
	flag = 0;
	if (argc != 5 && argc != 6)
		return (ret_msg("error: wrong number of arguments\n", 1));
	while (i < argc)
	{
		if (is_positive_dec_int(argv[i]))
		{
			if (flag)
				ft_putstr_fd(", ", 2);
			if (!flag)
				flag = (ret_msg("error: wrong argument(s): ", 1));
			ft_putstr_fd(argv[i], 2);
		}
		i++;
	}
	if (flag)
		return (ret_msg("\n", 1));
	return (0);
}

int				main(int argc, char **argv)
{
	(void)argv;
	if (check_arguments(argc, argv))
		return (1);
	return (0);
}
