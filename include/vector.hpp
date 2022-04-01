/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:11:44 by csejault          #+#    #+#             */
/*   Updated: 2022/04/01 17:18:18 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
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

				typedef T										value_type;
				typedef Allocator								allocator_type;
				typedef	typename std::size_t					size_type;
				typedef typename std::ptrdiff_t					difference_type;
				typedef value_type&								reference;
				typedef const value_type&						const_reference;
				typedef typename Allocator::pointer				pointer;
				typedef typename Allocator::const_pointer		const_pointer;
				typedef value_type*								iterator;
				typedef const value_type*						const_iterator;
				typedef	ft::reverse_iterator<iterator>			reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


				/////////////////
				//             //
				// CONSTRUCTOR //
				//             //
				/////////////////

				template <class InputIterator>
					vector(InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc_arg = allocator_type()) : elem(NULL), sz(0), space(0), alloc(alloc_arg)
				{
					assign(first, last);
				}

				explicit vector(const allocator_type& alloc_arg = allocator_type()) : elem(NULL), sz(0), space(0), alloc(alloc_arg) 
			{
				elem = alloc.allocate(0);
			}

				explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& allocator_arg = allocator_type()) : elem(NULL), sz(), space(0), alloc(allocator_arg)
			{
				assign(n, value);
			}

				vector(const vector& x) : elem(NULL), sz(0), space(0), alloc(x.alloc)
			{
				assign(x.begin(), x.end());
			}


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
					if (&x != this )
					{
						alloc = x.alloc;
						assign(x.begin(), x.end());
					}
					return (*this);
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
				iterator end() { return (elem + sz);}
				const_iterator end() const { return (elem + sz); }
				reverse_iterator rbegin() { return(reverse_iterator(end())); }
				const_reverse_iterator rbegin() const { return(const_reverse_iterator(end())); }
				reverse_iterator rend() { return(reverse_iterator(begin())); }
				const_reverse_iterator rend() const { const_reverse_iterator(begin()); }

				///////////////
				//           //
				// CAPACITY  //
				//           //
				///////////////

				bool empty() const { return begin() == end(); }
				size_type size() const { return sz; }
				size_type max_size() const {return alloc.max_size();}

				void reserve(size_type n)
				{
					if (n > max_size())
						throw std::length_error("vector::reserve");
					if (n <= space) return;
					pointer reserve = alloc.allocate(n);
					if (elem)
					{
						for (size_type i = 0; i<sz; ++i)
						{
							alloc.construct(&reserve[i], elem[i]);
							alloc.destroy(&elem[i]);
						}
						alloc.deallocate(elem, sz);
					}
					elem = reserve;
					space = n;
				}

				size_type capacity() const { return space; }

				void resize (size_type n, value_type val = value_type())
				{
					if (n > size())
						insert(end(), n - size(), val);
					else if (n < size())
						erase(&elem[n], end());
				}

				///////////////
				//           //
				// MODIFIERS //
				//           //
				///////////////

				template <class InputIterator>
					void assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
						size_type size = std::distance(first, last);
						clear();
						if (elem)
							alloc.deallocate(elem,space);
						elem = alloc.allocate(space);
						insert (begin(),first, last);
					}

				void assign (size_type n, const value_type& val) {
					clear();
					if (elem)
						alloc.deallocate(elem,space);
					elem = alloc.allocate(space);
					insert(begin(),n,val);
				}

				void pop_back( void )
				{
					if (begin() != end())
						erase(end() -1);
				}

				void	clear( void )
				{
					if (elem)
						erase(begin(), end());
				}

				iterator insert(iterator position, const_reference x = T())
				{
					size_type dist = 0;
					if (begin() || begin() != position)
						dist = std::distance(begin(), position);

					reserve(_find_new_cap(1));
					if (sz)
						for (size_type st = sz; st > dist; st--)
						{
							alloc.construct(&elem[st], elem[st -1]);
							alloc.destroy(&elem[st -1]);
						}
					alloc.construct(&elem[dist], x);
					sz++;
					return (&elem[dist]);
				}

				void insert( iterator pos, size_type count, const T& value )
				{
					if (count == 0)
						return;
					size_type dist_pos = 0;
					if (begin() || begin() != pos)
						dist_pos = std::distance(begin(), pos);
					size_type old_sz = sz;
					reserve(_find_new_cap(count));
					sz += count;
					if (sz - count)
						for (size_type elempos = sz - 1; elempos >= dist_pos + count; elempos--)
						{
							if (elempos < old_sz)
								alloc.destroy(&elem[elempos]);
							alloc.construct(&elem[elempos], elem[elempos - count]);
						}
					for (size_type itpos = 0; itpos < count; itpos++)
					{
						if (dist_pos + itpos < old_sz)
							alloc.destroy(&elem[dist_pos + itpos]);
						alloc.construct(&elem[dist_pos + itpos], value);
					}
				}

				template <class InputIterator>
					void insert(iterator position, InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
					{
						size_type dist_f_l = std::distance(first, last);
						if (!dist_f_l) return;
						size_type dist_pos = 0;
						if (begin() || begin() != position)
							dist_pos = std::distance(begin(), position);
						size_type old_sz = sz;

						reserve(_find_new_cap(dist_f_l));

						sz += dist_f_l;
						if (sz - dist_f_l)
							for (size_type elempos = sz - 1; elempos >= dist_pos + dist_f_l; elempos--)
							{
								if (elempos < old_sz)
									alloc.destroy(&elem[elempos]);
								alloc.construct(&elem[elempos], elem[elempos - dist_f_l]);
							}
						for (size_type itpos = 0; itpos < dist_f_l; itpos++)
						{
							if (dist_pos + itpos < old_sz)
								alloc.destroy(&elem[dist_pos + itpos]);
							alloc.construct(&elem[dist_pos + itpos], *first);
							first++;
						}
					}

				iterator erase(iterator p)
				{
					if (p==end()) return(p);
					for (iterator it = p; it != end(); it++)
					{
						alloc.destroy(it);
						if (it + 1 != end())
							alloc.construct(it, *(it + 1));
					}
					--sz;
					return(p);
				}

				iterator erase(iterator first, iterator last)
				{
					size_type dist = std::distance(first, last);
					iterator ret = first;
					for (; dist; dist--)
						ret = erase(ret);
					return(ret);
				}

				void push_back(const T& x) {insert(end(), x);}

				void swap(vector<T, Allocator>& x)
				{
					size_type tmp_sz = sz;
					size_type tmp_space = space;
					pointer tmp_elem = elem;
					sz = x.sz;
					space = x.space;
					elem = x.elem;
					x.sz = tmp_sz;
					x.space =tmp_space;
					x.elem = tmp_elem;
				}

			private:
				pointer			elem;
				size_type		sz;
				size_type		space;
				allocator_type	alloc;

				size_type    _find_new_cap(size_type n)
				{
					if ((size() + n) <= capacity())
						return (this->capacity());
					size_type len = size() + std::max(size(), n);
					return ((len < size() || len > max_size()) ? max_size() : len);
				}
		};

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {x.swap(y);}

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			if (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) &&
					!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()))
				return (true);
			return false;
		}

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(lhs == rhs));}

	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(lhs > rhs));}

	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (rhs < lhs);}

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(lhs < rhs));}

}
#endif
