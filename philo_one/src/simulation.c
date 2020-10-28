/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:04:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/29 00:12:38 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

static void		print_msg(t_ph *ph, char *msg)
{
	pthread_mutex_lock(&ph->data->mtx_out);
	if (ph->data->ph_died)
	{
		pthread_mutex_unlock(&ph->data->mtx_out);
		return ;
	}
	ft_putnbr_fd(get_time_in_ms() - ph->simulation_start_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(ph->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(msg, 1);
	pthread_mutex_unlock(&ph->data->mtx_out);
}

static int		take_forks_assist(t_ph *ph, int ffork, int sfork)
{
	pthread_mutex_lock(&ph->data->mtx_forks[ffork]);
	if (ph->data->ph_died)
	{
		pthread_mutex_unlock(&ph->data->mtx_forks[ffork]);
		return (1);
	}
	print_msg(ph, "has taken a fork\n");
	if (ph->data->num_of_ph == 1)
	{
		while (!ph->data->ph_died)
			usleep(1000);
		return (1);
	}
	pthread_mutex_lock(&ph->data->mtx_forks[sfork]);
	if (ph->data->ph_died)
	{
		pthread_mutex_unlock(&ph->data->mtx_forks[ffork]);
		pthread_mutex_unlock(&ph->data->mtx_forks[sfork]);
		return (1);
	}
	print_msg(ph, "has taken a fork\n");
	return (0);
}

static void		take_forks_and_eat(t_ph *ph)
{
	int			forks[2];

	forks[0] = ph->id - 1;
	forks[1] = ph->id % ph->data->num_of_ph;
	if (!(ph->id % 2) && take_forks_assist(ph, forks[0], forks[1]))
		return ;
	else if ((ph->id % 2) && take_forks_assist(ph, forks[1], forks[0]))
		return ;
	if (ph->data->ph_died)
	{
		pthread_mutex_unlock(&ph->data->mtx_forks[forks[0]]);
		pthread_mutex_unlock(&ph->data->mtx_forks[forks[1]]);
		return ;
	}
	print_msg(ph, "is eating\n");
	pthread_mutex_lock(&ph->data->mtx_time);
	ph->eat_last_time = get_time_in_ms();
	pthread_mutex_unlock(&ph->data->mtx_time);
	usleep(ph->data->time_to_eat * 1000);
	pthread_mutex_unlock(&ph->data->mtx_forks[forks[0]]);
	pthread_mutex_unlock(&ph->data->mtx_forks[forks[1]]);
}

static void		*check_death(void *arg)
{
	t_ph		*ph;

	ph = (t_ph*)arg;
	pthread_mutex_lock(&ph->data->mtx_time);
	while (get_time_in_ms() - ph->eat_last_time < ph->data->time_to_die)
	{
		pthread_mutex_unlock(&ph->data->mtx_time);
		usleep(1000);
		pthread_mutex_lock(&ph->data->mtx_time);
	}
	pthread_mutex_unlock(&ph->data->mtx_time);
	if (!ph->times_to_eat)
		return (NULL);
	pthread_mutex_lock(&ph->data->mtx_death);
	if (ph->data->ph_died)
	{
		pthread_mutex_unlock(&ph->data->mtx_death);
		return (NULL);
	}
	print_msg(ph, "is died\n");
	ph->data->ph_died = 1;
	pthread_mutex_unlock(&ph->data->mtx_death);
	return (NULL);
}

void			*simulation(void *arg)
{
	t_ph		*ph;
	pthread_t	death_thread;

	ph = (t_ph*)arg;
	ph->simulation_start_time = get_time_in_ms();
	ph->eat_last_time = ph->simulation_start_time;
	pthread_create(&death_thread, NULL, check_death, ph);
	while (ph->times_to_eat)
	{
		if (ph->data->ph_died)
			break ;
		take_forks_and_eat(ph);
		if (ph->times_to_eat > 0)
			ph->times_to_eat--;
		print_msg(ph, "is sleeping\n");
		usleep(ph->data->time_to_sleep * 1000);
		if (ph->data->ph_died)
			break ;
		print_msg(ph, "is thinking\n");
	}
	pthread_join(death_thread, NULL);
	return (NULL);
}
