/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:50:03 by csejault          #+#    #+#             */
/*   Updated: 2022/04/11 10:15:06 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//SOURCES :	Introduction to Algorithms : Thomas H. Cormen - Charles E. Leiserson - Ronald L. Rivest - Clifford Stein
//Class_Name = node

//define{
#ifndef NODE_HPP
# define NODE_HPP
# include <iostream>
//define - END}

template < class T >
class	node {

	public:

		typedef T						value_type;
		typedef T*						pointer;
		typedef T&						reference;
		typedef const T*				const_pointer;
		typedef const T&				const_reference;
		typedef node<T> 				node_type;
		typedef node_type* 				node_pointer;
		typedef node_type& 				node_reference;
		typedef const node_type* 		const_node_pointer;
		typedef const node_type&	 	const_node_reference;

		enum	t_color {
			BLACK = 0,
			RED
		};

		//pub_constructor{
		//node( void ) : color(BLACK), p(NULL), left(NULL), right(NULL) {} //used to create t_null -- unitisialized data
		node(node_pointer& t_null, value_type k) :color(RED), tree_null(t_null), p(t_null), left(t_null), right(t_null), data(k) {} //used to create node

		node(bool c, node_pointer t_null,  node_pointer parent, node_pointer left_node, node_pointer right_node, value_type dt) : color(c), tree_null(t_null), p(parent), left(left_node), right(right_node), data(dt) {} //used to create node

		node(const node& cpy) : color(cpy.color), tree_null(cpy.tree_null), p(cpy.p), left(cpy.left), right(cpy.right), data(cpy.data){ }

		~node( void ) {}
		//pub_constructor - END}

		//pub_operator{
		node&	operator=(const node& x)
		{
			if (this != &x)
			{
				color = x.color;
				tree_null = x.tree_null;
				p = x.p;
				left = x.left;
				right = x.right;
				data = x.data;
			}
			return (*this);
		}

		pointer	operator->( void )
		{
			return (&data);
		}

		const_pointer	operator->( void ) const
		{
			return (&data);
		}

		reference	operator*( void )
		{
			return (data);
		}

		const_reference	operator*( void ) const
		{
			return (data);
		}

		//pub_operator - END}

		//pub_debug{
		//pub_debug - END}

		//pub_static{
		//pub_static - END}

		//pub_getter{
		//pub_getter - END}

		//pub_setter{
		//pub_setter - END}

		//pub_exception{
		//pub_exception - END}

		//pub_fct{
		void	print_data( void ) {
			std::cout << data.first << " = " << data.second << std::endl;
		}

		node_pointer	minimum( void )
		{
			node_pointer m = this;
			while (m->left != tree_null)
				m = m->left;
			return (m);
		}

		node_pointer	maximum( void )
		{
			node_pointer m = this;

			while (m->right != tree_null)
				m = m->right;
			return (m);
		}

		node_pointer successor( void )
		{
			return (successor(this));
		}

		node_pointer predecessor( void ) 
		{
			return (predecessor(this));
		}

		node_pointer predecessor(node_pointer n) 
		{
			if (n->left != tree_null)
				return (n->left->maximum());
			node_pointer s = n->p;
			while(s != tree_null && n == s->left)
			{
				n = s;
				s = s->p;
			}
			return (s);
		}

		node_pointer successor(node_pointer n) 
		{
			if (n->right != tree_null)
				return (n->right->minimum());
			node_pointer s = n->p;
			while(s !=tree_null && n == s->right)
			{
				n = s;
				s = s->p;
			}
			return (s);
		}
		//pub_fct - END}

		//pub_var{
		bool	color;
		node_pointer		tree_null;
		node_pointer		p;
		node_pointer		left;
		node_pointer		right;
		value_type			data;
		//pub_var - END}

	private:
		//priv_debug{
		//priv_debug - END}

		//priv_constructor{
		//priv_constructor - END}

		//priv_static{
		//priv_static - END}

		//priv_var{
		//priv_var - END}
};

//out_class{
//std::ostream &	operator<<(std::ostream &os, node &to_print);
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
