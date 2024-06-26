/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:18:16 by zzaludov          #+#    #+#             */
/*   Updated: 2023/11/29 20:18:27 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// count components in array
int	arrlen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

bool	compare(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != n)
		return (false);
	while ((!s1 && !s2) || i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i] || s1[i] == '\0')
			return (false);
		i++;
	}
	return (true);
}

void	free_memory(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

static void	validate(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32
		|| nptr[i] == 45 || nptr[i] == 43 || (nptr[i] > 47 && nptr[i] < 58)
		|| nptr[i] == '.')
		i++;
	if (nptr[i] != '\0')
	{
		ft_putendl_fd("Invalid input", 2);
		exit(1);
	}
}

// atoi for float
double	ft_atof(const char *nptr)
{
	int		i;
	double	minus;
	double	result;
	double	divisor;

	i = 0;
	minus = 1;
	result = 0;
	divisor = 0.1;
	validate(nptr);
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i++] == 45)
			minus = -1;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
		result = (nptr[i++] - '0') + (result * 10);
	if (nptr[i++] == '.')
	{
		while (nptr[i] > 47 && nptr[i] < 58)
		{
			result += (nptr[i++] - '0') * divisor;
			divisor *= 0.1;
		}
	}
	return (result * minus);
}
