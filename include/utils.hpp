/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:40:36 by csejault          #+#    #+#             */
/*   Updated: 2022/04/20 15:44:12 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
namespace ft {
	template <class T>
	void swap(T &l, T &r)
	{
		T tmp = l;
		l = r;
		r = tmp;
	}
}
#endif
