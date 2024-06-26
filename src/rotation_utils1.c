/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:55:52 by zzaludov          #+#    #+#             */
/*   Updated: 2024/05/15 20:31:23 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	ft_vec3f_sum(t_vec3f const u, t_vec3f const v)
{
	return (ft_vec3f(u.x + v.x, u.y + v.y, u.z + v.z));
}

t_vec3f	ft_vec3f_cross(t_vec3f const u, t_vec3f const v)
{
	return (ft_vec3f(\
		u.y * v.z - u.z * v.y, \
		u.z * v.x - u.x * v.z, \
		u.x * v.y - u.y * v.x));
}

t_quat4f	ft_quat4f_prod(t_quat4f const q, t_quat4f const p)
{
	return (ft_quat4f(\
		ft_vec3f_sum(ft_vec3f_prod(p.xyz, q.w), \
		ft_vec3f_sum(ft_vec3f_prod(q.xyz, p.w), \
		ft_vec3f_cross(q.xyz, p.xyz))), \
		q.w * p.w - ft_vec3f_dot(q.xyz, p.xyz)));
}

t_quat4f	ft_quat4f_unit(t_quat4f const q)
{
	float const	t = 1.0F / sqrtf(powf(q.w, 2.0F) + ft_vec3f_dot(q.xyz, q.xyz));

	return (ft_quat4f(ft_vec3f_prod(q.xyz, t), q.w * t));
}

t_quat4f	ft_quat4f_conjugate(t_quat4f q)
{
	t_quat4f	conjugate;

	conjugate.xyz.x = -q.xyz.x;
	conjugate.xyz.y = -q.xyz.y;
	conjugate.xyz.z = -q.xyz.z;
	conjugate.w = q.w;
	return (conjugate);
}
