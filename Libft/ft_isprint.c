/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:02:28 by mhabbal           #+#    #+#             */
/*   Updated: 2024/06/17 23:47:18 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int C)
{
	if (C > 31 && C < 127)
		return (1);
	return (0);
}