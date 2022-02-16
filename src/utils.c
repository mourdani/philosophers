/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 03:36:18 by mourdani          #+#    #+#             */
/*   Updated: 2022/02/16 03:44:10 by mourdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	ft_is_whitespace(char character)
{
	return (character == '\n'
		|| character == '\t'
		|| character == '\v'
		|| character == '\r'
		|| character == '\f'
		|| character == ' '
	);
}

bool	ft_is_plus_or_minus(char character)
{
	return (character == '+' || character == '-');
}

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *number_pointer)
{
	int	number;
	int	sign;
	int	previous_number;

	number = 0;
	sign = -1;
	previous_number = 0;
	while (ft_is_whitespace(*number_pointer))
		number_pointer++;
	if (ft_is_plus_or_minus(*number_pointer))
		if (*number_pointer++ == '-')
			sign = 1;
	while (ft_isdigit(*number_pointer))
	{
		number *= 10;
		number -= (*number_pointer++ - '0');
		if (previous_number < number)
		{
			if (sign < 0)
				return (-1);
			return (0);
		}
		previous_number = number;
	}
	return (number * sign);
}
