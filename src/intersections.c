/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:35:57 by zzaludov          #+#    #+#             */
/*   Updated: 2023/12/06 21:36:00 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// Parametric form of RAY
// ray_org + ray_dir * t

// intersection point position:
// t = ((pl->pos - ray_org) * pl->dir) / ray_dir * pl->dir
int	intersect_pl(t_coord ray_org, t_coord ray_dir, t_plane *plane, double *t)
{
	double	denom;

	plane->dir = normalized(plane->dir);
	denom = dot_product(plane->dir, ray_dir);
	if (fabs(denom) < EPSILON)
		return (0);
	*t = dot_product(vector_subtract(plane->pos, ray_org), plane->dir) / denom;
	if (*t < 0)
		return (0);
	return (1);
}

// a = dot (ray_dir, ray_dir)
// b = 2 * dot (ray_org - sp->pos, ray_dir);
// c = dot (ray_org - sp->pos, ray_org - sp->pos) - r * r
int	intersect_sp(t_coord ray_org, t_coord ray_dir, t_sphere *sp, double *t)
{
	t_coord			vector;
	double			r;
	t_discriminant	d;

	vector = vector_subtract(ray_org, sp->pos);
	r = sp->diameter / 2;
	d.a = dot_product(ray_dir, ray_dir);
	d.b = 2.0 * dot_product(vector, ray_dir);
	d.c = dot_product(vector, vector) - r * r;
	return (discriminant(d, t, sp->inside));
}

// intersection point:
// p = ray_org + ray_dir * t
// vector from disk center to intersection point:
// v = pl.dir - pl.pos
// squared distance from disk center to intersection
// d2 = dot(v, v)
// distance comparason
// d2 <= r * r
int	intersect_disk(t_coord ray_org, t_coord ray_dir, t_cylinder *cy, double *t)
{
	t_plane	pl;
	t_coord	v;
	t_coord	p;
	t_coord	cy_pos;

	cy_pos = create_vector(cy->pos.x, cy->pos.y, cy->pos.z);
	pl.dir = cy->dir;
	pl.rgb = cy->rgb;
	pl.pos = cy_pos;
	if (intersect_pl(ray_org, ray_dir, &pl, t))
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		v = vector_add(p, vector_scale(pl.pos, -1));
		if (sqrt(dot_product(v, v)) <= cy->diameter / 2.0)
			return (1);
	}
	pl.pos = vector_add(cy_pos, vector_scale(cy->dir, cy->height));
	if (intersect_pl(ray_org, ray_dir, &pl, t))
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		v = vector_add(p, vector_scale(pl.pos, -1));
		if (sqrt(dot_product(v, v)) <= cy->diameter / 2.0)
			return (1);
	}
	return (0);
}

// 1. intersection between ray and infinite cylinder
//    infinite height cylinder: x * x + y * y = r * r
//    a = pow(ray_dir.x, 2) + pow(ray_dir.y, 2)
//    b = 2 * (ray_org.x * ray_dir.x + ray_org.y * ray_dir.y)
//    c = pow(ray_org.x, 2) + pow(ray_org.y, 2) - 2 * r

// 2. intersection with two disks
//    cap 1: - ray_org.z / ray_dir.z
//    cap 2  (height - ray_org.z) / ray_dir.z
int	height_cylinder(t_coord ray_org, t_coord ray_dir, t_cylinder *cy, double *t)
{
	t_coord	cy_pos;
	t_coord	intersection_point;
	double	projection;

	cy_pos = create_vector(cy->pos.x, cy->pos.y, cy->pos.z);
	intersection_point = vector_add(ray_org, vector_scale(ray_dir, *t));
	intersection_point = vector_subtract(intersection_point, cy_pos);
	projection = dot_product(intersection_point, cy->dir);
	if (projection < 0 || projection > cy->height)
		return (0);
	return (1);
}

int	intersect_cy(t_coord ray_org, t_coord ray_dir, t_cylinder *cy, double *t)
{
	t_coord			vector;
	t_coord			cy_pos;
	t_discriminant	d;

	cy_pos = create_vector(cy->pos.x, cy->pos.y, cy->pos.z);
	vector = vector_subtract(ray_org, cy_pos);
	d.a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cy->dir), 2);
	d.b = 2.0 * (dot_product(vector, ray_dir) - dot_product(vector, cy->dir)
			* dot_product(ray_dir, cy->dir));
	d.c = dot_product(vector, vector) - pow(dot_product(vector, cy->dir), 2)
		- pow(cy->diameter / 2.0, 2);
	if (!discriminant(d, t, cy->inside))
		return (0);
	if (height_cylinder(ray_org, ray_dir, cy, t))
		return (1);
	return (0);
}
