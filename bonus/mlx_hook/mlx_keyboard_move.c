/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:52:32 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/12 02:48:11 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_part.h"
#include "mlx_keycode.h"
#include "transform.h"
#include <stdio.h>
#include "print_info.h"
#include "quadrics.h"

static int	move_pos(t_vec3 *pos, int keycode)
{
	if (keycode == KEY_D)
		pos->x += 1;
	else if (keycode == KEY_A)
		pos->x -= 1;
	else if (keycode == KEY_W)
		pos->z += 1;
	else if (keycode == KEY_S)
		pos->z -= 1;
	else if (keycode == UARROW)
		pos->y -= 1;
	else if (keycode == DARROW)
		pos->y += 1;
	else
		return (FALSE);
	return (TRUE);
}

int	mlx_move_cam(t_mlx *mlx, int keycode)
{
	t_mat33		transform;

	if (keycode == KEY_Q)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), 1, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), 1, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(mlx->scene, mat33_trans(transform));
	}
	else if (keycode == KEY_E)
	{
		transform.r1 = rotate_vec3_deg(make_v3(0, 0, 1), -1, make_v3(1, 0, 0));
		transform.r2 = rotate_vec3_deg(make_v3(0, 0, 1), -1, make_v3(0, 1, 0));
		transform.r3 = make_v3(0, 0, 1);
		transform_to_cam_cord(mlx->scene, mat33_trans(transform));
	}
	else if (move_pos(&(mlx->scene->cam->pos), keycode) == FALSE)
		return (FALSE);
	print_info_camera(mlx->scene->cam);
	mlx_renew_image(mlx);
	return (TRUE);
}

int	mlx_move_light(t_mlx *mlx, int keycode)
{
	if (move_pos(&(mlx->selected_light->o), keycode) == FALSE)
		return (FALSE);
	print_info_light(mlx->scene->light);
	mlx_renew_image(mlx);
	return (TRUE);
}

int	mlx_move_obj(t_mlx *mlx, int keycode)
{
	const t_vec3	axis = make_v3(0, 0, 1);

	if (mlx->selected_quad == NULL)
		return (FALSE);
	else if (keycode == KEY_Q)
	{
		mlx->selected_quad->dir = rotate_vec3_deg(axis, -1, \
								mlx->selected_quad->dir);
		mlx->selected_quad->tan = rotate_vec3_deg(axis, -1, \
								mlx->selected_quad->tan);
		rotate_quadrics(mlx->selected_quad, axis, -1);
	}
	else if (keycode == KEY_E)
	{
		mlx->selected_quad->dir = rotate_vec3_deg(axis, 1, \
								mlx->selected_quad->dir);
		mlx->selected_quad->tan = rotate_vec3_deg(axis, 1, \
								mlx->selected_quad->tan);
		rotate_quadrics(mlx->selected_quad, axis, 1);
	}
	else if (move_pos(&(mlx->selected_quad->org), keycode) == FALSE)
		return (FALSE);
	print_single_quadrics(mlx->selected_quad);
	mlx_renew_image(mlx);
	return (TRUE);
}

void	mlx_switch_light(t_mlx *mlx)
{
	mlx->selected_light = mlx->selected_light->next;
	if (mlx->selected_light == NULL)
		mlx->selected_light = mlx->scene->light;
	printf("light changed\n");
	print_single_light(mlx->selected_light);
}
