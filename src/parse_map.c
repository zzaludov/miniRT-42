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

void	parse_objects(t_pointer_mlx *p, char **spl)
{
	if (compare(spl[0], "sp", 2) && arrlen(spl) == 4)
	{
		p->scene->sp[p->scene->n_sp] = malloc(sizeof(t_sphere));
		p->scene->sp[p->scene->n_sp]->pos = split_xyz(spl[1]);
		p->scene->sp[p->scene->n_sp]->diameter = ft_atof(spl[2]);
		p->scene->sp[p->scene->n_sp++]->rgb = split_rgb(spl[3]);
	}
	else if (compare(spl[0], "pl", 2) && arrlen(spl) == 4)
	{
		p->scene->pl[p->scene->n_pl] = malloc(sizeof(t_plane));
		p->scene->pl[p->scene->n_pl]->pos = split_xyz(spl[1]);
		p->scene->pl[p->scene->n_pl]->dir = split_xyz(spl[2]);
		p->scene->pl[p->scene->n_pl++]->rgb = split_rgb(spl[3]);
	}
	else if (compare(spl[0], "cy", 2) && arrlen(spl) == 6)
	{
		p->scene->cy[p->scene->n_cy] = malloc(sizeof(t_cylinder));
		p->scene->cy[p->scene->n_cy]->pos = split_xyz(spl[1]);
		p->scene->cy[p->scene->n_cy]->dir = split_xyz(spl[2]);
		p->scene->cy[p->scene->n_cy]->diameter = ft_atof(spl[3]);
		p->scene->cy[p->scene->n_cy]->height = ft_atof(spl[4]);
		p->scene->cy[p->scene->n_cy++]->rgb = split_rgb(spl[5]);
	}
	else
	{
		free_memory((void **) spl);
		// error
	}
}

void	parse_elements(t_pointer_mlx *p, char **spl)
{
	if (arrlen(spl) > 1)
	{
		if (compare(spl[0], "A", 1) && arrlen(spl) == 3)
		{
			p->scene->a->ratio = ft_atof(spl[1]);
			p->scene->a->rgb = split_rgb(spl[2]);
		}
		else if (compare(spl[0], "C", 1) && arrlen(spl) == 4)
		{
			p->scene->c->pos = split_xyz(spl[1]);
			p->scene->c->dir = split_xyz(spl[2]);
			p->scene->c->fov = ft_atof(spl[3]);
		}
		else if (compare(spl[0], "L", 1) && arrlen(spl) == 4)
		{
			p->scene->l->pos = split_xyz(spl[1]);
			p->scene->l->brightness = ft_atof(spl[2]);
			p->scene->l->rgb = split_rgb(spl[3]);
		}
		else
			parse_objects(p, spl);
	}
}

void	open_map(t_pointer_mlx* p)
{
	int				fd;
	char			*line;
	char			**spl;

	fd = open(p->map_name, 0);
	if (fd == -1)
		ft_printf("Opening file failure."); //error
	line = get_next_line(fd);
	while (line != NULL)
	{
		spl = ft_split(line, ' ');
		parse_elements(p, spl);
		free_memory((void**)spl);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	p->scene->sp[p->scene->n_sp] = NULL;
	p->scene->pl[p->scene->n_pl] = NULL;
	p->scene->cy[p->scene->n_cy] = NULL;
}
