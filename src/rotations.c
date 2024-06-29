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

static bool	ft_isrotated(mlx_key_data_t keys, t_quat4f *qrot)
{
	static float const	hagl = 8 * 3.14159265358979323846F / 360.0F;
	static float const	nhagl = 8 * 3.14159265358979323846F / -360.0F;
	t_vec3f const		standard[] = {
		ft_vec3f(1.0F, 0.0F, 0.0F),
		ft_vec3f(0.0F, 1.0F, 0.0F),
		ft_vec3f(0.0F, 0.0F, 1.0F)
	};

	if (keys.key == MLX_KEY_J || keys.key == MLX_KEY_KP_5)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[0], sinf(nhagl)), cosf(nhagl));
	else if (keys.key == MLX_KEY_U || keys.key == MLX_KEY_KP_8)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[0], sinf(hagl)), cosf(hagl));
	else if (keys.key == MLX_KEY_K || keys.key == MLX_KEY_KP_6)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[1], sinf(nhagl)), cosf(nhagl));
	else if (keys.key == MLX_KEY_H || keys.key == MLX_KEY_KP_4)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[1], sinf(hagl)), cosf(hagl));
	else if (keys.key == MLX_KEY_KP_7)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[2], sinf(nhagl)), cosf(nhagl));
	else if (keys.key == MLX_KEY_KP_9)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[2], sinf(hagl)), cosf(hagl));
	else
		return (false);
	return (true);
}

void	rotate_plane(mlx_key_data_t keys, t_plane *plane)
{
	t_quat4f	qrot;
	t_quat4f	rotated_dir_quat;
	t_quat4f	dir_quat;

	dir_quat.xyz.x = plane->dir.x;
	dir_quat.xyz.y = plane->dir.y;
	dir_quat.xyz.z = plane->dir.z;
	dir_quat.w = 0;
	if (ft_isrotated(keys, &qrot))
	{
		rotated_dir_quat = ft_quat4f_unit(ft_quat4f_prod
				(ft_quat4f_prod(qrot, dir_quat), ft_quat4f_conjugate(qrot)));
		plane->dir.x = rotated_dir_quat.xyz.x;
		plane->dir.y = rotated_dir_quat.xyz.y;
		plane->dir.z = rotated_dir_quat.xyz.z;
		plane->dir = normalized(plane->dir);
	}
}

void	rotate_cylinder(mlx_key_data_t keys, t_cylinder *cylinder)
{
	t_quat4f	qrot;
	t_quat4f	rotated_dir_quat;
	t_quat4f	dir_quat;

	dir_quat.xyz.x = cylinder->dir.x;
	dir_quat.xyz.y = cylinder->dir.y;
	dir_quat.xyz.z = cylinder->dir.z;
	dir_quat.w = 0;
	if (ft_isrotated(keys, &qrot))
	{
		rotated_dir_quat = ft_quat4f_unit(ft_quat4f_prod
				(ft_quat4f_prod(qrot, dir_quat), ft_quat4f_conjugate(qrot)));
		cylinder->dir.x = rotated_dir_quat.xyz.x;
		cylinder->dir.y = rotated_dir_quat.xyz.y;
		cylinder->dir.z = rotated_dir_quat.xyz.z;
		cylinder->dir = normalized(cylinder->dir);
	}
}

void	move_camera(mlx_key_data_t keys, t_camera *camera)
{
	if (keys.key == MLX_KEY_X)
		pos_right(camera, &camera->pos);
	if (keys.key == MLX_KEY_Z)
		pos_left(camera, &camera->pos);
	if (keys.key == MLX_KEY_C)
		pos_straight(camera, &camera->pos);
	if (keys.key == MLX_KEY_V)
		pos_back(camera, &camera->pos);
	if (keys.key == MLX_KEY_LEFT_SHIFT)
		pos_up(camera, &camera->pos);
	if (keys.key == MLX_KEY_LEFT_CONTROL)
		pos_down(camera, &camera->pos);
}

void	rotate_camera(mlx_key_data_t keys, t_camera *camera)
{
	t_quat4f	qrot;
	t_quat4f	rotated_dir_quat;
	t_quat4f	dir_quat;

	dir_quat.xyz.x = camera->dir.x;
	dir_quat.xyz.y = camera->dir.y;
	dir_quat.xyz.z = camera->dir.z;
	dir_quat.w = 0;
	if (keys.key == MLX_KEY_KP_4 || keys.key == MLX_KEY_KP_5
		|| keys.key == MLX_KEY_KP_6 || keys.key == MLX_KEY_KP_7
		|| keys.key == MLX_KEY_KP_8 || keys.key == MLX_KEY_KP_9)
	{
		if (ft_isrotated(keys, &qrot))
		{
			rotated_dir_quat = ft_quat4f_unit(ft_quat4f_prod
					(ft_quat4f_prod(qrot, dir_quat),
						ft_quat4f_conjugate(qrot)));
			camera->dir.x = rotated_dir_quat.xyz.x;
			camera->dir.y = rotated_dir_quat.xyz.y;
			camera->dir.z = rotated_dir_quat.xyz.z;
			camera->dir = normalized(camera->dir);
		}
	}
}
