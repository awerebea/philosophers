/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:04:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/30 22:18:06 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>

static void		print_msg(t_ph *ph, char *msg)
{
	sem_wait(ph->data->sem_print);
	if (ph->ph_died)
	{
		sem_post(ph->data->sem_print);
		return ;
	}
	ft_putnbr_fd(get_time_in_ms() - ph->simulation_start_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(ph->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(msg, 1);
	sem_post(ph->data->sem_print);
}

static int		take_forks_assist(t_ph *ph)
{
	sem_wait(ph->data->sem_waiter);
	sem_wait(ph->data->sem_forks);
	if (ph->ph_died)
	{
		sem_post(ph->data->sem_waiter);
		sem_post(ph->data->sem_forks);
		return (1);
	}
	print_msg(ph, "has taken a fork\n");
	sem_wait(ph->data->sem_forks);
	if (ph->ph_died)
	{
		sem_post(ph->data->sem_waiter);
		sem_post(ph->data->sem_forks);
		return (1);
	}
	sem_wait(ph->data->sem_forks);
	print_msg(ph, "has taken a fork\n");
	sem_post(ph->data->sem_waiter);
	return (0);
}

static void		take_forks_and_eat(t_ph *ph)
{
	if (take_forks_assist(ph))
		return ;
	if (ph->ph_died)
	{
		sem_post(ph->data->sem_forks);
		sem_post(ph->data->sem_forks);
		return ;
	}
	print_msg(ph, "is eating\n");
	sem_wait(ph->data->sem_time);
	ph->eat_last_time = get_time_in_ms();
	sem_post(ph->data->sem_time);
	usleep(ph->data->time_to_eat * 1000);
	sem_post(ph->data->sem_forks);
	sem_post(ph->data->sem_forks);
}

static void		*check_death(void *arg)
{
	t_ph		*ph;

	ph = (t_ph*)arg;
	sem_wait(ph->data->sem_time);
	while (get_time_in_ms() - ph->eat_last_time < ph->data->time_to_die)
	{
		sem_post(ph->data->sem_time);
		usleep(1000);
		sem_wait(ph->data->sem_time);
	}
	sem_post(ph->data->sem_time);
	if (!ph->times_to_eat)
	{
		sem_post(ph->sem_finish);
		return (NULL);
	}
	sem_wait(ph->data->sem_death);
	print_msg(ph, "is died\n");
	ph->ph_died = 1;
	sem_post(ph->data->sem_finish);
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
		if (ph->ph_died)
			break ;
		take_forks_and_eat(ph);
		if (ph->ph_died)
			break ;
		if (ph->times_to_eat > 0)
			ph->times_to_eat--;
		print_msg(ph, "is sleeping\n");
		usleep(ph->data->time_to_sleep * 1000);
		if (ph->ph_died)
			break ;
		print_msg(ph, "is thinking\n");
	}
	pthread_join(death_thread, NULL);
	return (NULL);
}
