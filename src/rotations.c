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

	if (keys.key == MLX_KEY_J || keys.key == MLX_KEY_DOWN)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[0], sinf(nhagl)), cosf(nhagl));
	else if (keys.key == MLX_KEY_U || keys.key == MLX_KEY_UP)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[0], sinf(hagl)), cosf(hagl));
	else if (keys.key == MLX_KEY_K || keys.key == MLX_KEY_RIGHT)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[1], sinf(nhagl)), cosf(nhagl));
	else if (keys.key == MLX_KEY_H || keys.key == MLX_KEY_LEFT)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[1], sinf(hagl)), cosf(hagl));
	else if (keys.key == MLX_KEY_N)
		*qrot = ft_quat4f(ft_vec3f_prod(standard[2], sinf(nhagl)), cosf(nhagl));
	else if (keys.key == MLX_KEY_M)
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

void	rotate_camera(mlx_key_data_t keys, t_camera *camera)
{
	t_quat4f	qrot;
	t_quat4f	rotated_dir_quat;
	t_quat4f	dir_quat;

	dir_quat.xyz.x = camera->dir.x;
	dir_quat.xyz.y = camera->dir.y;
	dir_quat.xyz.z = camera->dir.z;
	dir_quat.w = 0;
	if (keys.key == MLX_KEY_LEFT || keys.key == MLX_KEY_RIGHT
		|| keys.key == MLX_KEY_UP || keys.key == MLX_KEY_DOWN)
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
