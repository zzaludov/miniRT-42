/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:35:57 by zzaludov          #+#    #+#             */
/*   Updated: 2023/12/06 21:36:00 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	find_highlited(t_pointer_mlx *p, mlx_key_data_t keys)
{
	int	i;

	i = -1;
	while (++i < p->scene->n_cy)
		if (p->scene->cy[i]->highlighted == 1)
			cylinder_manipulation(p->scene, p->scene->cy[i], keys);
	i = -1;
	while (++i < p->scene->n_pl)
		if (p->scene->pl[i]->highlighted == 1)
			plane_manipulation(p->scene, p->scene->pl[i], keys);
	i = -1;
	while (++i < p->scene->n_sp)
		if (p->scene->sp[i]->highlighted == 1)
			sphere_manipulation(p->scene, p->scene->sp[i], keys);
}