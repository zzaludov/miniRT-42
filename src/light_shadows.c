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

int	find_shadow(t_pointer_mlx *p, int x, int y, t_coord light_dir)
{
	int	i;
	double	t;
	t_coord	bias;
	
	bias = vector_add(p->scene->l->pos, vector_scale(light_dir, -1 * EPSILON));
	i = 0;
	while (i < p->scene->n_sp)
	{
		if ((i != p->pixel[x][y].index || p->pixel[x][y].object != 's')
			&& intersect_sphere(bias, light_dir, p->scene->sp[i], &t)
			&& t > 0 && t < p->pixel[x][y].light_dist)
			return (0);
		i++;
	}
	i = 0;
	while (i < p->scene->n_cy)
	{
		if ((p->pixel[x][y].object != 'c' ||  p->pixel[x][y].index != i)
			&& intersect_cylinder(bias, light_dir, p->scene->cy[i], &t)
			 && t > 0 && t < p->pixel[x][y].light_dist)
			return (0);
		if ((p->pixel[x][y].object != 'd' || p->pixel[x][y].index != i)
			&& intersect_disk(bias, light_dir, p->scene->cy[i], &t)
			 && t > 0 && t < p->pixel[x][y].light_dist)
				return (0);
		i++;
	}
	i = 0;
	while (i < p->scene->n_pl)
	{

		if ((p->pixel[x][y].object != 'p' || p->pixel[x][y].index != i)
			&& intersect_plane(bias, light_dir, p->scene->pl[i], &t)
			&& t > 0 && t < p->pixel[x][y].light_dist)
				return (0);
		i++;
	}
	return 1;
}

