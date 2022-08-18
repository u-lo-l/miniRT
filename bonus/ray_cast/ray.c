/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 08:08:24 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/18 14:54:01 by dkim2            ###   ########.fr       */
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
#include "assert.h"
#include "scene_editer.h"

#define THREAD_NUM 4

float	get_intersect_distance(t_quadrics *objlst, \
								t_quadrics **out_intersecting_obj, \
								t_ray ray)
{
	t_quadrics			*target_obj;
	t_quadrics			*intersect_obj;
	float				dist[2];

	dist[0] = INFINITY;
	intersect_obj = NULL;
	target_obj = objlst;
	while (target_obj)
	{
		assert(ray.dir.w == 0);
		dist[1] = find_intersection(target_obj, &ray);
		if ((isnan(dist[1]) == FALSE) && (dist[1] < dist[0]))
		{
			dist[0] = dist[1];
			if (out_intersecting_obj != NULL)
				*out_intersecting_obj = target_obj;
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
		(tlo + i)->x = WIN_WIDTH / 2 * (i / 2);
		(tlo + i)->y = WIN_HEIGHT / 2 * (i % 2);
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
	time_check_start_sub();
	ray_multithread();
	if (get_scene_editer()->edit != 0 \
		&& get_scene_editer()->target_scene != E_NONE)
		render_lightsource(cam_proportion);
	time_check_end_sub("ray");
}
