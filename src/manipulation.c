/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:30:04 by zzaludov          #+#    #+#             */
/*   Updated: 2023/12/02 21:30:14 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_manipulation(t_scene *scene, t_sphere *sphere, mlx_key_data_t keys)
{
	mutate_diameter(&sphere->diameter, keys.key);
	mutate_pos(scene->c, &sphere->pos, keys.key);

}

void	plane_manipulation(t_scene *scene, t_plane *plane, mlx_key_data_t keys)
{
	mutate_pos(scene->c, &plane->pos, keys.key);
	// rotate();
}

void	cylinder_manipulation(t_scene *s, t_cylinder *cylinder, mlx_key_data_t keys)
{
	mutate_diameter(&cylinder->diameter, keys.key);
	mutate_height(&cylinder->height, keys.key);
	mutate_pos(s->c, &cylinder->pos, keys.key);
	// rotate()
}