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

void	parse_objects_plane_cylinder(t_pointer_mlx *p, char **spl)
{
	if (compare(spl[0], "pl", 2) && arrlen(spl) == 4)
	{
		p->scene->pl[p->scene->n_pl] = malloc(sizeof(t_plane));
		p->scene->pl[p->scene->n_pl]->pos = split_xyz(spl[1], 'p');
		p->scene->pl[p->scene->n_pl]->dir = split_xyz(spl[2], 'n');
		p->scene->pl[p->scene->n_pl]->highlighted = 0;
		p->scene->pl[p->scene->n_pl++]->rgb = split_rgb(spl[3]);
	}
	else if (compare(spl[0], "cy", 2) && arrlen(spl) == 6)
	{
		p->scene->cy[p->scene->n_cy] = malloc(sizeof(t_cylinder));
		p->scene->cy[p->scene->n_cy]->pos = split_xyz(spl[1], 'c');
		p->scene->cy[p->scene->n_cy]->dir = split_xyz(spl[2], 'c');
		p->scene->cy[p->scene->n_cy]->diameter = ft_atof(spl[3]);
		p->scene->cy[p->scene->n_cy]->height = ft_atof(spl[4]);
		p->scene->cy[p->scene->n_cy]->highlighted = 0;
		p->scene->cy[p->scene->n_cy]->inside = 0;
		p->scene->cy[p->scene->n_cy++]->rgb = split_rgb(spl[5]);
	}
	else
	{
		free_memory((void **) spl);
		mlx_close_window(p->mlx);
	}
}

void	parse_objects_sphere(t_pointer_mlx *p, char **spl)
{
	if (compare(spl[0], "sp", 2) && arrlen(spl) == 4)
	{
		p->scene->sp[p->scene->n_sp] = malloc(sizeof(t_sphere));
		p->scene->sp[p->scene->n_sp]->pos = split_xyz(spl[1], 's');
		p->scene->sp[p->scene->n_sp]->diameter = ft_atof(spl[2]);
		p->scene->sp[p->scene->n_sp]->highlighted = 0;
		p->scene->sp[p->scene->n_sp]->inside = 0;
		p->scene->sp[p->scene->n_sp++]->rgb = split_rgb(spl[3]);
	}
	else
		parse_objects_plane_cylinder(p, spl);
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
			p->scene->c->pos = split_xyz(spl[1], 'c');
			p->scene->c->dir = split_xyz(spl[2], 'c');
			p->scene->c->fov = ft_atof(spl[3]);
		}
		else if (compare(spl[0], "L", 1) && arrlen(spl) == 4)
		{
			p->scene->l->pos = split_xyz(spl[1], 'l');
			p->scene->l->brightness = ft_atof(spl[2]);
			p->scene->l->rgb = split_rgb(spl[3]);
		}
		else
			parse_objects_sphere(p, spl);
	}
}

void	open_map(t_pointer_mlx *p)
{
	int				fd;
	char			*line;
	char			**spl;
	// char			*tmp;

	p->scene = init_scene(p->map_name);
	fd = open(p->map_name, 0);
	if (fd == -1)
		ft_printf("Opening file failure.");
	line = get_next_line(fd);
	while (line != NULL)
	{
		// spl = ft_split(line, '\n');
		// tmp = spl[0];
		// free_memory((void **)spl);
		spl = ft_split(line, ' ');
		
		parse_elements(p, spl);
		free_memory((void **)spl);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	p->scene->sp[p->scene->n_sp] = NULL;
	p->scene->pl[p->scene->n_pl] = NULL;
	p->scene->cy[p->scene->n_cy] = NULL;
}
