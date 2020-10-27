/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 20:50:20 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/27 22:34:44 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				init_data(t_data *data, char **argv)
{
	int			i;

	i = 0;
	if (!(data->num_of_ph = ft_atoi(argv[1])))
		return (ret_msg("error: there must be at least one philosopher\n", 1));
	data->tm_to_die = ft_atoi(argv[2]);
	data->tm_to_eat = ft_atoi(argv[3]);
	data->tm_to_slp = ft_atoi(argv[4]);
	data->num_to_eat = (argv[5]) ? ft_atoi(argv[5]) : -1;
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
