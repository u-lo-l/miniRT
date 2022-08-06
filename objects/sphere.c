#include <math.h>
#include "libft.h"
#include "ray_cast.h"
#include "objects.h"

// discriminant : 이차방정식의 판별식
double	solve_quadratic_equation(double a, double b, double c)
{
	double	solution;
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		solution = -1;
	else if (discriminant == 0)
		solution = -b;
	else
	{
		solution = -b - sqrt(discriminant);
		if (solution <= 0)
			solution = -b + sqrt(discriminant);
	}
	if (solution <= 0)
		return (NAN);
	return (solution / (2 * a));
}

static double	obj_interstion(t_ray ray, \
								t_obj_base *obj, \
								unsigned int *pcolor_or_null)
{
	double	distance;
	t_vec3	obj_org;

	obj_org = v3_sub(obj->o, ray.org);
	distance = solve_quadratic_equation(v3_dot(ray.dir, ray.dir), \
					-2 * v3_dot(obj_org, ray.dir), \
					v3_dot(obj_org, obj_org) - pow(obj->r, 2));
	if (distance == NAN)
		return (NAN);
	if (pcolor_or_null != NULL)
		*pcolor_or_null = color_to_hex(obj->color);
	return (distance);
}

static t_vec3	obj_get_normal_vector(t_obj_base *obj, t_vec3 point, \
								t_vec3 cam_pos)
{
	t_vec3	normal;

	normal = v3_normalize(v3_sub(point, obj->o));
	if (v3_l2norm(v3_sub(cam_pos, obj->o)) < obj->r)
		return (v3_mul(normal, -1));
	return (normal);
}

struct objs_vtable_ *get_sphere()
{
	static struct objs_vtable_ sphere[] = { { obj_interstion, obj_get_normal_vector} };

	return sphere;
}