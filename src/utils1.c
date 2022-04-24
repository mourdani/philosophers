/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <mourdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:30:08 by mourdani          #+#    #+#             */
/*   Updated: 2022/03/24 22:48:02 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	puterr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(2, &str[i++], 1);
}

int	ft_is_number(char *n)
{
	int	i;

	i = -1;
	while (n[++i] != '\0')
	{
		if (n[i] < '0' || n[i] > '9')
			return (1);
	}
	return (0);
}

int	ft_check(unsigned long pt, int s)
{
	if (s == -1)
		return (0);
	else if (pt > 2147483647)
		return (-2);
	return (pt * s);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (ft_check(res, s));
}
