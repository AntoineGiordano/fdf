/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 17:41:29 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/22 19:24:26 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libc.h>

int	f(int a, int b)
{
	return (a < b);
}

int		main(int ac, char **av)
{
	int tab[3] = {101, 42, 0};
	printf("%i\n", tab[0]);
	printf("%i\n", tab[1]);
	printf("%i\n", tab[2]);
	ft_sorttab(tab, 3, &f);
	printf("%i\n", tab[0]);
	printf("%i\n", tab[1]);
	printf("%i\n", tab[2]);

	return (0);
}
