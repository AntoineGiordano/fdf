/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/10 17:21:09 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 16:38:10 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

int		deal_key(int key)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_init(s_window *win, s_inputs *inputs, s_map *map)
{
	float dx;
	float dy;

	dx = 10;
	dy = 4;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, 1000, 1000, "Test");
	map->zoom = 2.5;
	map->origin.x = 1000 / 2;
	map->origin.y = 1000 / 2;
	map->i.x = map->zoom * dx;
	map->i.y = map->zoom * dy;
	map->j.x = map->zoom * (-dx);
	map->j.y = map->zoom * dy;
	map->k.x = map->zoom * 0;
	map->k.y = map->zoom * (-5.8)/*(-ft_sqrt(dx*dx + dy*dy))*/;
	map->centre.x = inputs->lenx / 2 - ((inputs->lenx % 2) ? 0 : 0.5);
	map->centre.y = inputs->leny / 2 - ((inputs->leny % 2) ? 0 : 0.5);
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
	if (!(inputs->line = ft_strnew(0)))
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

int		main(int ac, char **av)
{
	s_window	win;
	s_inputs	inputs;
	s_map		map;
	s_par		par;

	if (ac == 1)
		ft_putstr("Fichier manquant\n");

	if (ft_parse(&inputs, av[1]))
		return (0);
	printf("Fin set parse\n");

	if (ft_init(&win, &inputs, &map))
		return (0);
	printf("Fin set init\n");

	if (set_dots(&win, &inputs, &map))
		return (0);
	printf("Fin set point\n");

	print_dots(&win, &inputs, &map);
	printf("Fin print dot\n");

	/*win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 1000, 1000, "Test");
	par.d1.x = 500;
	par.d1.y = 500;
	par.d2.x = 600;
	par.d2.y = 500;
	par.d3.x = 900;
	par.d3.y = 900;
	par.d4.x = 100;
	par.d4.y = 900;
	ft_put_par(&win, par, 0x005000);*/

	mlx_loop(win.mlx);
	return (0);
}

//Couleur
//Zoom
//Translation fleches
//Options
//	-	Proportionnalite
//	-	Taille fenetre
//	-	Nom fenetre
//Centres
