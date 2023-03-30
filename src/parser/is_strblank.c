/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_strblank.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaiane- < kdaiane-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:12:52 by kdaiane-          #+#    #+#             */
/*   Updated: 2023/03/30 20:12:53 by kdaiane-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_strblank(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (!*str)
		return (1);
	return (0);
}
