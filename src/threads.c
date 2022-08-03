/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomaris <tkomaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:47:51 by tkomaris          #+#    #+#             */
/*   Updated: 2022/03/31 15:38:22 by tkomaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_mutex_destroy(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_philos)
		pthread_mutex_destroy(&philos[i++].fork);
}

void	*ft_thread_death(void *tmp)
{
	t_philo	*philos;

	philos = (t_philo *)tmp;
	while (1)
	{
		if (ft_get_time() - philos->t_prev_meal > philos->t_die)
		{
			action_message(philos->t_start, philos->id, "DIE");
			pthread_mutex_unlock(philos->dead);
			return (NULL);
		}
		else if (philos->meal_target != -1
			&& philos->meal_count >= philos->meal_target)
		{
			ft_usleep((int)philos->id);
			pthread_mutex_unlock(philos->meals);
			return (NULL);
		}
	}
}

void	*ft_thread_enough_meal(void *tmp)
{
	t_philo	*philos;
	int		enough_meal;

	enough_meal = 0;
	philos = (t_philo *)tmp;
	if (philos->meal_target != 0)
		pthread_mutex_lock(philos->meals);
	while (philos->meal_target != 0 && enough_meal < philos->num_philos)
	{
		pthread_mutex_lock(philos->meals);
		enough_meal++;
	}
	action_message(philos->t_start, 0, "OVER");
	pthread_mutex_unlock(philos->dead);
	return (NULL);
}

void	*ft_thread_philos(void *tmp)
{
	pthread_t	thread;
	t_philo		*philos;

	philos = (t_philo *)tmp;
	pthread_create(&thread, NULL, ft_thread_death, philos);
	if (!(philos->id % 2))
		ft_usleep((int)philos->t_eat * 0.9 + 1);
	while (philos->meal_target == -1
		|| philos->meal_target > philos->meal_count)
	{
		pthread_mutex_lock(&philos->fork);
		action_message(philos->t_start, philos->id, "FORK");
		pthread_mutex_lock(philos->prev_fork);
		action_message(philos->t_start, philos->id, "FORK");
		philos->t_prev_meal = ft_get_time();
		action_message(philos->t_start, philos->id, "EAT");
		ft_usleep(philos->t_eat);
		pthread_mutex_unlock(&philos->fork);
		pthread_mutex_unlock(philos->prev_fork);
		philos->meal_count++;
		action_message(philos->t_start, philos->id, "SLEEP");
		ft_usleep(philos->t_sleep);
		action_message(philos->t_start, philos->id, "THINK");
	}
	return (NULL);
}

void	ft_philo(t_philo *philos)
{
	int				i;
	pthread_mutex_t	dead;
	pthread_mutex_t	meals;
	pthread_t		thread;

	pthread_mutex_init(&dead, NULL);
	pthread_mutex_init(&meals, NULL);
	philos[0].prev_fork = &philos[philos[0].num_philos - 1].fork;
	pthread_mutex_lock(&dead);
	i = 0;
	while (i < philos[0].num_philos)
	{
		philos[i].dead = &dead;
		philos[i].meals = &meals;
		pthread_create(&thread, NULL, ft_thread_philos, &philos[i++]);
	}
	if (philos[0].meal_target != -1)
		pthread_create(&thread, NULL, ft_thread_enough_meal, &philos[0]);
	pthread_mutex_lock(&dead);
	ft_mutex_destroy(philos);
	pthread_mutex_destroy(&dead);
	pthread_mutex_destroy(&meals);
	free(philos);
}
