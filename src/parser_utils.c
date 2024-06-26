/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:10:47 by zzaludov          #+#    #+#             */
/*   Updated: 2023/11/27 20:10:59 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	split_rgb(char *str)
{
	t_color	color;
	char	**split;

	split = ft_split(str, ',');
	color.r = ft_atoi(split[0]);
	color.g = ft_atoi(split[1]);
	color.b = ft_atoi(split[2]);
	free_memory((void **) split);
	return (color);
}

t_coord	split_xyz(char *str)
{
	t_coord	coord;
	char	**split;

	split = ft_split(str, ',');
	coord.x = ft_atof(split[0]);
	coord.y = ft_atof(split[1]);
	coord.z = ft_atof(split[2]);
	free_memory((void **) split);
	return (coord);
}
