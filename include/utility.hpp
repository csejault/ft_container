/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:28:04 by csejault          #+#    #+#             */
/*   Updated: 2022/04/07 16:51:25 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTILITY_HPP
# define UTILITY_HPP
namespace ft {
	template <class T1, class T2> 
		struct pair {
			typedef T1 first_type;
			typedef T2 second_type;
			T1		first;
			T2		second;
			pair( void ) : first(T1()), second(T2()) {}
			pair (const first_type& a, const second_type& b) : first(a), second(b) {}
			template <class V, class U>
				pair ( const pair <V, U> & p ) : first(p.first), second(p.second) {}
			pair&	operator=(const pair& rhs)
			{
				if (this != &rhs)
				{
					first = rhs.first;
					second = rhs.second;
				}
				return (*this);
			}
			~pair( void ) {}
		};

	template <class T1, class T2>
		bool operator == ( const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			if (x.first == y.first && x.second == y.second)
				return (true);
			return (false);
		}

	template <class T1, class T2>
		bool operator != (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return !(x==y);
		}

	template <class T1, class T2>
		bool operator < (const pair<T1, T2>& x, pair<T1, T2>& y)
		{
			if (x.first < y.first || (!(y.first < x.first) && x.second < y.second))
				return (true);
			return (false);
		}

	template <class T1, class T2>
		bool operator > (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return (y < x);
		}

	template <class T1, class T2>
		bool operator <= (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return !(y > x);
		}


	template <class T1, class T2>
		bool operator >= (const pair<T1, T2>& x, const pair <T1, T2>& y)
		{
			return !(x < y);
		}

	template <class T1,class T2>
		ft::pair<T1,T2> make_pair(T1 x, T2 y)
		{
			return ( ft::pair<T1,T2>(x,y) );
		}
}
#endif
