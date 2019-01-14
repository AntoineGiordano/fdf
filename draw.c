/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   axes.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 20:58:02 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 20:58:05 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

void	reset_dots(t_window *win, t_inputs *inputs, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (map->tabdot)
	{
		while (map->tabdot[++i])
		{
			j = -1;
			while (map->tabdot[i][++j])
				free(map->tabdot[i][j]);
			free(map->tabdot[i]);
		}
		free(map->tabdot);
	}
}

int		set_dots(t_window *win, t_inputs *inputs, t_map *map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < inputs->leny)
	{
		j = -1;
		while (++j < inputs->lenx[i])
		{
			map->tabdot[i][j]->x = map->zoom * (map->i.x * (j - map->centre.x) +
				map->j.x * (i - map->centre.y) + map->k.x * inputs->tab[i][j]) +
				map->origin.x;
			map->tabdot[i][j]->y = map->zoom * (map->i.y * (j - map->centre.x) +
				map->j.y * (i - map->centre.y) + map->k.y * inputs->tab[i][j]) +
				map->origin.y;
		}	
	}
	return (0);
}

void	print_dots(t_window *win, t_inputs *inputs, t_map *map)
{
	int	x;
	int	y;
	int	j;
	int	i;

	i = -1;
	while (++i < inputs->leny)
	{
		j = -1;
		while (++j < inputs->lenx[i])
		{
			x = map->tabdot[i][j]->x;
			y = map->tabdot[i][j]->y;
			if (j + 1 != inputs->lenx[i])
			{
				if (!((x < 0 || x > win->width || y < 0 || y > win->height) &&
				(map->tabdot[i][j + 1]->x < 0 ||
				map->tabdot[i][j + 1]->x > win->width ||
				map->tabdot[i][j + 1]->y < 0 ||
				map->tabdot[i][j + 1]->y > win->height)))
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i][j + 1]);
			}
			if (i + 1 != inputs->leny && j < inputs->lenx[i + 1])
			{
				if (!((x < 0 || x > win->width || y < 0 || y > win->height) &&
				(map->tabdot[i + 1][j]->x < 0 ||
				map->tabdot[i + 1][j]->x > win->width ||
				map->tabdot[i + 1][j]->y < 0 ||
				map->tabdot[i + 1][j]->y > win->height)))
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i + 1][j]);
			}
			/*if (j + 1 != inputs->lenx[i + 1] && i + 1 != inputs->leny)
			{
				if (!((x < 0 || x > win->width || y < 0 || y > win->height) &&
				(map->tabdot[i + 1][j + 1]->x < 0 ||
				map->tabdot[i + 1][j + 1]->x > win->width ||
				map->tabdot[i + 1][j + 1]->y < 0 ||
				map->tabdot[i + 1][j + 1]->y > win->height)))
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i + 1][j + 1]);
			}
			if (i - 1 != -1 && j + 1 != inputs->lenx[i - 1])
			{
				if (!((x < 0 || x > win->width || y < 0 || y > win->height) &&
				(map->tabdot[i - 1][j + 1]->x < 0 ||
				map->tabdot[i - 1][j + 1]->x > win->width ||
				map->tabdot[i - 1][j + 1]->y < 0 ||
				map->tabdot[i - 1][j + 1]->y > win->height)))
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i - 1][j + 1]);
			}*/
		}
	}
}
