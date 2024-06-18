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
int	intersect_plane(t_coord ray_org, t_coord ray_dir, t_plane *plane, double *t)
{
	double	denom;

	denom = vector_point(plane->dir, ray_dir);
	if (fabs(denom) < EPSILON)
		return (0);
	*t = vector_point(vector_subtract(plane->pos, ray_org), plane->dir) / denom;
	if (*t < 0)
		return (0);
	return (1);
}

// a = dot (ray_dir, ray_dir)
// b = 2 * dot (ray_org - sp->pos, ray_dir);
// c = dot (ray_org - sp->pos, ray_org - sp->pos) - r * r
int	intersect_sphere(t_coord ray_org, t_coord ray_dir, t_sphere *sp, double *t)
{
	t_coord	vector;
	double	a;
	double	b;
	double	c;
	double	r;

	vector = vector_subtract(ray_org, sp->pos);
	r = sp->diameter / 2;
	a = vector_point(ray_dir, ray_dir);
	b = 2.0 * vector_point(vector, ray_dir);
	c = vector_point(vector, vector) - r * r;
	return (discriminant(a, b, c, t));
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

	cy_pos.x = cy->pos.x;
	cy_pos.y = cy->pos.y;
	cy_pos.z = cy->pos.z - cy->height / 2;
	pl.dir = cy->dir;
	pl.rgb = cy->rgb;
	pl.pos = cy_pos;
	if (intersect_plane(ray_org, ray_dir, &pl, t))
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		v = vector_add(p, vector_scale(pl.pos, -1));
		if (sqrt(vector_point(v, v)) <= cy->diameter / 2.0)
			return (1);
	}
	pl.pos = vector_add(cy_pos, vector_scale(cy->dir, cy->height));
	if (intersect_plane(ray_org, ray_dir, &pl, t))
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		v = vector_add(p, vector_scale(pl.pos, -1));
		if (sqrt(vector_point(v, v)) <= cy->diameter / 2.0)
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

	cy_pos.x = cy->pos.x;
	cy_pos.y = cy->pos.y;
	cy_pos.z = cy->pos.z - cy->height / 2;
	intersection_point = vector_add(ray_org, vector_scale(ray_dir, *t));
	intersection_point = vector_subtract(intersection_point, cy_pos);
	projection = vector_point(intersection_point, cy->dir);
	if (projection < 0 || projection > cy->height)
		return (0);
	return (1);
}

int	intersect_cylinder(t_coord ray_org, t_coord ray_dir, t_cylinder *cy, double *t)
{
	t_coord	vector;
	t_coord	cy_pos;
	double	a;
	double	b;
	double	c;

	cy_pos.x = cy->pos.x;
	cy_pos.y = cy->pos.y;
	cy_pos.z = cy->pos.z - cy->height / 2;
	vector = vector_subtract(ray_org, cy_pos);
	a = vector_point(ray_dir, ray_dir) - pow(vector_point(ray_dir, cy->dir), 2);
	b = 2.0 * (vector_point(vector, ray_dir) - vector_point(vector, cy->dir)
		* vector_point(ray_dir, cy->dir));	
	c = vector_point(vector, vector) - pow(vector_point(vector, cy->dir), 2)
		- pow(cy->diameter / 2.0, 2);
	if (!discriminant(a, b, c, t))
		return (0);
	if (height_cylinder(ray_org, ray_dir, cy, t))
		return (1);
	return (0);
}
