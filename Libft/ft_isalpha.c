/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:51:04 by mhabbal           #+#    #+#             */
/*   Updated: 2024/06/10 13:57:12 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int C)
{
	if ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'))
	{
		return (1);
	}
	return (0);
}