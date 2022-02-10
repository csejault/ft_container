/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:22:05 by csejault          #+#    #+#             */
/*   Updated: 2022/02/09 18:04:46 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// the type of the container’s elements is passed as the first template argument and is known as its value_type
// allocator_type  19.4
//

//In general, size_type specifies the type used for indexing into the container, 
//   and difference_type is the type of the result of subtracting two iterators for a container.
//   For most containers, they correspond to size_t and ptrdiff_t (§6.2.1).
//
//Having to add typename before the names of member types of a template parameter is a nuisance.
//However, the compiler isn’t psychic. There is no general way for it to know whether a member of a template argument type is a typename (§C.13.5).
//
//https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <vector>
namespace ft {

template typename<class T>
	class vector : public std::vector
	{
	};

}
#endif
