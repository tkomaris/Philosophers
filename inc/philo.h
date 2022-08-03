/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomaris <tkomaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:48:24 by tkomaris          #+#    #+#             */
/*   Updated: 2022/03/31 15:46:22 by tkomaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num_philos;
	int				meal_target;
	int				id;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meal_count;
	long			t_start;
	long			t_prev_meal;
	int				*finished;
	pthread_mutex_t	*prev_fork;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*meals;
	pthread_mutex_t	fork;
}				t_philo;

int		ft_isdigit(char *str);
long	ft_get_time(void);
void	ft_usleep(int len);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	action_message(long time, int id, char *status);
int		error_message(void);
void	ft_philo(t_philo *philos);

#endif
