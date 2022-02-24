/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:59:58 by csejault          #+#    #+#             */
/*   Updated: 2022/02/23 18:48:43 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

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
				//typedef reverse_iterator;
				//typedef const_reverse_iterator;


				/////////////////
				//             //
				// CONSTRUCTOR //
				//             //
				/////////////////

				explicit vector(const allocator_type& alloc_arg = allocator_type()) : elem(NULL), sz(0), space(0), alloc(alloc_arg) { }

				explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& allocator_arg = allocator_type()) : elem(NULL), sz(n), space(n), alloc(allocator_arg)
			{
				elem = alloc.allocate(n);
				for (size_type i = 0 ; i < n; i++)
					alloc.construct(&elem[i], value);
			}

				vector(const vector& x) : elem(NULL), sz(0), space(0) { *this = x; }

				//enable if and is !integral
				//				template <class InputIteratohh>
				//					vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

				~vector()
				{
					if (elem)
						alloc.deallocate(elem, space);
				}

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

				const_reference at(int pos) const
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
				//reverse_iterator rbegin();
				//const_reverse_iterator rbegin();
				//reverse_iterator rend();
				//const_reverse_iterator rend();

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


				///////////////
				//           //
				// MODIFIERS //
				//           //
				///////////////

				//p746;

				void	clear( void )
				{
					for (iterator it = begin(); it != end(); it++)
						alloc.destroy(it);
					sz = 0;
				}

				iterator insert(iterator position, const_reference x = T())
				{
					if (!position)
						return (NULL);
					else if (sz==space)
						reserve(2*space);

					(void)x;
					(void)position;
					alloc.construct(elem + sz, back());
					iterator it = end();
					it--;
					while (std::distance(begin(), position) != std::distance(begin(), it))
					{
						std::cout << std::distance(begin(), position) << " - ";
						std::cout << std::distance(begin(), it) << std::endl; 
					std::cout << it - position  << " fsdf" << std::endl;
					it--;
					}
					//	*it = *(it -1);
					//*it = x;
					sz++;
					return (it);
				}

				//void insert(iterator position, size_type n, const T& x);
				//template <class InputIterator>
				//	void insert(iterator position, InputIterator first, InputIterator last);
				//void pop_back();
				void erase(iterator p)
				{
					if (p==end()) return p;
					for (iterator pos = p + 1; pos!=end(); ++pos)
						*(pos-1) = *pos; 
					--sz;
					return p;
				}
				//void erase(iterator first, iterator last);
				void push_back(const T& x)
				{
					if (space == 0)
						reserve(1);
					else if (sz==space)
						reserve(2*space);
					elem[sz] = x;
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
