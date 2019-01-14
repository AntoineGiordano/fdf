/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_set_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/12 14:59:37 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/12 14:59:38 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int		maping(t_window *win, int mincolor, int maxcolor, double prop)
{
	int r;
	int g;
	int b;

	r = (int)(prop * (((maxcolor >> 16) & 0xFF) - ((mincolor >> 16) & 0xFF))) +
		((mincolor >> 16) & 0xFF);
	g = (int)(prop * (((maxcolor >> 8) & 0xFF) - ((mincolor >> 8) & 0xFF))) +
		((mincolor >> 8) & 0xFF);
	b = (int)(prop * ((maxcolor & 0xFF) - (mincolor & 0xFF))) +
		(mincolor & 0xFF);
	return ((r << 16) | (g << 8) | (b | 0));
}

int		set_color(t_window *win, int z)
{
	double prop;

	prop = (double)(z - win->map->minz) /
	(double)(win->map->maxz - win->map->minz);
	return (maping(win, win->mincolor, win->maxcolor, prop));
}

int		colors(t_window *win, t_inputs *inputs, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	if (win->colorparam)
	{
		while (++i < inputs->leny)
		{
			j = -1;
			while (++j < inputs->lenx[i])
				map->tabdot[i][j]->color = set_color(win, inputs->tab[i][j]);
		}
	}
	return (0);
}

void	set_pixel(t_window *win, int x, int y, int color)
{
	if ((x > 0 && x < win->width) && (y > 0 && y < win->height))
		win->map->image->image[x + y * win->width] = color;
}

void	ft_put_line(t_window *win, t_dot *d1, t_dot *d2)
{
	t_vector	pas;
	int			nbpixels;
	int			i;
	int			color;

	pas.x = d2->x - d1->x;
	pas.y = d2->y - d1->y;
	if (ft_abs(pas.x) > ft_abs(pas.y))
	{
		nbpixels = ft_abs(pas.x);
		pas.y /= ft_abs(pas.x);
		pas.x /= ft_abs(pas.x);
	}
	else
	{
		nbpixels = ft_abs(pas.y);
		pas.x /= ft_abs(pas.y);
		pas.y /= ft_abs(pas.y);
	}
	i = -1;
	while (++i < nbpixels)
	{
		color = maping(win, d1->color, d2->color, (double)i / (double)nbpixels);
		set_pixel(win, d1->x + pas.x * i, d1->y + pas.y * i, color);
	}
}
