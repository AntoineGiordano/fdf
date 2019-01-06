/*HEADER*/

void	ft_filltabint(int **tab, size_t len, int nbr)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		(*tab)[i] = nbr;
		i++;
	}
}
