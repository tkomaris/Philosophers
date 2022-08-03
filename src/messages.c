/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomaris <tkomaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:45:46 by tkomaris          #+#    #+#             */
/*   Updated: 2022/03/31 15:41:43 by tkomaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	action_message(long time, int id, char *status)
{
	long	tmp;

	tmp = ft_get_time() - time;
	if (id == 0)
		printf("%ld\tTarget number of meals reached\n", tmp);
	else if (!ft_strcmp(status, "EAT"))
		printf("%ld\t%d is eating\n", tmp, id);
	else if (!ft_strcmp(status, "SLEEP"))
		printf("%ld\t%d is sleeping\n", tmp, id);
	else if (!ft_strcmp(status, "THINK"))
		printf("%ld\t%d is thinking\n", tmp, id);
	else if (!ft_strcmp(status, "DIE"))
		printf("%ld\t%d died\n", tmp, id);
	else if (!ft_strcmp(status, "FORK"))
		printf("%ld\t%d has taken a fork\n", tmp, id);
}

int	error_message(void)
{
	printf("Error: wrong input.\n");
	printf("Correct input: ./philo [num of philos] ");
	printf("[time to die] [time to eat] [time to sleep]");
	return (1);
}
