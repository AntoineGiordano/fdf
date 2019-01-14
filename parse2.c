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

int		flags(t_window *win, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-name"))
	{
		if (*i + 1 < ac)
			win->name = av[(*i)++ + 1];
	}
	else if (!ft_strcmp(av[*i], "-len"))
	{
		if (*i + 1 < ac)
			win->width = ft_atoi(av[++(*i)]);
		if (*i + 1 < ac)
			win->height = ft_atoi(av[++(*i)]);
	}
	else if (!ft_strcmp(av[*i], "-color"))
	{
		win->colorparam = 1;
		if (*i + 1 < ac)
			win->mincolor = ft_atoi_base(av[++(*i)], 16);
		if (*i + 1 < ac)
			win->maxcolor = ft_atoi_base(av[++(*i)], 16);
		printf("Min : %i\nMax : %i\n", win->mincolor, win->maxcolor);
	}
	else
		return (1);
	return (0);
}

int		params(t_window *win, int ac, char **av)
{
	int			i;
	int			ifile;

	i = 1;
	ifile = -1;
	win->colorparam = 0;
	win->name = ft_strdup("Fdf");
	win->width = 1000;
	win->height = 1000;
	win->maxcolor = 0x50BB50;
	win->mincolor = 0xFFFFFF;
	while (i < ac)
	{
		if (flags(win, ac, av, &i))
			ifile = i;
		i++;
	}
	//printf("fin params 1\n");
	return (ifile);
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

int		set_size(t_window *win, t_inputs *inputs, char *file)
{
	char	*line;
	char	**tab;
	int		nline;
	int		fd;
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (1);
	inputs->lenx = NULL;
	nline = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ret == -1)
			return (1);
		inputs->lenx = ft_addint(inputs->lenx, ft_tablen(tab = ft_strsplit(line, ' ')), nline++);
		//printf("Len : %i = %i\n", ft_tablen(tab = ft_strsplit(line, ' ')), inputs->lenx[nline]);
		ft_tabdel(&tab);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	inputs->leny = nline;
	close(fd);
	return (0);
}

int     parse(t_window *win, t_inputs *inputs, char *file)
{
	int		ret;
	int		nline;
	int		j;
	char	**tab;

	printf("Blanc : %i\n", ft_atoi_base("FFFFFF", 16));
	if (set_size(win, inputs, file))
		return (1);
	printf("Fin set size\n");
	if (ft_init_tabs(win, inputs, win->map))
		return (1);
	printf("Fin init tabs\n");
	if ((inputs->fd = open(file, O_RDONLY)) == -1)
		return (1);
	nline = 0;
	while ((ret = get_next_line(inputs->fd, &(inputs->line)) == 1))
	{
		tab = ft_strsplit(inputs->line, ' ');
		j = -1;
		while (++j < inputs->lenx[nline])
		{
			inputs->tab[nline][j] = ft_atoi(tab[j]);
			if (inputs->tab[nline][j] > win->map->maxz)
				win->map->maxz = inputs->tab[nline][j];
			else if (inputs->tab[nline][j] < win->map->minz)
				win->map->minz = inputs->tab[nline][j];
			if (!(win->colorparam))
			{
				win->map->tabdot[nline][j]->color = 16777215;
				if (ft_strstr(tab[j], ",0x"))
					win->map->tabdot[nline][j]->color = ft_atoi_base(ft_strstr(tab[j], ",0x") + 3, 16);
			}
		}
		ft_tabdel(&tab);
		ft_strdel(&(inputs->line));
		nline++;
	}
	printf("Min : %i\nMax : %i\n", win->map->minz, win->map->maxz);
	ft_strdel(&(inputs->line));
	colors(win, inputs, win->map);
	close(inputs->fd);
	return (0);
}

//colorparam = 1	->	Proportionnalite : minz_maxz. Pas de lecture des couleurs dans le parsing
//colorparam = 0	->	Parse des couleurs du fichier. Set a 0xFFFFFF de chaque points
