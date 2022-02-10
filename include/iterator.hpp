/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:22:05 by csejault          #+#    #+#             */
/*   Updated: 2022/02/09 19:11:45 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
//https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
namespace ft {

	struct random_access_iterator_tag {};

	template <class T>
		class	random_access_iterator
		{
			public:

				typedef	T								value_type;
				typedef ft::random_access_iterator_tag	iterator_category;
				typedef	ptrdiff_t						difference_type;
				typedef	T*								pointer;
				typedef T&								reference; 
				typedef	random_access_iterator			class_name;


				////////////////////////////////////////////////////////////////////////////////////
				//                                                                                //
				// Is default-constructible, copy-constructible, copy-assignable and destructible //
				//                                                                                //
				////////////////////////////////////////////////////////////////////////////////////

				~random_access_iterator( void );
				random_access_iterator( void ) : _ptr(NULL) {}
				random_access_iterator( random_access_iterator<T> &to_cpy ) : _ptr(to_cpy.get_ptr()) {}
				random_access_iterator & operator=( const random_access_iterator<T>& asign ) { if (&asign != this)_ptr = asign.get_ptr(); }


				/////////////////////////////////////////////////////////////////////////////
				//                                                                         //
				// Can be compared for equivalence using the equality/inequality operators //
				//                                                                         //
				/////////////////////////////////////////////////////////////////////////////

				bool	operator==( const random_access_iterator<T> &rhs ) const { return _ptr == rhs._ptr; }
				bool	operator!=( const random_access_iterator<T> &rhs ) const { return !(*this == rhs); }


				///////////////////////////////////////////////////////////////////////
				//                                                                   //
				// Can be dereferenced as an rvalue (if in a dereferenceable state). //
				//                                                                   //
				///////////////////////////////////////////////////////////////////////

				reference	operator*( void ) const { return *_ptr; }
				pointer		operator->( void ) const { return _ptr; }


				/////////////////////////////////////////////////////////
				//                                                     //
				// Can be incremented (if in a dereferenceable state). //
				//                                                     //
				/////////////////////////////////////////////////////////

				class_name &	operator++( void ) { ++_ptr; return *this; }
				class_name 		operator++( int ) { class_name to_ret = *this; ++*this; return to_ret; }


				///////////////////////////////////////////////////////////////////////////
				//                                                                       //
				// Can be decremented (if a dereferenceable iterator value precedes it). //
				//                                                                       //
				///////////////////////////////////////////////////////////////////////////

				class_name &	operator--( void ) { --_ptr; return *this; }
				class_name 		operator--( int ) { class_name to_ret = *this; --*this; return to_ret; }


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//                                                                                                                              //
				// Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another. //
				//                                                                                                                              //
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//???n + a
				class_name &	operator+( const difference_type & nb ) { return static_cast<class_name>(_ptr + nb); }

				class_name &	operator-( const difference_type & nb ) { return static_cast<class_name>(_ptr - nb); }
				difference_type &	operator-( const class_name & rai ) { return _ptr - rai._ptr; }

				pointer get_ptr( void ) const { return _ptr; }


				/////////////////////////////////////////////////////////////////////////////
				//                                                                         //
				// Can be compared with inequality relational operators (<, >, <= and >=). //
				//                                                                         //
				/////////////////////////////////////////////////////////////////////////////

				bool	operator<( const class_name & rhs ) const { return _ptr < rhs._ptr; }
				bool	operator>( const class_name & rhs ) const { return _ptr > rhs._ptr; }
				bool	operator<=( const class_name & rhs ) const { return !(*this > rhs); }
				bool	operator>=( const class_name & rhs ) const { return !(*this < rhs); }


				///////////////////////////////////////////////////////
				//                                                   //
				// Supports compound assignment operations += and -= //
				//                                                   //
				///////////////////////////////////////////////////////

				class_name &	operator+=( const difference_type & nb ) { _ptr += nb; return *this;}
				class_name &	operator-=( const difference_type & nb ) { _ptr -= nb; return *this;}


				///////////////////////////////////////////////////
				//                                               //
				// Supports the offset dereference operator ([]) //
				//                                               //
				///////////////////////////////////////////////////

				reference			operator[](const difference_type & nb) { return *(_ptr + nb); }

			private:
				pointer _ptr;
		};
}
#endif
