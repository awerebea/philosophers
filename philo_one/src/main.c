/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:36:48 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/29 11:49:51 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int				ret_msg(char *str, int errcode)
{
	int			fd;

	fd = (!errcode) ? 1 : 2;
	if (str)
		ft_putstr_fd(str, fd);
	return (errcode);
}

static int		is_positive_dec_int(char *str)
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

static int		check_arguments(int argc, char **argv)
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

static int		init_data(t_data *data, char **argv)
{
	int			i;

	i = 0;
	if (!(data->num_of_ph = ft_atoi(argv[1])))
		return (ret_msg("error: there must be at least one philosopher\n", 1));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_to_eat = (argv[5]) ? ft_atoi(argv[5]) : -1;
	data->ph_died = 0;
	if (!(data->mtx_forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * \
			data->num_of_ph)))
		return (ret_msg("error: malloc fails\n", 1));
	while (i < data->num_of_ph)
		pthread_mutex_init(&data->mtx_forks[i++], NULL);
	pthread_mutex_init(&data->mtx_death, NULL);
	pthread_mutex_init(&data->mtx_out, NULL);
	pthread_mutex_init(&data->mtx_time, NULL);
	return (0);
}

int				main(int argc, char **argv)
{
	t_data		data;

	if (check_arguments(argc, argv))
		return (1);
	if (init_data(&data, argv))
		return (1);
	start_threads(&data);
	pthread_mutex_destroy(&data.mtx_death);
	pthread_mutex_destroy(&data.mtx_out);
	pthread_mutex_destroy(&data.mtx_time);
	free(data.mtx_forks);
	return (0);
}
