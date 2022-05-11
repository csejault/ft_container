/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:38:59 by csejault          #+#    #+#             */
/*   Updated: 2022/05/11 15:59:29 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SET_HPP
# define SET_HPP
#include <functional> 
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "utils.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include "rbt.hpp"

namespace ft
{
	template < class Key,                                   	// set::key_type
			 class Compare = std::less<Key>,                	// set::key_compare
			 class Alloc = std::allocator<Key>    // set::allocator_type
				 > class set
				 {
					 public:

						 /////////////
						 //         //
						 // TYPEDEF //
						 //         //
						 /////////////

						 typedef Key											key_type;
						 typedef Key											value_type;
						 typedef Compare										key_compare;
						 typedef Compare										value_compare;
						 typedef Alloc											allocator_type;
						 typedef typename allocator_type::reference				reference;
						 typedef typename allocator_type::const_reference		const_reference;
						 typedef typename allocator_type::pointer				pointer;
						 typedef typename allocator_type::const_pointer			const_pointer;
						 typedef size_t											size_type;

					 private:
						 typedef rbt<value_type,typename allocator_type::template rebind< typename rbt < value_type, allocator_type, value_compare > ::node_type >::other, value_compare>	tree_type;
						 typedef typename allocator_type::template rebind<typename set<key_type,key_compare, allocator_type>::tree_type>::other allocator_type_tree;
						 typedef	typename tree_type::node_type				node_type;
						 typedef	typename tree_type::node_pointer				node_pointer;

					 public:
						 typedef typename tree_type::const_iterator								iterator;
						 typedef typename tree_type::const_iterator							const_iterator;
						 typedef ft::reverse_iterator<iterator>								reverse_iterator;
						 typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
						 typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;

						 /////////////
						 //         //
						 // OBJECTS //
						 //         //
						 /////////////

					 private:
						 key_compare						_key_compare;
						 value_compare						_value_compare;
						 allocator_type						_alloc;
						 allocator_type_tree				_tree_allocator;
						 node_pointer						_t_null;
						 tree_type*							_tree;

						 tree_type*& _alloc_tree(tree_type new_tree)
						 {
							 _tree = _tree_allocator.allocate(1);
							 _tree_allocator.construct(_tree, new_tree);
							 _t_null = _tree->get_t_null();
							 return ( _tree );
						 }

						 void _deallocate_tree( void )
						 {
							 _tree_allocator.destroy(_tree);
							 _tree_allocator.deallocate(_tree, 1);
							 _tree = NULL;
							 _t_null = NULL;
						 }


					 public:

						 /////////////////
						 //             //
						 // CONSTRUCTOR //
						 //             //
						 /////////////////

						 explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc_arg), _tree_allocator(allocator_type_tree()),  _t_null(NULL), _tree(_alloc_tree(tree_type(_tree_allocator,_value_compare))) { }

						 template <class InputIterator>
							 set (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc_arg), _tree_allocator(allocator_type_tree()), _t_null(NULL), _tree(_alloc_tree(tree_type(_tree_allocator,_value_compare)))
						 {
							 insert(first,last);
						 }

						 set(const set& x) : _key_compare(x._key_compare), _value_compare(x._key_compare), _alloc(x._alloc), _tree_allocator(x._tree_allocator),  _t_null(NULL), _tree(_alloc_tree(*x._tree)) { }

						 ~set( void )
						 {
							 if (_tree)
								 _deallocate_tree();
						 }


						 //////////////
						 //          //
						 // OPERATOR //
						 //          //
						 //////////////

						 set& operator=(const set& x)
						 {
							 if (this != &x)
							 {
								 if (_tree)
									 _deallocate_tree();
								 _key_compare = x._key_compare;
								 _value_compare = x._value_compare;
								 _alloc = x._alloc;
								 _tree_allocator = x._tree_allocator;
								 _alloc_tree(*x._tree);
							 }
							 return (*this);
						 }

						 //////////////
						 //          //
						 // ITERATOR //
						 //          //
						 //////////////

						 iterator begin()
						 {
							 return(iterator(_tree->minimum(), _tree->get_t_null(), _tree->get_root()));
						 }

						 const_iterator begin() const
						 {
							 return(const_iterator(_tree->minimum(), _tree->get_t_null(), _tree->get_root()));
						 }

						 iterator end()
						 {
							 return(iterator(_tree->get_t_null(), _tree->get_t_null(), _tree->get_root()));
						 }

						 const_iterator end() const
						 {
							 return(const_iterator(_tree->get_t_null(), _tree->get_t_null(), _tree->get_root()));
						 }

						 reverse_iterator rbegin()
						 {
							 return (reverse_iterator(end()));
						 }

						 const_reverse_iterator rbegin() const
						 {
							 return (const_reverse_iterator(end()));
						 }

						 reverse_iterator rend()
						 {
							 return (reverse_iterator(begin()));
						 }

						 const_reverse_iterator rend() const
						 {
							 return (const_reverse_iterator(begin()));
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
							 return (_alloc.max_size());
						 }


						 ///////////////
						 //           //
						 // MODIFIERS //
						 //           //
						 ///////////////


						 ft::pair<iterator,bool> insert (const value_type& val)
						 {
							 node_pointer& to_find = _tree->search(val);
							 if (to_find == _t_null)
								 return (ft::make_pair<iterator, bool>(iterator(_tree->insert_node(val), _tree->get_t_null(), _tree->get_root()), true));
							 else
								 return (ft::make_pair<iterator, bool>(iterator(to_find, _tree->get_t_null(), _tree->get_root()), false));
						 }

						 iterator insert (iterator position, const value_type& val)
						 {
							 (void)position;
							 return(insert(val).first);
						 }

						 template <class InputIterator>
							 void insert (InputIterator first, InputIterator last)
							 {
								 for (;first != last; first++)
									 insert(*first);
							 }

						 void erase (iterator position)
						 {
							 _tree->delete_node(*position);
						 }

						 size_type erase (const key_type& k)
						 {
							 iterator to_del = find(k);
							 if (to_del == end())
								 return (0);
							 else
								 erase(to_del);
							 return(1);
						 }

						 void erase (iterator first, iterator last)
						 {
							 iterator tmp;
							 while (first != last)
							 {
								 tmp = first++;
								 erase(tmp);
							 }
						 }

						 void swap (set& x)
						 {
							 ft::swap(_key_compare, x._key_compare);
							 ft::swap(_value_compare, x._value_compare);
							 ft::swap(_alloc, x._alloc);
							 ft::swap(_tree_allocator, x._tree_allocator);
							 ft::swap(_t_null, x._t_null);
							 ft::swap(_tree, x._tree);
						 }

						 void clear()
						 {
							 _tree->delete_tree(_tree->get_root());
						 }


						 ///////////////
						 //           //
						 // OBSERVERS //
						 //           //
						 ///////////////

						 key_compare key_comp() const
						 {
							 return (_key_compare);
						 }

						 value_compare value_comp() const
						 {
							 return(_value_compare);
						 }


						 ////////////////
						 //            //
						 // OPERATIONS //
						 //            //
						 ////////////////

						 iterator find (const key_type& k)
						 {
							 value_type p_to_find = k;
							 node_pointer to_find = _tree->search(p_to_find);
							 return (iterator(to_find, _tree->get_t_null(), _tree->get_root()));
						 }

						 const_iterator find (const key_type& k) const
						 {
							 value_type p_to_find = k;
							 node_pointer to_find = _tree->search(p_to_find);
							 return (const_iterator(to_find, _tree->get_t_null(), _tree->get_root()));
						 }

						 size_type count (const key_type& k) const
						 {
							 if (find(k) != end())
								 return (1);
							 else
								 return (0);
						 }

						 iterator lower_bound (const key_type& k)
						 {
							 return(_tree->lower_bound(k));
						 }

						 const_iterator lower_bound (const key_type& k) const
						 {
							 return(_tree->lower_bound(k));
						 }

						 iterator upper_bound (const key_type& k)
						 {
							 return(_tree->upper_bound(k));
						 }

						 const_iterator upper_bound (const key_type& k) const
						 {
							 return(_tree->upper_bound(k));
						 }

						 ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
						 {
							 return(_tree->equal_range(k));
						 }

						 ft::pair<iterator,iterator>     equal_range (const key_type& k)
						 {
							 return(_tree->equal_range(k));
						 }


						 ///////////////
						 //           //
						 // ALLOCATOR //
						 //           //
						 ///////////////

						 allocator_type get_allocator() const
						 {
							 return (_alloc);
						 }

				 };
	template< class Key, class Compare, class Alloc >
		void swap( ft::set<Key,Compare,Alloc>& lhs,
				ft::set<Key,Compare,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}

	template< class Key,  class Compare, class Alloc >
		bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs )
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(),lhs.end(),rhs.begin()));
		}

	template< class Key, class Compare, class Alloc >
		bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}

	template< class Key, class Compare, class Alloc >
		bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template< class Key, class Compare, class Alloc >
		bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs )
		{
			return (!(rhs < lhs));
		}

	template< class Key, class Compare, class Alloc >
		bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs )
		{
			return (rhs < lhs);
		}
	template< class Key, class Compare, class Alloc >
		bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs )
		{
			return (!(rhs > lhs));
		}

}
#endif
