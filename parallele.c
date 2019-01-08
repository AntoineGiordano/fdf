/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parallele.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 14:23:16 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/07 14:23:33 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parallele_x(t_window *win, int sign)
{
	if (sign == 1)
	{
		win->map->i.x = 0;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = -10;
		win->map->k.y = 0;
	}
	else
	{
		win->map->i.x = 0;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = 10;
		win->map->k.y = 0;
	}
}

void	ft_parallele_y(t_window *win, int sign)
{
	if (sign == 1)
	{
		win->map->i.x = 10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = 0;
		win->map->k.x = 0;
		win->map->k.y = 10;
	}
	else
	{
		win->map->i.x = 10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = 0;
		win->map->k.x = 0;
		win->map->k.y = -10;
	}
}

void	ft_parallele_z(t_window *win, int sign)
{
	if (sign == 1)
	{
		win->map->i.x = -10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = 0;
		win->map->k.y = 0;
	}
	else
	{
		win->map->i.x = 10;
		win->map->i.y = 0;
		win->map->j.x = 0;
		win->map->j.y = -10;
		win->map->k.x = 0;
		win->map->k.y = 0;
	}
}

void	ft_iso(t_map *map)
{
	map->i.x = map->zoom * 10;
	map->i.y = map->zoom * 4;
	map->j.x = map->zoom * (-10);
	map->j.y = map->zoom * 4;
	map->k.x = map->zoom * 0;
	map->k.y = map->zoom * (-10.7);
}

void	ft_parallele(t_window *win, int keycode)
{
	if (keycode == 87)
		ft_iso(win->map);
	if (keycode == 86)
		ft_parallele_x(win, -1);
	else if (keycode == 88)
		ft_parallele_x(win, 1);
	else if (keycode == 84)
		ft_parallele_y(win, -1);
	else if (keycode == 91)
		ft_parallele_y(win, 1);
	else if (keycode == 83)
		ft_parallele_z(win, -1);
	else if (keycode == 92)
		ft_parallele_z(win, 1);
}
