/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:10:47 by zzaludov          #+#    #+#             */
/*   Updated: 2024/06/27 19:07:27 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_camera_sq_pl(char **spl, char flag)
{
	t_coord	coord;
	t_color	color;
	double	fov;

	validate_xyz(spl, flag);
	if (flag == 'c')
		fov = ft_atof(spl[3]);
	else if (flag == 'y')
		color = split_rgb(spl[5]);
	else
		color = split_rgb(spl[4]);
	coord = split_xyz(spl[2], flag);
	if ((coord.x < -1 || coord.x > 1)
		|| (coord.y < -1 || coord.y > 1)
		|| (coord.z < -1 || coord.z > 1))
		print_to_exit("Incorrect 3d vector");
	else if ((flag == 'q' || flag == 'y') && ((color.r < 0 || color.r > 255)
			|| (color.b < 0 || color.b > 255)
			|| (color.g < 0 || color.g > 255)))
		print_to_exit("Incorrect RGB range");
	else if (flag == 'c' && (fov < 0 || fov > 180))
		print_to_exit("Incorrect fov range");
	else
		return ;
	exit (1);
}

void	validate_light_sphere(char **spl, char flag)
{
	double	brightness;
	t_color	color;

	validate_xyz(spl, flag);
	if (flag == 'l')
		brightness = ft_atof(spl[2]);
	color = split_rgb(spl[3]);
	if (flag == 'l' && (brightness < 0 || brightness > 1))
		print_to_exit("Brightness out of range");
	else if ((color.r < 0 || color.r > 255)
		|| (color.b < 0 || color.b > 255)
		|| (color.g < 0 || color.g > 255))
		print_to_exit("Incorrect RGB range");
	else
		return ;
	exit(1);
}

void	validate_objects(char **spl)
{
	if (!compare(spl[0], "sp", 2) && !compare(spl[0], "pl", 2)
		&& !compare(spl[0], "sq", 2) && !compare(spl[0], "cy", 2))
		print_to_exit("Incorrect object name");
	else if (compare(spl[0], "sp", 2) && arrlen(spl) == 4)
		validate_light_sphere(spl, 's');
	else if (compare(spl[0], "sq", 2) && arrlen(spl) == 4)
		validate_camera_sq_pl(spl, 'q');
	else if (compare(spl[0], "pl", 2) && arrlen(spl) == 4)
		validate_light_sphere(spl, 'p');
	else if (compare(spl[0], "cy", 2) && arrlen(spl) == 6)
		validate_camera_sq_pl(spl, 'y');
}

void	validate_elements(char **spl)
{
	static int	a = 0;
	static int	c = 0;
	static int	l = 0;

	if (a > 1 || c > 1 || l > 1)
		print_to_exit("Wrong amount of classifiers");
	if (spl && compare(spl[0], "A", 1) && arrlen(spl) == 3)
	{
		validate_ambient(spl);
		a++;
	}
	else if (spl && compare(spl[0], "C", 1) && arrlen(spl) == 4)
	{
		validate_camera_sq_pl(spl, 'c');
		c++;
	}
	else if (spl && compare(spl[0], "L", 1) && arrlen(spl) == 4)
	{
		validate_light_sphere(spl, 'l');
		l++;
	}
	else
		validate_objects(spl);
}

void	validate_map(char *map_name, t_pointer_mlx *p)
{
	int				fd;
	char			*line;
	char			**spl;

	fd = open(map_name, 0);
	if (fd == -1)
		handle_esc(p);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) <= 2)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		spl = ft_split(line, '\n');
		spl = ft_split(spl[0], ' ');
		validate_elements(spl);
		free_memory((void **)spl);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
