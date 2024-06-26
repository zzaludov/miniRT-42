/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:11:24 by zzaludov          #+#    #+#             */
/*   Updated: 2024/06/18 18:11:34 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	pixel_info(t_pixel *pixel, double dist, char obj, int i)
{
	if (pixel->rgb.r == -1
		|| (dist < pixel->cam_dist && dist >= 0))
	{
		pixel->object = obj;
		pixel->index = i;
		pixel->cam_dist = dist;
		return (1);
	}
	return (0);
}

void	pixel_info2(t_pixel *pixel, t_color color, int inside)
{
	pixel->rgb = color;
	pixel->inside = inside;
}

void	find_intersection_cy(t_pointer_mlx *p, t_pixel *pixel, t_coord ray_dir)
{
	int		i;
	double	t;

	i = 0;
	while (i < p->scene->n_cy)
	{
		p->scene->cy[i]->dir = normalized(p->scene->cy[i]->dir);
		if (intersect_cy(p->scene->c->pos, ray_dir, p->scene->cy[i], &t))
		{
			if (pixel_info(pixel, t, 'c', i))
				pixel_info2(pixel,
					p->scene->cy[i]->rgb, p->scene->cy[i]->inside);
		}
		if (intersect_disk(p->scene->c->pos, ray_dir, p->scene->cy[i], &t))
		{
			if (pixel_info(pixel, t, 'd', i))
				pixel_info2(pixel,
					p->scene->cy[i]->rgb, p->scene->cy[i]->inside);
		}
		i++;
	}
}

void	find_intersection(t_pointer_mlx *p, t_pixel *pixel, t_coord ray_dir)
{
	int		i;
	double	t;

	i = 0;
	while (i < p->scene->n_sp)
	{
		if (intersect_sp(p->scene->c->pos, ray_dir, p->scene->sp[i], &t))
		{
			if (pixel_info(pixel, t, 's', i))
				pixel_info2(pixel,
					p->scene->sp[i]->rgb, p->scene->sp[i]->inside);
		}
		i++;
	}
	find_intersection_cy(p, pixel, ray_dir);
	i = 0;
	while (i < p->scene->n_pl)
	{
		if (intersect_pl(p->scene->c->pos, ray_dir, p->scene->pl[i], &t))
		{
			if (pixel_info(pixel, t, 'p', i))
				pixel_info2(pixel, p->scene->pl[i]->rgb, 0);
		}
		i++;
	}
}
