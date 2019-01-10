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

	printf("Debut set dots\n");
	i = -1;
	while (++i < inputs->leny)
	{
		j = -1;
		while (++j < inputs->lenx)
		{
			map->tabdot[i][j]->x = map->zoom * (map->i.x * (j - map->centre.x) + map->j.x * (i - map->centre.y) + map->k.x * inputs->tab[i][j]) + map->origin.x;
			map->tabdot[i][j]->y = map->zoom * (map->i.y * (j - map->centre.x) + map->j.y * (i - map->centre.y) + map->k.y * inputs->tab[i][j]) + map->origin.y;
			
			map->tabdot[i][j]->color.r = inputs->colors[i][j] / (16 * 16 * 16 * 16);
			map->tabdot[i][j]->color.g = (inputs->colors[i][j] % (16 * 16 * 16 * 16)) / (16 * 16);
			map->tabdot[i][j]->color.b = inputs->colors[i][j] % (16 * 16);
		}	
	}
	printf("Fin set dots\n");
	return (0);
}

void	print_dots(t_window *win, t_inputs *inputs, t_map *map)
{
	int	x;
	int	y;
	int	j;
	int	i;

	printf("Debut print dots\n");
	i = -1;
	while (++i < inputs->leny)
	{
		j = -1;
		while (++j < inputs->lenx)
		{
			printf(".\n");
			printf("x = %f\t-\ty = %f\n", map->tabdot[i][j]->x, map->tabdot[i][j]->y);
			x = map->tabdot[i][j]->x;
			y = map->tabdot[i][j]->y;
			if (j + 1 != inputs->lenx)
			{
				if (!((x < 0 || x > win->width || y < 0 || y > win->height) &&
				(map->tabdot[i][j + 1]->x < 0 ||
				map->tabdot[i][j + 1]->x > win->width ||
				map->tabdot[i][j + 1]->y < 0 ||
				map->tabdot[i][j + 1]->y > win->height)))
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i][j + 1]);
			}
			if (i + 1 != inputs->leny)
			{
				if (!((x < 0 || x > win->width || y < 0 || y > win->height) &&
				(map->tabdot[i + 1][j]->x < 0 ||
				map->tabdot[i + 1][j]->x > win->width ||
				map->tabdot[i + 1][j]->y < 0 ||
				map->tabdot[i + 1][j]->y > win->height)))
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i + 1][j]);
			}
		}
	}
	printf("Fin print dot\n");
}

void	ft_print_bordure(t_window *win)
{
	t_par	bordure;

	bordure.d1.x = 0;
	bordure.d1.y = 0;
	bordure.d2.x = win->width;
	bordure.d2.y = 0;
	bordure.d3.x = win->width;
	bordure.d3.y = win->height / 10;
	bordure.d4.x = 0;
	bordure.d4.y = win->height / 10;
	ft_put_par(win, bordure, 0x50BB50);
	bordure.d1.x = 0;
	bordure.d1.y = 9 * win->height / 10;
	bordure.d2.x = win->width;
	bordure.d2.y = 9 * win->height / 10;
	bordure.d3.x = win->width;
	bordure.d3.y = win->height;
	bordure.d4.x = 0;
	bordure.d4.y = win->height;
	ft_put_par(win, bordure, 0x50BB50);
}

/*t_par	set_par(t_dot *d1, t_dot *d2, t_dot *d3, t_dot *d4)
{
	t_par	par;

	par.d1.x = d1->x;
	par.d1.y = d1->y;
	par.d2.x = d2->x;
	par.d2.y = d2->y;
	par.d3.x = d3->x;
	par.d3.y = d3->y;
	par.d4.x = d4->x;
	par.d4.y = d4->y;
	return (par);
}*/

/*printf("Fin malloc 3 :\n");
			printf("%f\n", map->zoom);
			printf("%f\n", map->i.x);
			printf("%f\n", map->centre.x);
			printf("%f\n", map->j.x);
			printf("%f\n", map->centre.y);
			printf("%f\n", map->k.x);
			printf("%f\n", map->origin.x);
			printf("%f\n", inputs->tab[i][j]);*/
