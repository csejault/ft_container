/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:38:59 by csejault          #+#    #+#             */
/*   Updated: 2022/04/05 18:26:41 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
//# include ".rbt/rbt.hpp"
#include <functional> 
#include "pair.hpp"

template < class Key,                                   	// map::key_type
		 class T,                                       	// map::mapped_type
		 class Compare = std::less<Key>,                	// map::key_compare
		 class Alloc = allocator<ft::pair<const Key,T> >    // map::allocator_type
		 > class map
{
	public:

		/////////////
		//         //
		// TYPEDEF //
		//         //
		/////////////

		typedef key												key_type;
		typedef T												mapped_type;
		typedef ft::pair<const key_type, mapped_type>			value_type;
		typedef	Compare											key_compare;
		typedef Alloc											allocatore_type;
		typedef allocator_type::reference						reference;
		typedef allocator_type::const_reference					const_reference;
		typedef allocator_type::pointer							pointer;
		typedef allocator_type::const_pointer					const_pointer;
		typedef size_t											size_type;

		//https://www.cplusplus.com/reference/map/map/value_comp/
		template <class Key, class T, class Compare, class Alloc>
			class map<Key,T,Compare,Alloc>::value_compare
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map;
				protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
			};

	private:
		typedef rbt<value_type, allocator_type, value_compare>	tree_type;

	public:
		typedef tree_type::iterator								iterator;
		typedef	tree_type::const_iterator						const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef ft::iterator_traits<iterator>::difference_type	difference_type;

		/////////////
		//         //
		// OBJECTS //
		//         //
		/////////////

	private:
		allocator_type	_alloc;
		//compare_type	_compare;
		tree_type		_tree_null;
		tree_type		_tree;

	public:


		/////////////////
		//             //
		// CONSTRUCTOR //
		//             //
		/////////////////

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type())
		{
		}

		template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type())
			{
			}

		map(const map& x)
		{

		}

		~map( void )
		{
		}


		//////////////
		//          //
		// OPERATOR //
		//          //
		//////////////

		map& operator=(const map& x)
		{
		}

		mapped_type& operator[] (const key_type& k)
		{
		}


		//////////////
		//          //
		// ITERATOR //
		//          //
		//////////////

		iterator begin()
		{
			return (iterator(tree->minimum());
		}

		const_iterator begin() const
		{
			return (const_iterator(tree->minimum());
		}

		iterator end()
		{
			return(iterator(tree->get_t_null());
		}

		const_iterator end() const
		{
			return(const_iterator(tree->get_t_null());
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin());
		}


		//////////////
		//          //
		// CAPACITY //
		//          //
		//////////////

		bool empty() const
		{
			return (size() == 0);
		}

		size_type size() const
		{
			return (_tree->size());
		}

		size_type max_size() const
		{
		}


		///////////////
		//           //
		// MODIFIERS //
		//           //
		///////////////

		pair<iterator,bool> insert (const value_type& val)
		{
		}

		iterator insert (iterator position, const value_type& val)
		{
		}

		template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
			}

		void erase (iterator position)
		{
		}

		size_type erase (const key_type& k)
		{
		}

		void erase (iterator first, iterator last)
		{
		}

		void swap (map& x)
		{
		}

		void clear()
		{
		}


		///////////////
		//           //
		// OBSERVERS //
		//           //
		///////////////

		key_compare key_comp() const
		{
		}

		value_compare value_comp() const
		{
		}


		////////////////
		//            //
		// OPERATIONS //
		//            //
		////////////////

		iterator find (const key_type& k)
		{
		}

		const_iterator find (const key_type& k) const
		{
		}

		size_type count (const key_type& k) const
		{
		}

		iterator lower_bound (const key_type& k)
		{
		}

		const_iterator lower_bound (const key_type& k) const
		{
		}

		iterator upper_bound (const key_type& k)
		{
		}

		const_iterator upper_bound (const key_type& k) const
		{
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
		}

		pair<iterator,iterator>             equal_range (const key_type& k)
		{
		}


		///////////////
		//           //
		// ALLOCATOR //
		//           //
		///////////////

		allocator_type get_allocator() const
		{
		}



};

#endif
