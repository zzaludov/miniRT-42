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

void	pos_up(t_camera *camera, t_coord *pos)
{
	(void)camera;
	pos->y += 1;
}
