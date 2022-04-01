
//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
// /* ************************************************************************** */ //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:59:58 by csejault          #+#    #+#             */
/*   Updated: 2022/03/15 17:59:36 by csejault         ###   ########.fr       */
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
					sz = std::distance(first,last);
					reserve(sz);
					for (size_type i = 0 ; i < sz; i++)
					{
						alloc.construct(&elem[i], *first);
						first++;
					}
				}

				explicit vector(const allocator_type& alloc_arg = allocator_type()) : elem(NULL), sz(0), space(0), alloc(alloc_arg) 
			{
				//alloc.allocate(elem, 0);
			}

				explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& allocator_arg = allocator_type()) : elem(NULL), sz(n), space(0), alloc(allocator_arg)
			{
				reserve(_find_new_cap(sz));

				for (size_type i = 0; i < sz; i++)
					alloc.construct(&elem[i], value);
			}

				vector(const vector& x) : elem(NULL), sz(x.size()), space(0), alloc(x.alloc) //{ *this = x; }
			{
				*this = x;
			}


			////////////////
			//            //
			// DESTRUCTOR //
			//            //
			////////////////

			~vector()
			{
				if (elem)
				{
					clear();
					alloc.deallocate(elem, space);
				}
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
					clear();
					alloc.deallocate(elem, space);
					alloc = x.alloc;
					space = x.capacity();
					sz = x.size();
					elem = alloc.allocate(space);
					for (size_type i = 0; i < sz; i++)
						alloc.construct(&elem[i], x[i]);
				}
				//if (&x != this )
				//{
				//	if (x.sz > space)
				//	{
				//		pointer n_elem = alloc.allocate(x.sz);
				//		for (size_type i = 0; i < x.sz; i++)
				//			alloc.construct(&n_elem[i], x.elem[i]);
				//		alloc.deallocate(elem, space);
				//		elem = n_elem;
				//		space = sz = x.sz;
				//	}
				//	else 
				//	{
				//		for (size_type i = 0; i < x.sz; i++)
				//			elem[i] = x.elem[i];
				//		sz = x.sz;
				//	}
				//	alloc = x.alloc;
				//}
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

			size_type max_size() const {
				return alloc.max_size();
			}

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n <= space && space) return;
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

			//void reserve (size_type n) {
			//	if (n > this->max_size())
			//		throw std::length_error("vector::reserve");
			//	else if (n > space)
			//	{
			//		vector	tmp = *this;
			//		clear();
			//		alloc.deallocate(elem,space);
			//		space = n;
			//		elem = alloc.allocate(space);
			//		sz = tmp.size();
			//		for (size_type i = 0; i < sz; i++)
			//			alloc.construct(&elem[i], tmp[i]);
			//	}
			//}


			size_type capacity() const { return space; }

			void resize (size_type n, value_type val = value_type())
			{
				if (n < size())
				{
					//						for (size_type to_pop = size() - n; to_pop > 0; to_pop--)
					//							pop_back();
					for (size_type i = n; i < sz; i++)
						alloc.destroy(&elem[i]);
					sz = n;

				}
				else if (n > sz && n > space)
				{
					reserve(n > 2 * sz ? n : 2 * sz);
					for (size_type i = sz; i < n; i++)
						alloc.construct(&elem[i], val);
					sz = n;
				}
				else if (n > size())
				{
					for (size_type i = sz; i < n; i++)
						alloc.construct(&elem[i], val);
					sz = n;
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
				reserve(count);
				insert(begin(),count, value);
			}

			template <class InputIt>
				void assign( InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last )
				{
					clear();
					reserve(std::distance(first, last));
					insert(begin(),first, last);
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
				if (elem)
					erase(begin(), end());
				sz = 0;
			}

			iterator insert(iterator position, const_reference x = T())
			{
				size_type	dist = std::distance(begin(), position);


				reserve(_find_new_cap(1));

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
				size_type dist_pos = std::distance(begin(), pos);
				size_type old_sz = sz;
				reserve(_find_new_cap(count));

				sz += count;
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
					size_type dist_pos = std::distance(begin(), position);
					size_type dist_f_l = std::distance(first, last);
					size_type old_sz = sz;

					reserve(_find_new_cap(dist_f_l));

					sz += dist_f_l;
					for (size_type elempos = sz - 1; elempos >= dist_pos + dist_f_l; elempos--)
					{
						if (elempos < old_sz)
						{
							alloc.destroy(&elem[elempos]);
						}
						alloc.construct(&elem[elempos], elem[elempos - dist_f_l]);
					}

					for (size_type itpos = 0; itpos < dist_f_l; itpos++)
					{
						if (dist_pos + itpos < old_sz)
							alloc.destroy(&elem[dist_pos + itpos]);
						alloc.construct(&elem[dist_pos + itpos], *first);
						first++;
					}

					//iterator new_pos = begin() + dist_pos;
					//for (iterator it = end(); it != new_pos; it--)
					//{
					//	if (old_sz + dist_f_l <= sz)
					//		alloc.destroy(it);
					//	else
					//		sz++;
					//	alloc.construct(it, *(it - dist_f_l));
					//}

					//for (size_type to_insert = dist_f_l; to_insert > 0; to_insert--)
					//{
					//	alloc.destroy(new_pos + to_insert);
					//	alloc.construct(new_pos + to_insert, *(first + to_insert));
					//}
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
				iterator ret = first;
				for (; dist; dist--)
					ret = erase(ret);
				return(ret);
			}


			void push_back(const T& x)
			{
				insert(end(), x);
				//reserve(_find_new_cap(1));
				//alloc.construct(&elem[sz], x);
				//++sz;
			}

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
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}

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
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs > rhs));
		}


	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}

}
#endif
