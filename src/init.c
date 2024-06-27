/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:50:20 by zzaludov          #+#    #+#             */
/*   Updated: 2024/06/24 20:50:28 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	pixel_struct(t_pointer_mlx	*p)
{
	int				i;
	int				j;

	i = 0;
	p->pixel = (t_pixel **) malloc (WIDTH * sizeof(t_pixel *));
	while (i < WIDTH)
	{
		j = 0;
		p->pixel[i] = (t_pixel *) malloc (HEIGHT * sizeof(t_pixel));
		while (j < HEIGHT)
		{
			p->pixel[i][j].rgb.r = -1;
			p->pixel[i][j].rgb.g = -1;
			p->pixel[i][j].rgb.b = -1;
			p->pixel[i][j].cam_dist = -1;
			p->pixel[i][j].light_dist = -1;
			p->pixel[i][j].object = 0;
			p->pixel[i][j].index = -1;
			p->pixel[i][j].inside = 0;
			j++;
		}
		i++;
	}
}

int	find_objs(char *file, char *obj)
{
	int		objs;
	int		fd;
	char	*line;
	char	*found;

	objs = 0;
	fd = open(file, 0);
	if (fd == -1)
		ft_printf("Opening file failure.");
	line = get_next_line(fd);
	while (line != NULL)
	{
		found = ft_strnstr(line, obj, ft_strlen(obj));
		if (found != NULL)
			objs++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (objs);
}

t_scene	*init_scene(char *file)
{
	t_scene	*scene;

	scene = malloc (sizeof(t_scene));
	scene->a = malloc (sizeof(t_ambient));
	scene->c = malloc (sizeof(t_camera));
	scene->l = malloc (sizeof(t_light));
	scene->sp = malloc ((find_objs(file, "sp") + 1) * sizeof(t_sphere *));
	scene->pl = malloc ((find_objs(file, "pl") + 1) * sizeof(t_plane *));
	scene->cy = malloc ((find_objs(file, "cy") + 1) * sizeof(t_cylinder *));
	scene->n_sp = 0;
	scene->n_pl = 0;
	scene->n_cy = 0;
	return (scene);
}

void	final_free(t_pointer_mlx *p)
{
	int	i;

	free(p->scene->a);
	free(p->scene->c);
	free(p->scene->l);
	i = 0;
	while (p->scene->sp[i] != NULL)
		free(p->scene->sp[i++]);
	free(p->scene->sp);
	i = 0;
	while (p->scene->pl[i] != NULL)
		free(p->scene->pl[i++]);
	free(p->scene->pl);
	i = 0;
	while (p->scene->cy[i] != NULL)
		free(p->scene->cy[i++]);
	free(p->scene->cy);
	free(p->scene);
	i = 0;
	while (i < WIDTH)
		free(p->pixel[i++]);
	free(p->pixel);
}
