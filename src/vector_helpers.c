/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:22:23 by zzaludov          #+#    #+#             */
/*   Updated: 2023/12/04 20:55:03 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//len of vector -> distance of the vector from origin in 3D
double	vector_len(t_coord v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

//to get point between two vectors -> good for lighting and shading
double	vector_point(t_coord v1, t_coord v2) //dot product
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	deg_to_rad(double deg)
{
	return (deg * 3.141529 / 180.0);
}

t_coord vector_projection(t_coord v1, t_coord v2)
{
	double	scalar_projection;

	scalar_projection = vector_point(v1, v2) / vector_point(v2, v2);
	return vector_scale(v2, scalar_projection);
}
