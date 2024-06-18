/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:22:23 by zzaludov          #+#    #+#             */
/*   Updated: 2023/12/04 20:55:03 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vector_len(t_coord v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_coord	normalized(t_coord v)
{
	double	len;

	len = vector_len(v);
	if (len == 0)
		return (v);
	return (vector_scale(v, 1 / len));
}

//to get point between two vectors (dot product)
double	vector_point(t_coord v1, t_coord v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// cross_product
t_coord	vector_produkt(t_coord v1, t_coord v2)
{
	t_coord	v;

	v.x = v1.y * v2.z - v2.y * v1.z;
	v.y = v1.z * v2.x - v2.z * v1.x;
	v.z = v1.x * v2.y - v2.x * v1.y;
	return (v);
}

t_coord	vector_projection(t_coord v1, t_coord v2)
{
	double	scalar_projection;

	scalar_projection = vector_point(v1, v2) / vector_point(v2, v2);
	return (vector_scale(v2, scalar_projection));
}
