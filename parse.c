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

int		ft_params_2(t_window *win, int ac, char **av, int *i)
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

int		ft_params(t_window *win, int ac, char **av)
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
		if (ft_params_2(win, ac, av, &i))
			ifile = i;
		i++;
	}
	//printf("fin params 1\n");
	return (ifile);
}
/*
min        current                max
RGB1       color                  RGB2
*/

void	set_z(t_window *win, t_inputs *inputs, char *line, int j)
{
	//printf("Debut set z\n");
	line = inputs->tabline[j];
	inputs->tmptab[j] = ft_atoi(line);
	if (inputs->tmptab[j] > win->map->maxz)
		win->map->maxz = inputs->tmptab[j];
	if (inputs->tmptab[j] < win->map->minz)
		win->map->minz = inputs->tmptab[j];
	if ((!(win->colorparam) && (ft_strlen(line) != ft_nbrlen(ft_atoi(line)))) ||
	((ft_strlen(line) != ft_nbrlen(ft_atoi(line)) + 1) && line[0] == '-'))
		inputs->tmpcolors[j] = ft_atoi_base(ft_strsub(line, ft_nbrlen(ft_atoi(line)) + 3, ft_strlen(line) - ft_nbrlen(ft_atoi(line)) - 3), 16);
	//printf("Fin set z\n");
}

int		ft_parse_2(t_window *win, t_inputs *inputs, int *count, int *nline)
{
	char	*line;
	int		j;

	inputs->tabline = ft_strsplit(inputs->line, ' ');
	*count = ft_tablen(inputs->tabline);
	if (!(inputs->tmptab = (int *)malloc(sizeof(int) * *count)))
		return (1);
	if (!(inputs->tmpcolors = (int *)malloc(sizeof(int) * *count)))
		return (1);
	ft_filltabint(&(inputs->tmpcolors), *count, ft_atoi_base("FFFFFF", 16));
	j = -1;
	while (++j < *count)
	{
		//printf("Nb : %s\n", inputs->tabline[j]);
		set_z(win, inputs, line, j);
	}
	inputs->tab = ft_addinttab(inputs->tab, inputs->tmptab, *nline);
	inputs->colors = ft_addinttab(inputs->colors, inputs->tmpcolors, *nline);
	free(inputs->tabline);
	//printf("Fin sous parse\n");
	return (0);
}

int		ft_parse(t_window *win, t_inputs *inputs, char *file)
{
	//gnl - split - nb de cases - malloc tabint - convertir char/int - addinttab -
	int		count;
	int		ret;
	int		nline;

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
		if (ft_parse_2(win, inputs, &count, &nline))
			return (1);
		free(inputs->line);
		nline++;
	}
	inputs->lenx = count;
	inputs->leny = nline;
	return (0);
}
