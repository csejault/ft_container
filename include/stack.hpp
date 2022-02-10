/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:53:58 by csejault          #+#    #+#             */
/*   Updated: 2022/02/08 17:03:03 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
# include <deque>
namespace ft {
	template <class T, class Container = std::deque<T> >
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

			protected:
				Container	c;

		};

	// Nonmember Operators
	template <class T, class Container>
		bool operator==(const stack<T, Container>& a,
				const stack<T, Container>& b) { return a.c == b.c; }

	template <class T, class Container>
		bool operator!=(const stack<T, Container>& a, 
				const stack<T, Container>& b) { return !( a.c == b.c); }

	template <class T, class Container>
		bool operator<(const stack<T, Container>& a,
				const stack<T, Container>& b) { return a.c < b.c; }

	template <class T, class Container>
		bool operator>(const stack<T, Container>& a,
				const stack<T, Container>& b) { return a.c > b.c; }

	template <class T, class Container>
		bool operator<=(const stack<T, Container>& a,
				const stack<T, Container>& b) { return a.c <= b.c; }

	template <class T, class Container>
		bool operator>=(const stack<T, Container>& a,
				const stack<T, Container>& b) { return a.c >= b.c; }
}
#endif
