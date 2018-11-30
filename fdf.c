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
	int		i;
	int		ifile;

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
				win->width = ft_atoi(av[i + 1]);
			if (i + 2 < ac)
				win->height = ft_atoi(av[i + 2]);
			i += 2;
		}
		else
			ifile = i;
	}
	return (ifile);
}

int		ft_init(t_window *win)
{
	t_inputs	inputs;
	t_map		map;
	float		dx;
	float		dy;

	dx = 10;
	dy = 4;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	map.zoom = 1.5;
	map.origin.x = win->width / 2;
	map.origin.y = win->height / 2;
	map.i.x = map.zoom * dx;
	map.i.y = map.zoom * dy;
	map.j.x = map.zoom * (-dx);
	map.j.y = map.zoom * dy;
	map.k.x = map.zoom * 0;
	map.k.y = map.zoom * (-5.8);
	map.centre.x = inputs.lenx / 2 - ((inputs.lenx % 2) ? 0 : 0.5);
	map.centre.y = inputs.leny / 2 - ((inputs.leny % 2) ? 0 : 0.5);
	win->inputs = &inputs;
	win->map = &map;
	return (0);
}

int		ft_parse(t_inputs *inputs, char *file)
{
	//gnl - split - nb de cases - malloc tabint - convertir char/int - addinttab -
	int		count;
	int		ret;
	int		j;
	int		nline;

	if ((inputs->fd = open(file, O_RDONLY)) == -1)
		return (1);
		printf("Fin open\n");
	if (!(inputs->tab = (int **)malloc(sizeof(int *))))
		return (1);
	inputs->tab = NULL;
	if (!(inputs->line = ft_strnew(0)))
		return (1);
	printf("Fin malloc tab & line\n");
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
		printf("Valeur 0 : %i\n", inputs->tmp[0]);
		printf("Avant addinttab\n");
		inputs->tab = ft_addinttab(inputs->tab, inputs->tmp, nline);
        printf("Apres addinttab\n");
		nline++;
	}
	inputs->lenx = count;
	inputs->leny = nline;
	return (0);
}

int		main(int ac, char **av)
{
	t_window	win;
	int			ifile;
	
	ifile = ft_params(&win, ac, av);
	printf("Fin check params\n");

	if (ft_parse(win.inputs, av[ifile]))
		return (0);
	printf("Fin set parse\n");

	if (ft_init(&win))
		return (0);
	printf("Fin set init\n");

	if (set_dots(&win, win.inputs, win.map))
		return (0);
	printf("Fin set point\n");

	print_dots(&win, win.inputs, win.map);
	printf("Fin print dot\n");

	mlx_mouse_hook(win.mlx, &mouse_hook, &win);
	mlx_key_hook(win.mlx, &key_hook, &win);
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
