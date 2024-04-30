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

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
int	intersect_plane(t_coord ray_org, t_coord ray_dir, t_plane *plane, double *t)
{
	double	denominator;

	denominator = vector_point(plane->dir, ray_dir);
	if (fabs(denominator) < EPSILON)
	{
		return 0; // Ray is parallel to the plane, no intersection
	}
	*t = vector_point(vector_subtract(plane->pos, ray_org), plane->dir) / denominator;
	if (*t < 0)
	{
		return 0;
	}
	return 1;
}

// a = dot (ray_dir, ray_dir)
// b = 2 * dot (ray_org - sp->pos, ray_dir);
// c = dot (ray_org - sp->pos, ray_org - sp->pos) - sqrt(r)

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
int	intersect_sphere(t_coord ray_org, t_coord ray_dir, t_sphere *sp, double *t)
{
	t_coord	vector;
	double	a;
	double	b;
	double	c;
	double	r;

	vector = vector_subtract(ray_org, sp->pos);
	r = sp->diameter / 2;

	a = vector_point(ray_dir, ray_dir);  // point or dot ?
	b = 2.0 * vector_point(vector, ray_dir);
	c = vector_point(vector, vector) - sqrt(r);
	return (discriminant(a, b, c, t));
}

// intersection point:
// p = ray_org + ray_dir * t
// vector from disk center to intersection point:
// v = pl.dir - pl.pos
// sqrt distance from disk center to intersection
// d2 = dot(v, v)
// distance comparason
// d2 <= r * r

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
int intersect_disk(t_coord ray_org, t_coord ray_dir, t_cylinder* cy, double* t)
{
	t_plane	pl;
	t_coord	v;
	t_coord	p;

	pl.dir = cy->dir;  // is this correct?
	pl.rgb = cy->rgb;
	pl.pos = cy->pos;
	if (intersect_plane(ray_org, ray_dir, &pl, t))  // maybe not use same t?
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		//v = vector_add(p, vector_scale(pl.pos, -1));
		v = vector_subtract(pl.dir, pl.pos);
		if (sqrt(vector_point(v, v)) <= cy->diameter / 2.0)
			return 1;
	}

	pl.pos = vector_add(cy->pos, vector_scale(cy->dir, cy->height));
	if (intersect_plane(ray_org, ray_dir, &pl, t))
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		v = vector_add(p, vector_scale(pl.pos, -1));
		//if (sqrt(vector_point(v, v)) <= cy->diameter / 2.0)
		if (sqrt(vector_point(v, v)) <= sqrt(cy->diameter / 2.0))
			return 1;
	}
	return 0;
}

// 1. intersection between ray and infinite cylinder
//    infinite height cylinder: sqrt(x) + sqrt(y) = sqrt(r)
//    a = sqrt(ray_dir.x) + sqrt(ray_dir.y)
//    b = 2 * (ray_org.x * ray_dir.x + ray_org.y * ray_dir.y)
//    c = sqrt(ray_org.x) + sqrt(ray_org.y) - 2 * r

// 2. intersection with two disks
//    cap 1: - ray_org.z / ray_dir.z
//    cap 2  (height - ray_org.z) / ray_dir.z
// https://www.irisa.fr/prive/kadi/Master_Recherche/cours_CTR/RayTracing.pdf
int intersect_cylinder(t_coord ray_org, t_coord ray_dir, t_cylinder *cy, double *t)
{
	t_coord	vector;
	double	a;
	double	b;
	double	c;
	
	vector = vector_subtract(ray_org, cy->pos);  // ??
	// z needs to be 0
	a = vector_point(ray_dir, ray_dir) - pow(vector_point(ray_dir, cy->dir), 2);
	// a = sqrt(ray_dir.x) + sqrt(ray_dir.y);
	b = 2.0 * (vector_point(vector, ray_dir) - vector_point(vector, cy->dir)
	* vector_point(ray_dir, cy->dir));	
	// b = 2.0 * (ray_org.x * ray_dir.x + ray_org.y * ray_dir.y);
	c = vector_point(vector, vector) - pow(vector_point(vector, cy->dir), 2)
	- pow(cy->diameter / 2.0, 2);
	// c = sqrt(ray_org.x) + sqrt(ray_org.y) - 2 * (cy->diameter / 2.0)

	if (!discriminant(a, b, c, t))
		return 0;

	// Calculate intersection point
	t_coord intersection_point = vector_add(ray_org, vector_scale(ray_dir, *t));  // update!!!!

	// Check if intersection point is within the height bounds of the cylinder
	t_coord v = vector_subtract(intersection_point, cy->pos);
	double projection = vector_point(v, cy->dir);
	if (projection < 0 || projection > cy->height)
		return 0; // Intersection is outside the height bounds of the cylinder
	//cap	
/*	double distance_to_axis_squared = vector_point(v, v) - pow(projection, 2);
	if (distance_to_axis_squared > pow(cy->diameter / 2.0, 2))
		return 0; */

	return 1;

}
