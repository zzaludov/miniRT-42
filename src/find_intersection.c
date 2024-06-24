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

t_pixel	pixel_info(t_pixel *prev, t_color color, double dist, char obj, int i)
{
	t_pixel	pixel;

	if (prev->rgb.r == -1
		|| (dist < prev->cam_dist && dist >= 0))
	{
		pixel.rgb = color;
        pixel.cam_dist = dist;
		pixel.object = obj;
		pixel.index = i;
	}
	else
		pixel = *prev;
	return (pixel);
}

// t_pixel	pixel_info(t_pixel *prev, t_color color, double dist, char obj, int i)
// {
// 	t_pixel	pixel;

// 	if (prev->rgb.r == -1
// 		|| (dist < prev->cam_dist && dist >= 0))
// 	{
// 		pixel.rgb = color;
//         pixel.cam_dist = dist;
// 		pixel.object = obj;
// 		pixel.index = i;
// 	}
// 	else
// 		pixel = *prev;
// 	return (pixel);
// }

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
			*pixel = pixel_info(pixel, p->scene->cy[i]->rgb, t, 'c', i);
		}
		if (intersect_disk(p->scene->c->pos, ray_dir, p->scene->cy[i], &t))
		{
			*pixel = pixel_info(pixel, p->scene->cy[i]->rgb, t, 'd', i);
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
			*pixel = pixel_info(pixel, p->scene->sp[i]->rgb, t, 's', i);
		}
		i++;
	}
	find_intersection_cy(p, pixel, ray_dir);
	i = 0;
	while (i < p->scene->n_pl)
	{
		if (intersect_pl(p->scene->c->pos, ray_dir, p->scene->pl[i], &t))
		{
			*pixel = pixel_info(pixel, p->scene->pl[i]->rgb, t, 'p', i);
		}
		i++;
	}
}
