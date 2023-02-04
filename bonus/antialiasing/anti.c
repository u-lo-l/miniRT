/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:54:42 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/24 15:04:56 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resolution.h"
// #include "anti.h"
#include "mlx_manager.h"
#include "color.h"
#include "color.h"

#define W WIN_WIDTH
#define H WIN_HEIGHT

void	sing(int a[3], int x, int y, int z);

static unsigned int	*get_board(void)
{
	static unsigned int	board[WIN_HEIGHT][WIN_WIDTH];

	return ((unsigned int *)board);
}

static void	draw(void)
{
	int					i;
	int					j;
	t_mlx_manager		*mlx;
	const unsigned int	*board = get_board();

	mlx = get_mlx();
	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			ft_mlx_set_pixel_color(&mlx->image, i, \
							j, *(board + WIN_WIDTH * j + i));
			i++;
		}
		j++;
	}
}

static unsigned int	ft_mlx_get_pixel_color(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

static t_color	func(int i, int j)
{
	const int			dir_xy[3] = {-1, 0, 1};
	t_mlx_manager		*mlx;
	int					a[9];

	mlx = get_mlx();
	a[5] = 0;
	a[0] = -1;
	sing(a + 6, 0, 0, 0);
	while (++a[0] < 3)
	{
		a[1] = -1;
		while (++a[1] < 3)
		{
			a[2] = i + dir_xy[a[0]];
			a[3] = j + dir_xy[a[1]];
			if (a[2] >= 0 && a[2] < W && a[3] >= 0 && a[3] < H && ++a[5])
			{
				a[4] = ft_mlx_get_pixel_color(&mlx->image, a[2], a[3]);
				sing (a + 6, a[6] + (a[4] >> 16) & 0xFF, a[7] += (a[4] >> 8) \
						&0xFF, a[8] + (a[4]) & 0xFF);
			}
		}
	}
	sing(a + 6, a[6] / a[5], a[7] / a[5], a[8] / a[5]);
	return (rgb_color(a[6], a[7], a[8]));
}

void	antialiasing(void)
{
	t_mlx_manager	*mlx;
	unsigned int	*board;
	int				i;
	int				j;
	t_color			color;

	board = get_board();
	mlx = get_mlx();
	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			color = func(i, j);
			*(board + WIN_WIDTH * j + i) = color_to_hex(color);
			i++;
		}
		j++;
	}
	draw();
}
