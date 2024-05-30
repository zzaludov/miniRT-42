/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:10:47 by zzaludov          #+#    #+#             */
/*   Updated: 2023/11/27 20:10:59 by zzaludov         ###   ########.fr       */
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
		ft_putendl_fd("Incorrect ambient lightning range", 2);
	else if ((!color.r || color.r < 0 || color.r > 255)
		|| (!color.b || color.b < 0 || color.b > 255)
		|| (!color.b || color.g < 0 || color.g > 255))
		ft_putendl_fd("Incorrect RGB range", 2);
	else
		return ;
	exit(1);
}

void	validate_camera_sq_pl(char **spl, char flag)
{
	t_coord	coord;
	t_color	color;
	double	fov;

	if (flag == 'c')
		fov = ft_atof(spl[3]);
	else if (flag == 'y')
		color = split_rgb(spl[5]);
	else
		color = split_rgb(spl[4]);
	coord = split_xyz(spl[2]);
	if ((coord.x < -1 || coord.x > 1)
		|| (coord.y < -1 || coord.y > 1)
		|| (coord.z < -1 || coord.z > 1))
		ft_putendl_fd("Incorrect 3d vector", 2);
	else if ((flag == 'q' || flag == 'y') && ((color.r < 0 || color.r > 255)
			|| (color.b < 0 || color.b > 255)
			|| (color.g < 0 || color.g > 255)))
		ft_putendl_fd("Incorrect RGB range", 2);
	else if (flag == 'c' && (fov < 0 || fov > 180))
		ft_putendl_fd("Incorrect fov range", 2);
	else
		return ;
	exit (1);
}

void	validate_light_sphere(char **spl, char flag)
{
	double	brightness;
	t_color	color;

	if (flag == 'l')
		brightness = ft_atof(spl[2]);
	color = split_rgb(spl[3]);
	if (flag == 'l' && (brightness < 0 || brightness > 1))
		ft_putendl_fd("Brightness out of range", 2);
	else if ((color.r < 0 || color.r > 255)
		|| (color.b < 0 || color.b > 255)
		|| (color.g < 0 || color.g > 255))
		ft_putendl_fd("Incorrect RGB range", 2);
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
		validate_light_sphere(spl, 'q');
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

void	validate_map(char *map_name)
{
	int				fd;
	char			*line;
	char			**spl;

	fd = open(map_name, 0);
	if (fd == -1)
		print_to_exit("Opening file failure.");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) <= 2)
		{
			line = get_next_line(fd);
			continue ;
		}
		spl = ft_split(line, ' ');
		validate_elements(spl);
		free_memory((void **)spl);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
