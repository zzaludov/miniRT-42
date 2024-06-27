/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:18:16 by zzaludov          #+#    #+#             */
/*   Updated: 2024/06/27 20:26:41 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	skip_whitespace_and_sign(const char **nptr, double *minus)
{
	int	i;

	i = 0;
	while (((*nptr)[i] > 8 && (*nptr)[i] < 14) || (*nptr)[i] == 32)
		i++;
	if ((*nptr)[i] == 45 || (*nptr)[i] == 43)
	{
		if ((*nptr)[i++] == 45)
			*minus = -1;
	}
	*nptr += i;
}

double	parse_number(const char **nptr, double *minus)
{
	double	result;
	double	divisor;

	result = 0;
	divisor = 0.1;
	while (**nptr > 47 && **nptr < 58)
	{
		result = ((**nptr) - '0') + (result * 10);
		(*nptr)++;
	}
	if (**nptr == '.')
	{
		(*nptr)++;
		while (**nptr > 47 && **nptr < 58)
		{
			result += ((**nptr) - '0') * divisor;
			divisor *= 0.1;
			(*nptr)++;
		}
	}
	return (result * (*minus));
}

double	ft_atof(const char *nptr)
{
	double	minus;

	minus = 1;
	validate(nptr);
	skip_whitespace_and_sign(&nptr, &minus);
	return (parse_number(&nptr, &minus));
}
