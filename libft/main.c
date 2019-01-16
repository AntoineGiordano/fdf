/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 17:09:15 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 18:10:15 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"
#include "stdlib.h"
/*
int		main(void)
{
	char **tab;
	char **newtab;

	tab = ft_tabnew(2, 3);
	newtab = ft_tabnew(2, 3);
	ft_strfill(tab[0], 'A', 3);
	ft_strfill(tab[1], 'B', 3);
	ft_strfill(newtab[0], 'X', 3);
	ft_strfill(newtab[1], 'X', 3);

	ft_printtabl(tab);
	ft_printtabl(newtab);

	if (!(ft_tabcpy(newtab, tab)))
		ft_putendl("Error");

	ft_printtabl(tab);
	ft_printtabl(newtab);

	ft_tabdel(&tab);
	ft_printtabl(tab);
	ft_printtabl(newtab);

	ft_putendl("Fin");
	return (0);
}*/

int main(int ac, char **av)
{
	char *line;
	int fd;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("Line : %s\n", line);
		ft_strdel(&line);
	}
	return (0);
}