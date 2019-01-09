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

int		ft_params(t_window *win, int ac, char **av)
{
	int			i;
	int			ifile;

	i = 0;
	ifile = 1;
	win->name = ft_strdup("Fdf");
	win->width = 1000;
	win->height = 1000;
	printf("Nombre params : %i\n", ac);
	if (ac == 1)
		ft_putstr("Fichier manquant\n");
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-name"))
		{
			if (i + 1 < ac)
				win->name = av[i + 1];
			i++;
		}
		else if (!ft_strcmp(av[i], "-len"))
		{
			if (i + 1 < ac)
				win->width = ft_atoi(av[i++ + 1]);
			if (i + 1 < ac)
				win->height = ft_atoi(av[i++ + 2]);
		}
		else
			ifile = i;
	}
	
	return (ifile);
}

int		ft_init_tabdot(t_window *win, t_inputs *inputs, t_map *map)
{
	int	i;
	int	j;

	if (!(map->tabdot = (t_dot ***)malloc(sizeof(t_dot **) * (inputs->leny + 1))))
		return (1);
	printf("Fin malloc\n");
	map->tabdot[inputs->leny] = NULL;
	i = -1;
	while (++i < inputs->leny)
	{
		printf("New line\n");
		if (!(map->tabdot[i] = (t_dot **)malloc(sizeof(t_dot *) * (inputs->lenx + 1))))
			return (1);
		map->tabdot[i][inputs->lenx] = NULL;
		j = -1;
		while (++j < inputs->lenx)
		{
			if (!(map->tabdot[i][j] = (t_dot *)malloc(sizeof(t_dot))))
				return (1);
			//map->tabdot[i][j]->x = -1;
			//map->tabdot[i][j]->y = -1;
		}
	}
	return (0);
}

int		ft_init(t_window *win, t_inputs *inputs, t_map *map)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	map->zoom = 1.5;
	map->origin.x = win->width / 2;
	map->origin.y = win->height / 2;
	map->i.x = map->zoom * 10;
	map->i.y = map->zoom * 4;
	map->j.x = map->zoom * (-10);
	map->j.y = map->zoom * 4;
	map->k.x = map->zoom * 0;
	map->k.y = map->zoom * (-10.7);
	map->centre.x = win->inputs->lenx / 2 - ((win->inputs->lenx % 2) ? 0 : 0.5);
	map->centre.y = win->inputs->leny / 2 - ((win->inputs->leny % 2) ? 0 : 0.5);
	ft_init_tabdot(win, inputs, map);
	return (0);
}

int		ft_parse(t_inputs *inputs, char *file)
{
	//gnl - split - nb de cases - malloc tabint - convertir char/int - addinttab -
	int		count;
	int		ret;
	int		j;
	int		nline;
	char		*info;

	if ((inputs->fd = open(file, O_RDONLY)) == -1)
		return (1);
	if (!(inputs->tab = (int **)malloc(sizeof(int *))))
		return (1);
	if (!(inputs->colors = (int **)malloc(sizeof(int **))))
		return (1);
	printf("Fin malloc tab & line\n");
	nline = 0;
	ret = 1;
	while ((ret = get_next_line(inputs->fd, &(inputs->line))) == 1)
	{
		inputs->tabstr = ft_strsplit(inputs->line, ' ');
		count = ft_tablen(inputs->tabstr);
		if (!(inputs->tmptab = (int *)malloc(sizeof(int) * count)))
			return (1);
		if (!(inputs->tmpcolors = (int *)malloc(sizeof(int) * count)))
			return (1);
		ft_filltabint(&(inputs->tmpcolors), count, ft_atoi_base("FFFFFF", 16));
		j = -1;
		while (++j < count)
		{
			info = inputs->tabstr[j];
			inputs->tmptab[j] = ft_atoi(inputs->tabstr[j]);
			if (ft_strlen(info) != ft_nbrlen(ft_atoi(info)))
				inputs->tmpcolors[j] = ft_atoi_base(ft_strsub(info, ft_nbrlen(ft_atoi(info)) + 3, ft_strlen(info) - ft_nbrlen(ft_atoi(info)) - 3), 16);
		}
		inputs->tab = ft_addinttab(inputs->tab, inputs->tmptab, nline);
		inputs->colors = ft_addinttab(inputs->colors, inputs->tmpcolors, nline);
        //printf("Apres addinttab\n");
		nline++;
	}
	inputs->lenx = count;
	inputs->leny = nline;
	//printf("Leny : %i\n", win->inputs->leny);
	return (0);
}

int		main(int ac, char **av)
{
	t_window	win;
	t_map		map;
	t_inputs	inputs;
	int			ifile;
	
	win.inputs = &inputs;
	win.map = &map;


	/*win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 1000, 1000, "gv");
	t_dot d1;
	t_dot d2;
	d1.x = 100;
	d2.x = 900;
	d1.y = 100;
	d2.y = 900;
	d1.color.r = ft_atoi_base("50BB50", 16) / (16 * 16 * 16 * 16);
	d1.color.g = (ft_atoi_base("50BB50", 16) % (16 * 16 * 16 * 16)) / (16 * 16);
	d1.color.b = ft_atoi_base("50BB50", 16) % (16 * 16);

	d2.color.r = ft_atoi_base("5050FF", 16) / (16 * 16 * 16 * 16);
	d2.color.g = (ft_atoi_base("5050FF", 16) % (16 * 16 * 16 * 16)) / (16 * 16);
	d2.color.b = ft_atoi_base("5050FF", 16) % (16 * 16);
	
	printf("RGB 1 : %f, %f, %f\n", d1.color.r, d1.color.g, d1.color.b);
	printf("RGB 2 : %f, %f, %f\n", d2.color.r, d2.color.g, d2.color.b);
			
	ft_put_line(&win, &d1, &d2);
	mlx_loop(win.mlx);*/

	


	ifile = ft_params(&win, ac, av);
	printf("Fin check params\n");

	if (ft_parse(&inputs, av[ifile]))
		return (0);
	printf("Fin set parse\n");

	if (ft_init(&win, win.inputs, win.map))
		return (0);
	printf("Fin set init\n");

	ft_refresh(&win);
	//ft_print_bordure(&win);
	mlx_mouse_hook(win.win, mouse_hook, &win);
	mlx_key_hook(win.win, key_hook, &win);
	mlx_loop(win.mlx);
	return (0);
}

//ATTENTION FICHIERS INVALIDE

//Couleur ?..
//Zoom
//Translation fleches
//Options
//	-	Taille fenetre
//	-	Nom fenetre
//Centres
//echo $? pour retour de la derniere commande