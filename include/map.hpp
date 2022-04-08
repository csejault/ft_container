/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:38:59 by csejault          #+#    #+#             */
/*   Updated: 2022/04/08 16:55:19 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
//# include ".rbt/rbt.hpp"
#include <functional> 
#include "type_traits.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include "rbt/rbt.hpp"

namespace ft
{
	template < class Key,                                   	// map::key_type
			 class T,                                       	// map::mapped_type
			 class Compare = std::less<Key>,                	// map::key_compare
			 class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
				 > class map
				 {
					 public:

						 /////////////
						 //         //
						 // TYPEDEF //
						 //         //
						 /////////////

						 typedef Key											key_type;
						 typedef T												mapped_type;
						 typedef ft::pair<const key_type, mapped_type>			value_type;
						 typedef Compare										key_compare;
						 typedef Alloc											allocator_type;
						 typedef typename allocator_type::reference				reference;
						 typedef typename allocator_type::const_reference		const_reference;
						 typedef typename allocator_type::pointer				pointer;
						 typedef typename allocator_type::const_pointer			const_pointer;
						 typedef size_t											size_type;

						 //https://www.cplusplus.com/reference/map/map/value_comp/
						 //class map<key_type,value_type,key_compare,allocator_type>::value_compare
						 class value_compare
						 {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
							 friend class map<key_type, value_type, key_compare, allocator_type>;
							 protected:
							 key_compare comp;
							 value_compare (key_compare c) : comp(c) {}  // constructed with map's comparison object
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
						 //typedef rbt<value_type,typename allocator_type::template rebind< typename rbt < value_type > ::node_type >::other, value_compare>	tree_type;
						 typedef rbt<value_type, allocator_type, value_compare>	tree_type;
						 //typedef rbt<value_type>	tree_type;

					 public:
						 typedef typename tree_type::iterator								iterator;
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
						 key_compare						_compare;
						 allocator_type						_alloc;
						 tree_type*							_tree;
					typename allocator_type::template rebind<typename map<key_type, mapped_type,key_compare, allocator_type>::tree_type>::other _tree_allocator;

						 void _alloc_tree(tree_type new_tree)
						 {
							 _tree = _tree_allocator.allocate(1);
							 _tree_allocator.construct(_tree, new_tree);
						 }

						 void _deallocate_tree( void )
						 {
							 _tree_allocator.deallocate(_tree, 1);
							 _tree = NULL;
						 }

					 public:


						 /////////////////
						 //             //
						 // CONSTRUCTOR //
						 //             //
						 /////////////////

						 explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type()) : _compare(comp), _alloc(alloc_arg)
					 {
							 _alloc_tree(tree_type());
					 }

						 template <class InputIterator>
							 map (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type()) : _compare(comp), _alloc(alloc_arg)
						 {
							 _alloc_tree(tree_type());
							 while(first != last)
							 {
								 _tree->insert_node(*first);
								 first++;
							 }
						 }

						 map(const map& x) : _alloc(x._alloc),  _tree(NULL)
						 {
							 _alloc_tree(tree_type());
							 *this = x;
						 }

						 ~map( void )
						 {
								 if (_tree)
								 	_deallocate_tree();
						 }


						 //////////////
						 //          //
						 // OPERATOR //
						 //          //
						 //////////////

						 map& operator=(const map& x)
						 {
							 if (this != &x)
							 {
								 if (_tree)
								 	_deallocate_tree();
								 _compare = x._compare;
								 _alloc = x._alloc;
								 _alloc_tree(*x._tree);
							 }
							 return (*this);
						 }

						 mapped_type& operator[] (const key_type& k)
						 {
							 (void)k;
						 }


						 //////////////
						 //          //
						 // ITERATOR //
						 //          //
						 //////////////

						 iterator begin()
						 {
							 return (iterator(_tree->minimum()));
						 }

						 const_iterator begin() const
						 {
							 return (const_iterator(_tree->minimum()));
						 }

						 iterator end()
						 {
							 return(iterator(_tree->get_t_null()));
						 }

						 const_iterator end() const
						 {
							 return(const_iterator(_tree->get_t_null()));
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
							 iterator it = iterator(_tree->insert_node(val));
							 return (ft::make_pair<iterator, bool>(it, true));
						 }

						 iterator insert (iterator position, const value_type& val)
						 {
							 (void)val;
							 (void)position;
						 }

						 template <class InputIterator>
							 void insert (InputIterator first, InputIterator last)
							 {
								 (void)first;
								 (void)last;
							 }

						 void erase (iterator position)
						 {
							 (void)position;
						 }

						 size_type erase (const key_type& k)
						 {
							 (void)k;
						 }

						 void erase (iterator first, iterator last)
						 {
							 (void)first;
							 (void)last;
						 }

						 void swap (map& x)
						 {
							 (void)x;
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
							 (void)k;
						 }

						 const_iterator find (const key_type& k) const
						 {
							 (void)k;
						 }

						 size_type count (const key_type& k) const
						 {
							 (void)k;
						 }

						 iterator lower_bound (const key_type& k)
						 {
							 (void)k;
						 }

						 const_iterator lower_bound (const key_type& k) const
						 {
							 (void)k;
						 }

						 iterator upper_bound (const key_type& k)
						 {
							 (void)k;
						 }

						 const_iterator upper_bound (const key_type& k) const
						 {
							 (void)k;
						 }

						 ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
						 {
							 (void)k;
						 }

						 ft::pair<iterator,iterator>             equal_range (const key_type& k)
						 {
							 (void)k;
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

}
#endif
