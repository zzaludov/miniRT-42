/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:10:47 by zzaludov          #+#    #+#             */
/*   Updated: 2024/06/27 21:45:34 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	split_rgb(char *str)
{
	t_color	color;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (split[i] != NULL)
		i++;
	if (i != 3)
		print_to_exit("Incorrect format");
	color.r = ft_atoi(split[0]);
	color.g = ft_atoi(split[1]);
	color.b = ft_atoi(split[2]);
	free_memory((void **) split);
	return (color);
}

t_coord	split_xyz(char *str, char flag)
{
	t_coord	coord;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (split[i] != NULL)
		i++;
	if (flag != 'p' && i != 3)
		print_to_exit("Incorrect format");
	else if (flag == 'p' && i < 2)
		print_to_exit("Incorrect format");
	coord.x = ft_atof(split[0]);
	coord.y = ft_atof(split[1]);
	if (split[2])
		coord.z = ft_atof(split[2]);
	else
		coord.z = 0;
	free_memory((void **) split);
	return (coord);
}
