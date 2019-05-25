/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnormdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:56:13 by rkeli             #+#    #+#             */
/*   Updated: 2019/05/04 03:46:20 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstnormdel(t_list *alst)
{
	t_list *link;

	if (!alst)
		return ;
	while (alst)
	{
		link = alst->next;
		ft_lstnormdelone(alst);
		free(alst);
		alst = link;
	}
	free(link);
	alst = NULL;
}
