/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:37:46 by awerebea          #+#    #+#             */
/*   Updated: 2020/10/27 22:27:28 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
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

int				ft_atoi(char *str);
int				ft_isdigit(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
int				init_data(t_data *data, char **argv);
int				ret_msg(char *str, int errcode);

#endif
