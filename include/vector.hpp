/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:59:58 by csejault          #+#    #+#             */
/*   Updated: 2022/03/04 17:52:11 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "type_traits.hpp"
#include "iterator.hpp"
#include <memory>
#include <stdexcept>
#include <limits>
#include <iostream>

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
		class vector {
			public:

				/////////////
				//         //
				// TYPEDEF //
				//         //
				/////////////

				typedef T									value_type;
				typedef Allocator							allocator_type;
				typedef	std::size_t							size_type;
				typedef std::ptrdiff_t						difference_type;
				typedef value_type&							reference;
				typedef const value_type&					const_reference;
				typedef typename Allocator::pointer			pointer;
				typedef typename Allocator::const_pointer	const_pointer;
				typedef value_type*							iterator;
				typedef const value_type*					const_iterator;
				typedef	ft::reverse_iterator<iterator>		reverse_iterator;
				typedef ft::reverse_iterator<const iterator>	const_reverse_iterator;




				//enable if and is !integral
				template <class InputIterator>
					vector(InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc_arg = allocator_type()) : elem(NULL), sz(0), space(0), alloc(alloc_arg)
				{
					for (InputIterator it = first; it != last; it++)
						push_back(*it);
				}


				/////////////////
				//             //
				// CONSTRUCTOR //
				//             //
				/////////////////

				explicit vector(const allocator_type& alloc_arg = allocator_type()) : elem(NULL), sz(0), space(0), alloc(alloc_arg) { }

				explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& allocator_arg = allocator_type()) : elem(NULL), sz(0), space(0), alloc(allocator_arg)
			{
				for (size_type i = 0 ; i < n; i++)
					push_back(value);
			}

				vector(const vector& x) : elem(NULL), sz(0), space(0) { *this = x; }


				////////////////
				//            //
				// DESTRUCTOR //
				//            //
				////////////////

				~vector()
				{
					clear();
					alloc.deallocate(elem, space);
				}


				//////////////
				//          //
				// OPERATOR //
				//          //
				//////////////

				vector<T, Allocator>& operator=(const vector<T, Allocator>& x)
				{
					if (&x != this)
					{
						if (x.sz > space)
						{
							pointer n_elem = alloc.allocate(x.sz);
							for (size_type i = 0; i < x.sz; i++)
								alloc.construct(&n_elem[i], x.elem[i]);
							alloc.deallocate(elem, space);
							elem = n_elem;
							space = sz = x.sz;
						}
						else 
						{
							for (size_type i = 0; i < x.sz; i++)
								elem[i] = x.elem[i];
							sz = x.sz;
						}
						alloc = x.alloc;
					}
					return *this;
				}


				///////////////////
				//               //
				// GET_ALLOCATOR //
				//               //
				///////////////////


				////////////////////
				//                //
				// ELEMENT ACCESS //
				//                //
				////////////////////

				reference at(size_type pos)
				{
					if (!(pos < size()))
						throw std::out_of_range(" at position out of range");
					return elem[pos];
				}

				const_reference at(size_type pos) const
				{
					if (!(pos < size()))
						throw std::out_of_range(" at position out of range");
					return elem[pos];
				}

				reference operator[](size_type n) { return elem[n]; }
				const_reference operator[](size_type n) const { return elem[n]; }

				reference front() { return (*begin()); }
				const_reference front() const { return *begin(); }

				reference back() { return *(end() -1); }
				const_reference back() const { return *(end() -1); }


				///////////////
				//           //
				// ITERATORS //
				//           //
				///////////////

				iterator begin() { return elem; }
				const_iterator begin() const { return elem; }
				iterator end() { return (elem + sz); }
				const_iterator end() const { return (elem + sz); }

				reverse_iterator rbegin() { return(reverse_iterator(end())); }
				const_reverse_iterator rbegin() const { return(reverse_iterator(end())); }
				reverse_iterator rend() { return(reverse_iterator(begin())); }
				const_reverse_iterator rend() const { reverse_iterator(begin()); }

				///////////////
				//           //
				// CAPACITY  //
				//           //
				///////////////

				bool empty() const { return begin() == end(); }

				size_type size() const { return sz; }

				size_type max_size() const {
					return alloc.max_size();
				}

				void reserve(size_type n)
				{
					if (n <= space) return;
					pointer reserve = alloc.allocate(n);
					for (size_type i = 0; i<sz; ++i)
						alloc.construct(&reserve[i], elem[i]);
					alloc.deallocate(elem, sz);
					elem = reserve;
					space = n;
				}

				size_type capacity() const { return space; }

				void resize (size_type n, value_type val = value_type())
				{
					if (n < size())
					{
						for (size_type to_pop = size() - n; to_pop > 0; to_pop--)
							pop_back();
					}
					else if (n > size())
					{
						for (size_type to_add = n - size(); to_add > 0; to_add--)
							push_back(val);
					}

				}


				///////////////
				//           //
				// MODIFIERS //
				//           //
				///////////////
				//p746;

				void assign( size_type count, const T& value )
				{
					clear();
					for (size_type st = 0; st < count; st++)
						push_back(value);
				}

				template <class InputIt>
					void assign( InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last )
					{
						clear();
						for (InputIt it = first; it != last; it++)
							push_back(*it);
					}

				void pop_back( void )
				{
					if (begin() != end())
					{
						alloc.destroy(end() - 1);
						sz--;
					}
				}

				void	clear( void )
				{
					for (iterator it = begin(); it != end(); it++)
						alloc.destroy(it);
					sz = 0;
				}

				iterator insert(iterator position, const_reference x = T())
				{
					difference_type dist = std::distance(begin(), position);
					if (dist == 0)
					{
						push_back(x);
						return (begin());
					}
					push_back(back());
					iterator it = end() - 1;
					while (dist != std::distance(begin(), it))
					{
						*it = *(it - 1);
						it--;
					}
					*it = x;
					sz++;
					return (it);
				}

				void insert( iterator pos, size_type count, const T& value )
				{
					iterator new_pos = pos;
					for (size_type st = 0; st < count; st++)
						new_pos = insert(new_pos,value);
				}

				template <class InputIterator>
					void insert(iterator position, InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
					{
						iterator new_pos = position;
						for(InputIterator it = first; it != last; it++)
							new_pos = insert(new_pos, *it);
					}

				iterator erase(iterator p)
				{
					if (p==end()) return(p);
					for (iterator pos = p + 1; pos!=end(); ++pos)
					{
						alloc.destroy(pos-1);
						alloc.construct(pos - 1,*pos);
					}
					--sz;
					return(p);
				}

				iterator erase(iterator first, iterator last)
				{
					size_type dist = std::distance(first, last);
					iterator ret = first;;
					for (; dist; dist--)
						ret = erase(ret);
					return(ret);
				}


				void push_back(const T& x)
				{
					if (space == 0)
						reserve(1);
					else if (sz==space)
						reserve(2*space);
					alloc.construct(&elem[sz], x);
					++sz;
				}

				void swap(vector<T, Allocator>& x);



			private:
				pointer			elem;
				size_type		sz;
				size_type		space;
				allocator_type	alloc;
		};
	//template <class T, class Allocator>
	//bool operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
	//template <class T, class Allocator>
	//bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
}
#endif