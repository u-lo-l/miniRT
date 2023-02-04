/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:24 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/07 18:25:43 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "../Libft_vector/vector3.h"
#include "scene.h"
#include "mlx_part.h"
#include "ray_cast.h"
#include <stdio.h>
#include <time.h>
#include "objects.h"
#include "print_info.h"

static t_color	intensity_attenuation(t_color color, t_vec3 pos1, t_vec3 pos2)
{
	const int	unit = 100;
	double		dist;
	double		a[3];
	double		attenuation;

	a[0] = 1;
	a[1] = 1;
	a[2] = 0;
	dist = v3_l2norm(v3_sub(pos1, pos2)) / unit;
	attenuation = fmin(1, 1 / (a[0] + a[1] * dist + a[2] * dist * dist));
	return (color_scale(color, attenuation));
}

double	get_intersect_distance(t_obj_base *objlst, \
								t_obj_base **intersecting_obj_out, \
								t_ray ray)
{
	t_obj_base			*target_obj;
	// t_obj_base			*intersect_obj;
	double				dist[2];

	dist[0] = INFINITY;
	// intersect_obj = NULL;
	target_obj = objlst;
	while (target_obj)
	{
		dist[1] = intersect(ray, target_obj);
		if ((dist[1] != NAN) && (dist[1] < dist[0]))
		{
			dist[0] = dist[1];
			*intersecting_obj_out = target_obj;
		}
		target_obj = target_obj->next;
	}
	if (*intersecting_obj_out == NULL)
		return (INFINITY);
	return (dist[0]);
}

static t_color	single_ray_cast(t_mlx *mlx, t_ray ray)
{
	t_obj_base	*intersect_obj;
	t_vec3		intersect;
	t_color		c;
	double		dist;

	intersect_obj = NULL;
	dist = get_intersect_distance(mlx->scene->obj, &intersect_obj, ray);
	if (isinf(dist) == TRUE)
		return (rgb_color(0, 0, 0));
	else
	{
		intersect = v3_mul(ray.dir, dist);
		intersect = v3_add(intersect, ray.org);
		c = phong_reflection(mlx, intersect_obj, intersect, ray.org);
		return (intensity_attenuation(c, intersect, ray.org));
	}
}

static void	ft_fill_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	unsigned int	s[2];

	s[0] = -1;
	while (++s[0] < (mlx->edit + 1))
	{
		s[1] = -1;
		while (++s[1] < (mlx->edit + 1))
			ft_mlx_set_pixel_color(mlx->image, x + s[0], y + s[1], color);
	}
}

void	ray_cast(t_mlx *mlx)
{
	unsigned int	pixel[2];
	double			d;
	t_color			color;
	t_ray			ray;

	d = ((double)mlx->width / 2) / tan(mlx->scene->cam->hfov / 2);
	pixel[1] = 0;
	while (pixel[1] < mlx->height - mlx->edit)
	{
		pixel[0] = 0;
		while (pixel[0] < mlx->width - mlx->edit)
		{
			ray.dir = v3_normalize(make_v3((int)(pixel[0] - mlx->width / 2), \
										(int)(pixel[1] - mlx->height / 2), d));
			ray.org = mlx->scene->cam->pos;
			color = single_ray_cast(mlx, ray);
			ft_fill_pixel(mlx, pixel[0], pixel[1], color_to_hex(color));
			pixel[0] += (mlx->edit + 1);
		}
		pixel[1] += (mlx->edit + 1);
	}
	if (mlx->edit != 0 && mlx->target_scene != E_NONE)
		render_lightsource(mlx, d);
}
