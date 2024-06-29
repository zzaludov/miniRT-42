/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:23 by nandroso          #+#    #+#             */
/*   Updated: 2024/06/27 21:43:34 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_ambient(char **spl)
{
	double	light_range;
	t_color	color;

	color = split_rgb(spl[2]);
	light_range = ft_atof(spl[1]);
	if (!light_range || light_range < 0 || light_range > 1)
		print_to_exit("Incorrect ambient lightning range");
	else if ((!color.r || color.r < 0 || color.r > 255)
		|| (!color.b || color.b < 0 || color.b > 255)
		|| (!color.b || color.g < 0 || color.g > 255))
		print_to_exit("Incorrect RGB range");
	else
		return ;
	exit(1);
}

void	validate_xyz(char **spl, char flag)
{
	t_coord	pos;

	pos = split_xyz(spl[1], flag);
	(void)pos;
}
