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

int		ft_init(t_window *win, t_map *map)
{
	float		dx;
	float		dy;

	dx = 10;
	dy = 4;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	map->zoom = 1.5;
	map->origin.x = win->width / 2;
	map->origin.y = win->height / 2;
	map->i.x = map->zoom * dx;
	map->i.y = map->zoom * dy;
	map->j.x = map->zoom * (-dx);
	map->j.y = map->zoom * dy;
	map->k.x = map->zoom * 0;
	map->k.y = map->zoom * (-5.8); 
	/*map->i.x = map->zoom * 10;
	map->i.y = map->zoom * 0;
	map->j.x = map->zoom * 0;
	map->j.y = map->zoom * 0;
	map->k.x = map->zoom * 0;
	map->k.y = map->zoom * (-10);*/
	map->tabdot = NULL;
	map->centre.x = win->inputs->lenx / 2 - ((win->inputs->lenx % 2) ? 0 : 0.5);
	map->centre.y = win->inputs->leny / 2 - ((win->inputs->leny % 2) ? 0 : 0.5);
	return (0);
}
void		ft_get_colors(t_window *win, char *point, int i, int j)
{//Bien malloc tou ca
	if (ft_strlen(point) != ft_nbrlen(ft_atoi(point)))
		win->inputs->colors[i][j] = ft_atoi_base(
		ft_strsub(point, 3, 8), 16);
}

int		ft_parse(t_window *win, char *file)
{
	//gnl - split - nb de cases - malloc tabint - convertir char/int - addinttab -
	int		count;
	int		ret;
	int		j;
	int		nline;

	if ((win->inputs->fd = open(file, O_RDONLY)) == -1)
		return (1);
	if (!(win->inputs->tab = (int **)malloc(sizeof(int *))))
		return (1);
	if (!(win->inputs->colors = (int **)malloc(sizeof(int *))))
		return (1);
	//win->inputs->tab = NULL;
	/*if (!(win->inputs->line = ft_strnew(0)))
		return (1);*/
	printf("Fin malloc tab & line\n");
	nline = 0;
	ret = 1;
	while ((ret = get_next_line(win->inputs->fd, &(win->inputs->line))) == 1)
	{
		win->inputs->tabstr = ft_strsplit(win->inputs->line, ' ');
		/*count = -1;
		while (win->inputs->tabstr[++count]);*/
		count = ft_tablen(win->inputs->tabstr);
		if (!(win->inputs->tmp = (int *)malloc(sizeof(int) * count)))
			return (1);
		j = -1;
		while (++j < count)
		{
			win->inputs->tmp[j] = ft_atoi(win->inputs->tabstr[j]);
			ft_get_colors(win, win->inputs->tabstr, j);
		}
		win->inputs->tab = ft_addinttab(win->inputs->tab, win->inputs->tmp, nline);
        //printf("Apres addinttab\n");
		nline++;
	}
	win->inputs->lenx = count;
	win->inputs->leny = nline;
	//printf("Leny : %i\n", win->inputs->leny);
	return (0);
}

int		main(int ac, char **av)
{
	t_window	win;
	t_map		map;
	t_inputs	inputs;
	int		ifile;
	
	win.inputs = &inputs;
	win.map = &map;
	
	ifile = ft_params(&win, ac, av);
	printf("Fin check params\n");
	
	mlx_mouse_hook(win.win, &mouse_hook, &win);
	mlx_key_hook(win.win, &key_hook, &win);
	mlx_loop(win.mlx);

	if (ft_parse(&win, av[ifile]))
		return (0);
	printf("Fin set parse\n");
	if (ft_init(&win, win.map))
		return (0);
	printf("Fin set init\n");

	ft_refresh(&win);
	//ft_print_bordure(&win);
	mlx_mouse_hook(win.win, &mouse_hook, &win);
	mlx_key_hook(win.win, &key_hook, &win);
	mlx_loop(win.mlx);
	return (0);
}

//ATTENTION FICHIERS INVALIDE

//Couleur ?
//Zoom
//Translation fleches
//Options
//	-	Taille fenetre
//	-	Nom fenetre
//Centres
