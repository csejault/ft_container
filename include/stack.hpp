/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:53:58 by csejault          #+#    #+#             */
/*   Updated: 2022/04/25 20:25:42 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
# include "vector.hpp"
namespace ft {
	template <class T, class Container = ft::vector<T> >
		class stack {

			public:

				typedef Container							container_type;
				typedef typename Container::value_type		value_type;
				typedef typename Container::size_type		size_type;
				typedef typename Container::reference		reference;
				typedef typename Container::const_reference	const_reference;

				// Constructor
				explicit stack(const Container& a = Container()) : c(a) {}

				// Accessors
				bool empty() const { return c.empty(); }
				size_type size() const { return c.size(); }
				value_type& top() { return c.back(); }
				const value_type& top() const { return c.back(); }
				void push(const value_type& p) { c.push_back(p); }
				void pop() { c.pop_back(); }


				friend bool operator==(const stack & lhs, const stack & rhs)
				{
					return(lhs.c == rhs.c); 
				}

				friend bool operator!=(const stack & lhs, const stack & rhs)
				{
					return(lhs.c != rhs.c); 
				}

				friend bool operator<(const stack & lhs, const stack & rhs)
				{
					return(lhs.c < rhs.c); 
				}

				friend bool operator<=(const stack & lhs, const stack & rhs)
				{
					return(lhs.c <= rhs.c); 
				}

				friend bool operator>(const stack & lhs, const stack & rhs)
				{
					return(lhs.c > rhs.c); 
				}

				friend bool operator>=(const stack & lhs, const stack & rhs)
				{
					return(lhs.c >= rhs.c); 
				}


			protected:
				Container	c;

		};

}
#endif
