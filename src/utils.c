/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:43:27 by gshim             #+#    #+#             */
/*   Updated: 2022/04/12 14:21:17 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	get_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

static int	get_ret(int sign)
{
	if (sign < 0)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	char		*s;
	long long	ret;
	int			i;
	int			sign;

	s = (char *)str;
	ret = 0;
	i = 0;
	while ((9 <= s[i] && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
		sign = get_sign(s[i++]);
	else
		sign = 1;
	while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
	{
		ret = (ret * 10) + (s[i] - '0');
		if (!(INT_MIN <= ret * sign && ret * sign <= INT_MAX))
			return (get_ret(sign));
		i++;
	}
	ret *= sign;
	return ((int)ret);
}
