/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:31:43 by zzaludov          #+#    #+#             */
/*   Updated: 2023/02/16 22:27:12 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	validate(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32
			|| nptr[i] == 45 || nptr[i] == 43 || (nptr[i] > 47 && nptr[i] < 58))
			i++;
	if (nptr[i] != '\0')
	{
		ft_putendl_fd("Invalid input", 2);
		exit(1);
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	minus;
	int	result;

	i = 0;
	minus = 0;
	result = 0;
	validate(nptr);
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i] == 45)
			minus++;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		result = (nptr[i] - '0') + (result * 10);
		i++;
	}
	if (minus == 1)
		result = -result;
	return (result);
}
