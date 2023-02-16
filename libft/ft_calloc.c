/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:58:12 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/16 14:59:21 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_calloc(size_t cnt, size_t n)
// {
// 	void	*ptr;
// 	int		result;

// 	if (cnt == 0 || n == 0)
// 		return (NULL);
// 	result = (cnt * n);
// 	if (result / cnt != n)
// 		return (NULL);
// 	ptr = ((void *) malloc (cnt * n));
// 	if (!ptr)
// 		return (NULL);
// 	ft_bzero(ptr, n * cnt);
// 	return (ptr);
// }

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*alloc;
	size_t		alloc_size;

	alloc_size = nmemb * size;
	if (alloc_size / size != nmemb && size)
		return (NULL);
	alloc = malloc(alloc_size);
	if (!alloc)
		return (NULL);
	ft_bzero(alloc, alloc_size);
	return (alloc);
}