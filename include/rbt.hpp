/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:50:03 by csejault          #+#    #+#             */
/*   Updated: 2022/05/11 16:38:32 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//SOURCES :	Introduction to Algorithms : Thomas H. Cormen - Charles E. Leiserson - Ronald L. Rivest - Clifford Stein
//Class_Name = rbt

//define{
#ifndef RBT_HPP
# define RBT_HPP

# ifndef COL_GREEN
#  define COL_GREEN 		"\033[0;32m"
# endif
# ifndef COL_RED
#  define COL_RED		"\033[0;31m"
# endif
# ifndef COL_YELLOW
#  define COL_YELLOW		"\033[0;33m"
# endif
# ifndef COL_NORMAL
#  define COL_NORMAL		"\033[0m"
# endif

# include <iostream>
# include <memory>
# include "node.hpp"
# include "rbt_iterator.hpp"

template < class T >
class node;
//define - END}

template < class T, class Allocator = std::allocator< node<T> >, class Compare = std::less< T > >
class	rbt {
	public:
		enum	t_color {
			BLACK = 0,
			RED
		};
		typedef	T																value_type;
		typedef	value_type *													pointer;
		typedef	value_type &													reference;
		typedef Compare															compare_type;
		typedef	typename node<value_type>::node_type							node_type;
		typedef	typename node<value_type>::node_pointer							node_pointer;
		typedef rbt_iterator<value_type, node_type>								iterator;
		typedef rbt_iterator<const value_type, node_type>						const_iterator;
		typedef size_t															size_type;
		typedef Allocator														allocator_type;

		//pub_constructor{
		rbt(const allocator_type& alloc_arg = allocator_type(), const compare_type& compare_arg = compare_type()) : _size(0), _alloc(alloc_arg), _comp(compare_arg), _t_null(_alloc_t_null()), _root(_t_null)  { }

		rbt(const rbt& cpy) : _size(0), _alloc(cpy._alloc), _comp(cpy._comp), _t_null(_alloc_t_null()), _root(_t_null) { *this = cpy; }

		rbt&	operator=(const rbt& rhs)
		{
			if (this != &rhs)
			{
				if (_root != _t_null)
					delete_tree(_root);
				_comp = rhs._comp;
				_alloc = rhs._alloc;
				_root = _t_null;
				for (const_iterator it = const_iterator(rhs.minimum(), rhs._t_null, rhs._root); it != const_iterator(rhs._t_null, rhs._t_null, rhs._root); it++)
					insert_node(*it);

			}
			return (*this);
		}

		~rbt( void )
		{ 
			if (_root != _t_null)
				delete_tree(_root);
			deallocate_node(_t_null);
		}

		//pub_constructor - END}

		//pub_operator{
		//pub_operator - END}

		//pub_debug{
		//pub_debug - END}

		//pub_static{

		//pub_static - END}

		//pub_getter{

		size_type	size( void ) const
		{
			return (_size);
		}

		node_pointer	get_t_null( void ) const
		{
			return (_t_null);
		}

		node_pointer	get_root( void ) const
		{
			return (_root);
		}
		//pub_getter - END}

		//pub_setter{
		//pub_setter - END}

		//pub_exception{
		class	rotate_on_t_null : public std::exception
	{
		virtual const char* what() const throw()
		{
			return ("Rotate on t_null");
		}
	};
		//pub_exception - END}

		//pub_fct{
		node_pointer	minimum( void ) const
		{
			return(_root->minimum());
		}

		node_pointer	maximum( void ) const 
		{
			return(_root->maximum());
		}

		void	deallocate_node(node_pointer to_dell)
		{
			_alloc.destroy(to_dell);
			_alloc.deallocate(to_dell, 1);
		}

		node_pointer	create_node(node_type	n)
		{
			node_pointer	ret = _alloc.allocate(1);
			_alloc.construct(ret, n);
			return (ret);
		}

		node_pointer	insert_node(value_type k)
		{
			node_pointer n = create_node(node_type(_t_null,k));
			t_insert(n);
			_size++;
			return(n);
		}

		void	delete_node(value_type k)
		{
			node_pointer n = search(_root,k);
			if (n != _t_null)
			{
				t_delete(n);
				deallocate_node(n);
				_size--;
			}
		}

		void	delete_tree( node_pointer p )
		{
			if (p != _t_null)
			{
				delete_tree(p->left);
				delete_tree(p->right);
				deallocate_node(p);
				_size--;
			}
			_root = _t_null;
		}

		void	inorder_walk( void ) const
		{
			inorder_walk(_root);
		}

		void	inorder_walk( node_pointer p ) const
		{
			if (p != _t_null)
			{
				inorder_walk(p->left);
				p->print_data();
				inorder_walk(p->right);
			}
		}

		node_pointer&	search(const value_type& k) 
		{
			node_pointer & n = search(_root,k);
			return (n);
		}

		node_pointer&	search(node_pointer& n, const value_type& k)
		{
			if (n == _t_null || _is_equal(n->data, k)) 
				return (n);
			if (_comp(k, n->data))
				return (search(n->left, k));
			else
				return (search(n->right, k));
		}

		node_pointer	iterative_search(const value_type k) const
		{
			return(iterative_search(_root,k));
		}

		node_pointer	iterative_search(node_pointer n, const value_type k) const 
		{
			while (n != _t_null && !_is_equal(k, n->data))
			{
				if (_comp(k,n->data))
					n = n->left;
				else
					n = n->right;
			}
			return (n);
		}

		void	left_rotate(node_pointer x)
		{
			if (x->right == _t_null)
				throw (rotate_on_t_null());
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _t_null)
				y->left->p = x;
			y->p = x->p;	
			if (x->p == _t_null)
				_root = y;
			else if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->left = x;
			x->p = y;
		}

		void	right_rotate(node_pointer y)
		{
			if (y->left == _t_null)
				throw (rotate_on_t_null());
			node_pointer x = y->left;
			y->left = x->right;
			if (x->right != _t_null)
				x->right->p = y;
			x->p = y->p;	
			if (y->p == _t_null)
				_root = x;
			else if (y == y->p->left)
				y->p->left = x;
			else
				y->p->right = x;
			x->right = y;
			y->p = x;
		}


		void	t_insert(node_pointer z)
		{
			node_pointer y = _t_null;
			node_pointer x = _root;
			while (x != _t_null)
			{
				y = x;
				if (_comp(z->data, x->data))
					x = x->left;
				else
					x = x->right;
			}
			z->p = y;
			if (y == _t_null)
				_root = z;
			else if (_comp(z->data, y->data))
				y->left = z;
			else
				y->right = z;
			t_insert_fixup(z);
		}

		void	t_insert_fixup(node_pointer& z)
		{
			node_pointer uncle = _t_null;
			//z is red at the begining
			while (z->p->color == RED)
			{
				// if z'parent is a left child
				if (z->p == z->p->p->left)
				{
					uncle = z->p->p->right;
					if (uncle->color == RED)
					{
						//case 1 - z's uncle is red
						z->p->color = BLACK;
						uncle->color = BLACK;
						z->p->p->color = RED;
						//jump to grand parent(which just turned red)
						z = z->p->p;
					}
					else 
					{
						//z is not the root because it has an uncle
						if (z == z->p->right)
						{
							//case 2 - z is right child and uncle black
							z = z->p;
							left_rotate(z);
						}
						//case 3 - 
						//right rotate if uncle is black (balance)
						z->p->color = BLACK;
						z->p->p->color = RED;
						right_rotate(z->p->p);
					}
				}
				else
				{
					// if z'parent is a right child
					uncle = z->p->p->left;
					if (uncle->color == RED)
					{
						//case 1 - z's uncle is red
						z->p->color = BLACK;
						uncle->color = BLACK;
						z->p->p->color = RED;
						//jump to grand parent(which just turned red)
						z = z->p->p;
					}
					else 
					{
						//z is not the root because it has an uncle
						if (z == z->p->left)
						{
							//case 2 - z is right child and uncle black
							z = z->p;
							right_rotate(z);
						}
						//case 3 - 
						//right rotate if uncle is black (balance)
						z->p->color = BLACK;
						z->p->p->color = RED;
						left_rotate(z->p->p);
					}
				}
			}
			_root->color = BLACK;
		}

		void transplant(node_pointer u, node_pointer v)
		{
			if (u->p == _t_null)
				_root = v;
			else if (u == u->p->left)
				u->p->left = v;
			else
				u->p->right = v;
			v->p = u->p;
		}

		void	t_delete(node_pointer z)
		{
			node_pointer y = z;
			node_pointer x = _t_null;
			bool y_original_color = y->color;
			if (z->left == _t_null)
			{
				x = z->right;
				transplant(z,z->right);
			}
			else if (z->right == _t_null)
			{
				x = z->left;
				transplant(z,z->left);
			}
			else
			{
				y = z->right->minimum();
				y_original_color = y->color;
				if (y->p == z)
					x->p = y;
				else
				{
					transplant(y,y->right);
					y->right = z->right;
					y->right->p = y;
				}
				transplant(z,y);
				y->left = z->left;
				y->left->p = y;
				y->color = z->color;
				if (y_original_color == BLACK)
					t_delete_fixup(x);
			}
		}

		void	t_delete_fixup(node_pointer x)
		{
			node_pointer w = _t_null;
			while (x != _root && x->color == BLACK)
			{
				if (x == x->p->left)
				{
					w = x->p->right;
					if (w->color == BLACK)
					{
						w->color = BLACK;
						x->p->color = RED;
						left_rotate(x->p);
						w = x->p->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{
						if (w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							right_rotate(w);
							w = x->p->right;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->right->color = BLACK;
						left_rotate(x->p);
						x = _root;
					}
				}
				else
				{
					w = x->p->left;
					if (w->color == BLACK)
					{
						w->color = BLACK;
						x->p->color = RED;
						right_rotate(x->p);
						w = x->p->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{
						if (w->left->color == BLACK)
						{
							w->right->color = BLACK;
							w->color = RED;
							left_rotate(w);
							w = x->p->left;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->left->color = BLACK;
						right_rotate(x->p);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}

		iterator	lower_bound(value_type vt) const
		{
			iterator end = iterator(_t_null, _t_null, _root);
			iterator it = iterator(minimum(), _t_null, _root);
			while (it != end)
			{
				if (!_comp(*it, vt))
					break;
				it++;
			}
			return (it);
		}

		iterator	upper_bound(value_type vt) const
		{
			iterator end = iterator(_t_null, _t_null, _root);
			iterator it = iterator(minimum(), _t_null, _root);
			while (it != end)
			{
				if (_comp(vt, *it))
					break;
				it++;
			}
			return (it);
		}

		ft::pair<iterator,iterator>	equal_range(value_type vt) const
		{
			return (ft::make_pair(lower_bound(vt),upper_bound(vt)));
		}


		//pub_fct - END}

		//pub_var{
		//pub_var - END}

	private:

		bool _is_equal(const value_type& x , const value_type& y) const 
		{
			if (_comp(x, y) || _comp(y, x))
				return (false);
			else
				return (true);
		}

		node_pointer &	_alloc_t_null( void )
		{
			_t_null = create_node(node_type(BLACK, NULL,  NULL, NULL, NULL, value_type()));
			_t_null->p = _t_null;
			_t_null->left = _t_null;
			_t_null->right = _t_null;
			_t_null->tree_null = _t_null;
			return (_t_null);
		}

		//priv_debug{
		//priv_debug - END}

		//priv_constructor{
		//priv_constructor - END}

		//priv_static{
		//priv_static - END}

		//priv_var{
		size_type		_size;
		allocator_type	_alloc;
		compare_type	_comp;
		node_pointer	_t_null;
		node_pointer	_root;
		//priv_var - END}
};

//out_class{
//std::ostream &	operator<<(std::ostream &os, rbt &to_print);
//out_class - END}

#endif

//Color{
//The codes for foreground and background colours are:
//
//         foreground background
//black        30         40
//red          31         41
//green        32         42
//yellow       33         43
//blue         34         44
//magenta      35         45
//cyan         36         46
//white        37         47
//Color - END}
