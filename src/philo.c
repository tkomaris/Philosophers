/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomaris <tkomaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:45:54 by tkomaris          #+#    #+#             */
/*   Updated: 2022/03/31 15:40:01 by tkomaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_arg_check(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_init(t_philo *philos, char **argv, int tmp)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&philos[i].fork, NULL);
		if (i != 0)
			philos[i].prev_fork = &philos[i - 1].fork;
		else
			philos[i].prev_fork = NULL;
		philos[i].num_philos = ft_atoi(argv[1]);
		philos[i].t_die = ft_atoi(argv[2]);
		philos[i].t_eat = ft_atoi(argv[3]);
		philos[i].t_sleep = ft_atoi(argv[4]);
		philos[i].t_start = ft_get_time();
		philos[i].meal_target = tmp;
		philos[i].t_prev_meal = philos[i].t_start;
		philos[i].meal_count = 0;
		philos[i].id = i + 1;
		philos[i].finished = 0;
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (!(ft_arg_check(argc, argv)) || !(ft_atoi(argv[1])))
		return (error_message());
	philos = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (0);
	if (argc == 6)
		ft_init(philos, argv, ft_atoi(argv[5]));
	else
		ft_init(philos, argv, -1);
	ft_philo(philos);
	return (0);
}
