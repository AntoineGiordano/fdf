/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_addinttab.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 20:16:36 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/12 05:54:03 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		**ft_addinttab(int **tab, int *line, size_t length)
{
	int		**newtab;
	size_t	i;

	newtab = (int **)malloc(sizeof(int *) * (length + 1));
	i = 0;
	while (i < length)
	{
		newtab[i] = tab[i];
		tab[i] = NULL;
		i++;
	}
	newtab[i] = line;
	free(tab);
	return (newtab);
}
