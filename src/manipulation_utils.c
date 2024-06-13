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

void	pos_right(t_camera *camera, t_coord *pos)
{
		(void)camera;
		pos->x += 1;
	}

void	pos_left(t_camera *camera, t_coord *pos)
{
		(void)camera;
		pos->x -= 1;
}

void	pos_straight(t_camera *camera, t_coord *pos)
{
	pos->x -= (camera->dir.x * 1);
	pos->y -= (camera->dir.y * 1);
	pos->z -= (camera->dir.z * 1);
}

void	pos_back(t_camera *camera, t_coord *pos)
{
	pos->x += (camera->dir.x * 1);
	pos->y += (camera->dir.y * 1);
	pos->z += (camera->dir.z * 1);
}

void	mutate_diameter(double *diameter, keys_t key)
{
	if (key == MLX_KEY_4)
		*diameter += 0.25;
	else if (key == MLX_KEY_3 && *diameter > 0.26)
		*diameter -= 0.25;
	else if (key == MLX_KEY_3)
		return ;
}

void	mutate_pos(t_camera *camera, t_coord *pos, keys_t key)
{
	if (key == MLX_KEY_D)
		pos_right(camera, pos);
	if (key == MLX_KEY_A)
		pos_left(camera, pos);
	if (key == MLX_KEY_W)
		pos_straight(camera, pos);
	if (key == MLX_KEY_S)
		pos_back(camera, pos);
}

void	mutate_height(double *height, keys_t key)
{
	if (key == MLX_KEY_2)
		*height += 1;
	else if (key == MLX_KEY_1 && *height > 1)
		*height -= 1;
	else if (key == MLX_KEY_1)
		return ;
}