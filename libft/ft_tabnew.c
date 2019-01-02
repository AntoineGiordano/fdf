/*HEADER*/

#include "libft.h"

char	**ft_tabnew(size_t nline, size_t lline)
{
	char	**tab;
	size_t	i;

	tab = (char **)malloc(sizeof(char *) * (nline + 1));
	tab[nline] = NULL;
	i = -1;
	while (++i < nline)
		tab[i] = ft_strnew((int) lline);
	return (tab);
}
