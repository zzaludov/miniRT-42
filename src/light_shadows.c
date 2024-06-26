/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:12:30 by zzaludov          #+#    #+#             */
/*   Updated: 2024/06/18 18:12:34 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_shadow_sp(t_pointer_mlx *p, t_pixel *pixel, t_coord light_dir)
{
	int		i;
	double	t;
	t_coord	bias;

	bias = vector_add(pixel->intersection,
			vector_scale(pixel->normal, 1 * EPSILON));
	i = 0;
	while (i < p->scene->n_sp)
	{
		if ((i != pixel->index || pixel->object != 's')
			&& intersect_sp(bias, light_dir, p->scene->sp[i], &t)
			&& t > 0 && t < pixel->light_dist)
			return (0);
		i++;
	}
	return (1);
}

int	find_shadow_cy(t_pointer_mlx *p, t_pixel *pixel, t_coord light_dir)
{
	int		i;
	double	t;
	t_coord	bias;

	bias = vector_add(pixel->intersection,
			vector_scale(pixel->normal, 1 * EPSILON));
	i = 0;
	while (i < p->scene->n_cy)
	{
		if ((pixel->object != 'c' || pixel->index != i)
			&& intersect_cy(bias, light_dir, p->scene->cy[i], &t)
			&& t > 0 && t < pixel->light_dist)
			return (0);
		if ((pixel->object != 'd' || pixel->index != i)
			&& intersect_disk(bias, light_dir, p->scene->cy[i], &t)
			&& t > 0 && t < pixel->light_dist)
			return (0);
		i++;
	}
	return (1);
}

int	find_shadow_pl(t_pointer_mlx *p, t_pixel *pixel, t_coord light_dir)
{
	int		i;
	double	t;
	t_coord	bias;

	bias = vector_add(pixel->intersection,
			vector_scale(pixel->normal, 1 * EPSILON));
	i = 0;
	while (i < p->scene->n_pl)
	{
		if ((pixel->object != 'p' || pixel->index != i)
			&& intersect_pl(bias, light_dir, p->scene->pl[i], &t)
			&& t > 0 && t < pixel->light_dist)
			return (0);
		i++;
	}
	return (1);
}

int	find_shadow(t_pointer_mlx *p, t_pixel *pixel, t_coord light_dir)
{
	if (!find_shadow_sp(p, pixel, light_dir))
		return (0);
	if (!find_shadow_cy(p, pixel, light_dir))
		return (0);
	if (!find_shadow_pl(p, pixel, light_dir))
		return (0);
	return (1);
}
