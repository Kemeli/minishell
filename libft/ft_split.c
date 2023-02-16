/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:02:02 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/02/16 15:00:02 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ft_count_words(char *s, char c)
// {
// 	size_t	words;

// 	words = 0;
// 	if (*s == '\0')
// 		return (words);
// 	if (c == '\0')
// 		return (1);
// 	while (*s == c && *s)
// 		s++;
// 	while (*s)
// 	{
// 		words++;
// 		while (*s != c && *s)
// 		s++;
// 		while (*s == c && *s)
// 			s++;
// 	}
// 	return (words);
// }

// static int	get_word_len(char *s, char c)
// {
// 	int		i;
// 	size_t	len;

// 	i = 0;
// 	len = 0;
// 	while (s[i] == c && s[i])
// 		i++;
// 	while (s[i] != c && s[i])
// 	{
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }

// static char	*ft_get_word(char const *s, size_t len, char c)
// {
// 	size_t	i;
// 	char	*str1;

// 	str1 = (char *) malloc(sizeof(char) * len + 1);
// 	if (str1 == NULL)
// 		return (NULL);
// 	while (*s == c)
// 		s++;
// 	i = 0;
// 	while (i < len)
// 	{
// 		str1[i] = *s;
// 		s++;
// 		i++;
// 	}
// 	str1[i] = '\0';
// 	return (str1);
// }

// static void	*free_mem(char **arr, int i)
// {
// 	while (--i > -1)
// 		free(arr[i]);
// 	free(arr);
// 	return (NULL);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr;
// 	int		word_n;
// 	size_t	len;
// 	int		i;
// 	char	*str2;

// 	str2 = (char *)s;
// 	word_n = ft_count_words(str2, c);
// 	arr = malloc((word_n + 1) * (sizeof (char *)));
// 	if (arr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < word_n)
// 	{
// 		len = get_word_len(str2, c);
// 		arr[i] = ft_get_word(str2, len, c);
// 		if (arr[i] == NULL)
// 			return (free_mem(arr, i));
// 		i++;
// 		while (*str2 == c)
// 			str2++;
// 		str2 = str2 + len + 1;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }

static void	ft_insertstr(char **list, char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	start;

	i = 0;
	len = 0;
	start = 0;
	while (s[start + len])
	{
		while (s[start] == c && s[start])
			start++;
		while (s[start + len] != c && s[start + len])
			len++;
		if (len)
		{
			list[i] = ft_substr(s, start, len);
			start = start + len;
			len = 0;
			i++;
		}
	}
	list[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c && i != 0 && s[i - 1] != c)
			count++;
		i++;
	}
	if (i != 0 && s[i - 1] != c && ft_strlen(s) > 0)
		count++;
	list = malloc(sizeof(char *) * (count + 1));
	if (!list)
		return (NULL);
	ft_insertstr(list, s, c);
	return (list);
}
