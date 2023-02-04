/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:24 by dkim2             #+#    #+#             */
/*   Updated: 2022/10/28 11:29:02 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../Libft_vector/vector3.h"
#include "scene.h"
#include "mlx_manager.h"
#include "ray_cast.h"
#include "quadrics.h"
#include "print_info.h"
#include "timer.h"
#include <unistd.h>
#include <pthread.h>
#include "resolution.h"
#include "scene_editer.h"
// #include "anti.h"

static int	is_in_bounding_sphere(const t_ray *R, const t_quadrics *Q)
{
	const	t_vec3 ray_org_to_obj_org = v3_sub(Q->org, R->org);
	t_vec3	dist_vec;

	if (Q->type == Q_PLANE)
		return (TRUE);
	dist_vec = v3_crs(R->dir, ray_org_to_obj_org);
	dist_vec = v3_crs(dist_vec, R->dir);
	if (v3_dot(dist_vec, dist_vec) <= Q->bounding_radius_sphere)
		return (TRUE);
	return (FALSE);
}

float	get_intersect_distance(t_quadrics *objlst, \
								t_quadrics **out_intersecting_obj, \
								t_ray ray)
{
	t_quadrics			*target_obj;
	float				dist[2];

	dist[0] = INFINITY;
	if (out_intersecting_obj != NULL)
		*out_intersecting_obj = NULL;
	target_obj = objlst;
	while (target_obj)
	{
		if (is_in_bounding_sphere(&ray, target_obj) == TRUE)
		{
			dist[1] = find_intersection(target_obj, &ray);
			if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
			{
				dist[0] = dist[1];
				if (out_intersecting_obj != NULL)
					*out_intersecting_obj = target_obj;
			}
		}
		target_obj = target_obj->next;
	}
	if (dist[0] < EPSILON)
		return (NAN);
	return (dist[0]);
}

static void	init_thread_local_object(t_thread_local_object *tlo)
{
	int	i;

	i = 0;
	while (i < THREAD_NUM)
	{
		(tlo + i)->x = WIN_WIDTH / THREAD_PARAM * (i / THREAD_PARAM);
		(tlo + i)->y = WIN_HEIGHT / THREAD_PARAM * (i % THREAD_PARAM);
		i++;
	}
}

static void	ray_multithread(void)
{
	static pthread_t				thread_data[THREAD_NUM];
	static t_thread_local_object	tlo[THREAD_NUM];
	int								i;

	init_thread_local_object(tlo);
	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_create((thread_data + i), NULL, \
						thread_routine, (void *)(tlo + i));
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_join(thread_data[i], NULL);
		i++;
	}
}

void	ray_cast(void)
{
	double	cam_proportion;

	cam_proportion = (WIN_WIDTH / 2) / tan(get_scene()->cam->hfov / 2);
	if (get_scene_editer()->edit == 0)
		time_check_start_sub();
	ray_multithread();
	if (get_scene_editer()->edit != 0 \
		&& get_scene_editer()->target_scene != E_NONE)
		render_lightsource(cam_proportion);
	if (get_scene_editer()->edit == 0)
		time_check_end_sub("ray");
}
