/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:38:59 by csejault          #+#    #+#             */
/*   Updated: 2022/04/14 12:35:43 by csejault         ###   ########.fr       */
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
						 //typedef ft::pair<const key_type, mapped_type>			value_type;
						 typedef Compare										key_compare;
						 typedef Alloc											allocator_type;
						 typedef typename allocator_type::reference				reference;
						 typedef typename allocator_type::const_reference		const_reference;
						 typedef typename allocator_type::pointer				pointer;
						 typedef typename allocator_type::const_pointer			const_pointer;
						 typedef size_t											size_type;

						 //https://www.cplusplus.com/reference/map/map/value_comp/
						 class value_compare : public std::binary_function<value_type, value_type, bool>
					 {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
						 private:
							 friend class map;
						 protected:
							 key_compare comp;
							 value_compare (key_compare c) : comp(c) {}  // constructed with map's comparison object
						 public:
							 typedef bool result_type;
							 typedef value_type first_argument_type;
							 typedef value_type second_argument_type;
							 result_type	operator() (const first_argument_type& x, const second_argument_type& y) const
							 {
								 return comp(x.first, y.first);
							 }
					 };

					 private:
						 typedef rbt<value_type,typename allocator_type::template rebind< typename rbt < value_type, allocator_type, value_compare > ::node_type >::other, value_compare>	tree_type;
						 typedef typename allocator_type::template rebind<typename map<key_type, mapped_type,key_compare, allocator_type>::tree_type>::other allocator_type_tree;
						 typedef	typename tree_type::node_type				node_type;
						 typedef	typename tree_type::node_pointer				node_pointer;
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

						 typename value_compare::result_type	is_equal(const typename value_compare::first_argument_type& x , const typename value_compare::second_argument_type& y) const 
						 {
							 if (_value_compare(x, y) || _value_compare(y, x))
								 return (false);
							 else
								 return (true);
						 }

					 public:


						 /////////////////
						 //             //
						 // CONSTRUCTOR //
						 //             //
						 /////////////////

						 explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc_arg), _tree_allocator(allocator_type_tree()),  _t_null(NULL), _tree(_alloc_tree(tree_type(_tree_allocator,_value_compare))) { }

						 template <class InputIterator>
							 map (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc_arg = allocator_type()) : _key_compare(comp), _value_compare(comp), _alloc(alloc_arg), _tree_allocator(allocator_type_tree()), _t_null(NULL), _tree(_alloc_tree(tree_type(_tree_allocator,_value_compare)))
						 {
							 insert(first,last);
						 }

						 map(const map& x) : _key_compare(x._key_compare), _value_compare(x._key_compare), _alloc(x._alloc), _tree_allocator(x._tree_allocator),  _t_null(NULL), _tree(_alloc_tree(*x._tree)) { }

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
								 _key_compare = x._key_compare;
								 _value_compare = x._value_compare;
								 _alloc = x._alloc;
								 _tree_allocator = x._tree_allocator;
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
							 node_pointer& to_find = _tree->search(val);
							 if (to_find == _t_null)
								 return (ft::make_pair<iterator, bool>(iterator(_tree->insert_node(val)), true));
							 else
								 return (ft::make_pair<iterator, bool>(iterator(to_find), false));
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
							 _tree->delete_tree(_tree->get_root());
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
