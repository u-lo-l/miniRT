/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:47:27 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/06 13:59:30 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ray_cast.h"
#include "objects.h"


static double	obj_interstion(t_ray ray, \
								t_obj_base *obj, \
								unsigned int *pcolor_or_null)
{
	double	dist;
	t_vec3	obj_org;

	obj_org = v3_sub(obj->o, ray.org);
	if (v3_dot(ray.dir, obj->n) == 0)
		return (NAN);
	dist = v3_dot(obj_org, obj->n) / v3_dot(ray.dir, obj->n);
	if (dist <= 0)
		return (NAN);
	if (pcolor_or_null != NULL)
		*pcolor_or_null = color_to_hex(obj->color);
	return (dist);
}



static t_vec3	obj_get_normal_vector(t_obj_base *obj, t_vec3 point, t_vec3 cam_pos)
{
	t_vec3	org_to_cam;

	point.x = point.x;
	org_to_cam = v3_sub(cam_pos, obj->o);
	if (v3_dot(org_to_cam, obj->n) > 0)
		return (obj->n);
	else
		return (v3_mul(obj->n, -1));
}

struct objs_vtable_ *get_plain()
{
	static struct objs_vtable_ plain[] = { { obj_interstion, obj_get_normal_vector} };

	return plain;
}
