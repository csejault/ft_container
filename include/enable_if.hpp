/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:38:15 by csejault          #+#    #+#             */
/*   Updated: 2022/02/10 18:41:09 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP
namespace ft {

	template <bool Cond, class T = void>
		struct enable_if {}
	template<class T>
		struct enable_if<true, T> { typedef T type; };
}
#endif
