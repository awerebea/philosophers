/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:46 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/31 21:15:45 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef struct	s_data
{
	int				num_of_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				ph_died;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_death;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_time;
}				t_data;

typedef struct	s_ph
{
	int				id;
	int				simulation_start_time;
	int				eat_last_time;
	int				times_to_eat;
	t_data			*data;
}				t_ph;

void			f_sleep(int t);
int				ft_atoi(char *str);
int				ft_isdigit(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
int				get_time_in_ms(void);
int				ret_msg(char *str, int errcode);
void			*simulation(void *arg);
int				start_threads(t_data *data);

#endif
