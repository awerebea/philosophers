/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:47:32 by awerebea          #+#    #+#             */
/*   Updated: 2020/11/01 14:03:59 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int		init_ph(t_data *data, t_ph *ph, int i)
{
	sem_unlink("ph_finish");
	if ((ph->sem_finish = sem_open("ph_finish", O_CREAT, 0660, 0)) \
			== SEM_FAILED)
		return (1);
	ph->id = i + 1;
	ph->times_to_eat = data->times_to_eat;
	ph->data = data;
	return (0);
}

static int		process_create(t_data *data, t_ph *ph, int i)
{
	pid_t		pid;

	if ((pid = fork()) < 0)
		return (1);
	else if (!pid)
	{
		simulation(ph);
		while (1)
			usleep(1000);
	}
	else
		data->pid[i] = pid;
	return (0);
}

void			*check_finish(void *arg)
{
	t_ph		*ph;
	int			i;

	ph = (t_ph*)arg;
	i = -1;
	while (++i < ph->data->num_of_ph)
		sem_wait(ph[i].sem_finish);
	sem_post(ph->data->sem_finish);
	return (NULL);
}

static void		kill_processes(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->num_of_ph)
		kill(data->pid[i], SIGKILL);
}

int				start_processes(t_data *data)
{
	t_ph		*ph;
	pthread_t	check_thread;
	int			i;

	i = -1;
	if (!(ph = (t_ph*)malloc(sizeof(t_ph) * data->num_of_ph)) \
		|| !(data->pid = (pid_t*)malloc(sizeof(pid_t) * data->num_of_ph)))
		return (1);
	while (++i < data->num_of_ph)
	{
		if (init_ph(data, &ph[i], i))
			return (1);
		if (process_create(data, &ph[i], i))
			return (1);
	}
	if (pthread_create(&check_thread, NULL, check_finish, ph))
		return (1);
	sem_wait(data->sem_finish);
	kill_processes(data);
	i = -1;
	while (++i < data->num_of_ph)
		sem_close(ph[i].sem_finish);
	free(ph);
	free(data->pid);
	return (0);
}
