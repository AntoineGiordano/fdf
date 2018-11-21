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

int		set_dots(s_window *win, s_inputs *inputs, s_map *map)
{
	int	i;
	int	j;

	printf("Debut\n");
	if (!(map->tabdot = (s_dot ***)malloc(sizeof(s_dot **) * (inputs->leny + 1))))
		return (1);
	printf("Fin malloc\n");
	map->tabdot[inputs->leny] = NULL;
	i = -1;
	while (++i < inputs->leny)
	{
		printf("New line\n");
		if (!(map->tabdot[i] = (s_dot **)malloc(sizeof(s_dot *) * (inputs->lenx + 1))))
			return (1);
		printf("Fin malloc 2\n");
		map->tabdot[inputs->lenx] = NULL;
		j = -1;
		while (++j < inputs->lenx)
		{
			printf("New point\n");
			if (!(map->tabdot[i][j] = (s_dot *)malloc(sizeof(s_dot))))
				return (1);
			/*printf("Fin malloc 3 :\n");
			printf("%f\n", map->zoom);
			printf("%f\n", map->i.x);
			printf("%f\n", map->centre.x);
			printf("%f\n", map->j.x);
			printf("%f\n", map->centre.y);
			printf("%f\n", map->k.x);
			printf("%f\n", map->origin.x);
			printf("%f\n", inputs->tab[i][j]);*/
			map->tabdot[i][j]->x = map->zoom * (map->i.x * (j - map->centre.x) + map->j.x * (i - map->centre.y) + map->k.x * inputs->tab[i][j]) + map->origin.x;
			map->tabdot[i][j]->y = map->zoom * (map->i.y * (j - map->centre.x) + map->j.y * (i - map->centre.y) + map->k.y * inputs->tab[i][j]) + map->origin.y;
		}	
	}
	return (0);
}

void	print_dots(s_window *win, s_inputs *inputs, s_map *map)
{
	int		j;
	int		i;
	s_par	par;

	printf("len y = %i\nlen x = %i\n", inputs->leny, inputs->lenx);
	i = -1;
	while (++i < inputs->leny)
	{
		j = -1;
		while (++j < inputs->lenx)
		{
			//printf("x = %f\ny = %f\n\n", map->tabdot[i][j]->x, map->tabdot[i][j]->y);
			if (j + 1 < inputs->lenx)
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i][j + 1], 0x00FF00);
			if (i + 1 < inputs->leny)
				ft_put_line(win, map->tabdot[i][j], map->tabdot[i + 1][j], 0x00FF00);
			/*if (j + 1 < inputs->lenx && i + 1 < inputs->leny)
			{
				par = set_par(map->tabdot[i][j], map->tabdot[i][j + 1], map->tabdot[i + 1][j + 1], map->tabdot[i + 1][j]);
				ft_put_par(win, par, 0x00FF00);
			}*/
		}
	}
}

s_par	set_par(s_dot *d1, s_dot *d2, s_dot *d3, s_dot *d4)
{
	s_par	par;

	par.d1.x = d1->x;
	par.d1.y = d1->y;
	par.d2.x = d2->x;
	par.d2.y = d2->y;
	par.d3.x = d3->x;
	par.d3.y = d3->y;
	par.d4.x = d4->x;
	par.d4.y = d4->y;
	return (par);
}