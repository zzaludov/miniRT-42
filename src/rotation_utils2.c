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

float	ft_vec3f_dot(t_vec3f const u, t_vec3f const v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3f	ft_vec3f(float const x, float const y, float const z)
{
	t_vec3f	u;

	u.x = x;
	u.y = y;
	u.z = z;
	return (u);
}

t_vec3f	ft_vec3f_prod(t_vec3f const u, float const t)
{
	return (ft_vec3f(u.x * t, u.y * t, u.z * t));
}

t_quat4f	ft_quat4f(t_vec3f const xyz, float const w)
{
	t_quat4f	q;

	q.xyz = xyz;
	q.w = w;
	return (q);
}
