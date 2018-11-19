/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/10 17:21:09 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/11 17:41:52 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "fdf.h"

int		deal_key(int key)
{
	exit(EXIT_SUCCESS);
	return (0);
}

void		set_vectors(s_map map)
{
	float dx;
	float dy;

	dx = 5;
	dy = 3;
	map->zoom = 10;
	map->origin.x = WX / 2;
	map->origin.y = WY / 2;
	map->i.dx = map->zoom * dx;
	map->i.dy = map->zoom * dy;
	map->j.dx = map->zoom * (-dx);
	map->j.dy = map->zoom * dy;
	map->k.dx = map->zoom * 0;
	map->k.dy = map->zoom * (-ft_sqrt(dx*dx + dy*dy));
}

int		ft_init(s_window *win, s_inputs *inputs, s_map map)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, 1000, 1000, "Test");
	inputs->line = ft_strnew(0);
	inputs->tabstr = NULL;
	inputs->tmp = NULL;
	inputs->tab = NULL;
	set_vectors(map);	
	return (0);
}

int		ft_parse(s_inputs *inputs, char *file)
{
	//gnl - split - nb de cases - malloc tabint - convertir char/int - addinttab -
	int		count;
	int		ret;
	int		j;
	int		nline;

	if ((inputs->fd = open(file, O_RDONLY)) == -1)
		return (1);
	if (!(inputs->tab = (int **)malloc(sizeof(int *))))
		return (1);
	nline = 0;
	while ((ret = get_next_line(inputs->fd, &(inputs->line))) == 1)
	{
		inputs->tabstr = ft_strsplit(inputs->line, ' ');
		count = 0;
		while (inputs->tabstr[count])
			count++;
		if (!(inputs->tmp = (int *)malloc(sizeof(int) * count)))
			return (1);
		j = -1;
		while (++j < count)
			inputs->tmp[j] = ft_atoi(inputs->tabstr[j]);
		inputs->tab = ft_addinttab(inputs->tab, inputs->tmp, nline);
		nline++;
	}
	inputs->lenx = count;
	inputs->leny = nline;
	return (0);
}

int		set_point(s_window win, s_inputs inputs, s_map map)
{
	int	i;
	int	j;

	if (!(map->tabdot = (s_dot ***)malloc(sizeof(s_dot **) * (inputs->leny + 1))))
		return (1);
	map->tabdot[inputs->leny] = NULL;
	i = -1;
	while (inputs->tabstr[++i])
	{
		if (!(map->tabdot[i] = (s_dot **)malloc(sizeof(s_dot *) * (inputs->lenx + 1))))
			return (1);
		map->tabdot[inputs->lenx] = NULL;
		j = -1;
		while (inputs->tabstr[i][++j])
		{
			if (!(map->tabdot[i][j] = (s_dot *)malloc(sizeof(s_dot))))
				return (1);
			map->tabdot[i][j].x = map.zoom * (map.i.x * (j - origin.x) + map.j.x * (i - origin.y));
			map->tabdot[i][j].y = map.zoom * (map.i.y * (j - origin.x) + map.j.y * (i - origin.y));
		}	
	}
	return (0);
}

int		main(int ac, char **av)
{
	s_window	win;
	s_inputs	inputs;
	s_map		map;

	if (ac == 1)
		ft_putstr("Fichier manquant\n");
	if (ft_init(&win, &inputs, &map))
		return (0);
	if (ft_parse(&inputs, av[1]))
		return (0);	
	
	if (intputs.lenx % 2 == 0)//Ternaire ?
		map.origin.x = inputs.lenx / 2 - 0.5;
	else
		map.origin.x = inputs.lenx / 2;
	if (intputs.leny % 2 == 0)//Ternaire ?
		map.origin.y = inputs.leny / 2 - 0.5;
	else
		map.origin.y = inputs.leny / 2;
	
	if (set_point(win, inputs, map))
		return (0);

	mlx_loop(win.mlx);
	return (0);
}
