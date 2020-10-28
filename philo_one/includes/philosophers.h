/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:46 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/28 23:02:20 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef struct	s_data
{
	int				num_of_ph;
	int				tm_to_die;
	int				tm_to_eat;
	int				tm_to_slp;
	int				num_to_eat;
	int				ph_died;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_death;
	pthread_mutex_t	mtx_out;
	pthread_mutex_t	mtx_time;
}				t_data;

typedef struct	s_ph
{
	int				id;
	int				tm_sim_start;
	int				tm_meal;
	int				num_to_eat;
	t_data			*data;
}				t_ph;

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
