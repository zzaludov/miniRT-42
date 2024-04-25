/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:59:40 by mvocasko          #+#    #+#             */
/*   Updated: 2023/12/04 21:40:38 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//pretty self-explanatory -> creates 4D vector
t_coord	create_vector(double x, double y, double z)
{
	t_coord	v;

	v.x = x;
	v.y = y;
	v.z = z;
//	v.w = 1;
	return (v);
}

// sc = scalar -> changes len without changing direction 
// sc negative = reverses direction of vector, sc <0-1> 
//shrinking, sc > 1 scaling up
t_coord	vector_scale(t_coord v, double sc)
{
	t_coord	v1;

	v1.x = v.x * sc;
	v1.y = v.y * sc;
	v1.z = v.z * sc;
	return (v1);
}

//creating normalized vectors
t_coord	normalized(t_coord v)
{
	double	len;

	len = vector_len(v);
	if (len == 0)
		return (v);
	return (vector_scale(v, 1 / len));
}

//we will use it for determining direction of vectors
t_coord	vector_add(t_coord v1, t_coord v2)
{
	t_coord	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_coord	vector_subtract(t_coord v1, t_coord v2)
{
	t_coord	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
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
