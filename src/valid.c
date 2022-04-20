/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:26:59 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 17:44:58 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	is_num(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	is_overflow(char *input)
{
	if (input[0] == '-' && ft_atoi(input) > 0)
		return (1);
	if (input[0] != '-' && ft_atoi(input) < 0)
		return (1);
	return (0);
}

int	is_valid(char *input)
{
	int	i;
	int	len;

	i = 0;
	if (input[i] == '-' && !is_num(input[i + 1]))
		return (0);
	if (input[i] == '-' && is_num(input[i + 1]))
		i++;
	len = ft_strlen(&input[i]);
	if (len > 10)
		return (0);
	while (input[i])
	{
		if (!is_num(input[i]))
			return (0);
		i++;
	}
	if (len == 10 && is_overflow(input))
		return (0);
	return (1);
}
