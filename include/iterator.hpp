/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:22:05 by csejault          #+#    #+#             */
/*   Updated: 2022/04/25 20:08:48 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
//https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
namespace ft {


	struct input_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	template <class Iterator>
		class iterator_traits
		{
			public:
				typedef	typename Iterator::difference_type		difference_type;
				typedef	typename Iterator::value_type			value_type;
				typedef	typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference; 
				typedef	typename Iterator::iterator_category	iterator_category;
		};


	template <class T>
		class iterator_traits<T*>
		{
			public:
				typedef	ptrdiff_t								difference_type;
				typedef	T										value_type;
				typedef	T*										pointer;
				typedef T&										reference; 
				typedef ft::random_access_iterator_tag			iterator_category;
		};

	template <class T>
		class iterator_traits<const T*>
		{
			public:
				typedef	ptrdiff_t								difference_type;
				typedef	T										value_type;
				typedef	const T*								pointer;
				typedef const T&								reference; 
				typedef ft::random_access_iterator_tag			iterator_category;
		};


	template< class Iterator >
		class reverse_iterator
		{

			public:
				typedef Iterator													iterator_type;
				typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
				typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
				typedef typename ft::iterator_traits<Iterator>::reference			reference;

				//reverse_iterator( void ) : _ptr(NULL) { }
				reverse_iterator( void ) : _ptr() { }
				explicit reverse_iterator( iterator_type x ) : _ptr(x) { }
				template< class U >
					reverse_iterator( const reverse_iterator<U>& other ) : _ptr(other.base()) { }

				~reverse_iterator( void ) {};



				iterator_type 		base() const { return (iterator_type( _ptr )); }


				reference			operator*( void ) const { iterator_type tmp = _ptr; return *(--tmp); }
				pointer				operator->( void ) const { return &(operator*()); }

				reverse_iterator &	operator++( void ) { --_ptr; return *this; }
				reverse_iterator	operator++( int ) { reverse_iterator to_ret = *this; operator++(); return to_ret; }

				reverse_iterator &	operator--( void ) { ++_ptr; return *this; }
				reverse_iterator	operator--( int ) { reverse_iterator to_ret = *this; operator--(); return to_ret; }

				reverse_iterator 	operator+( const difference_type & nb ) const {return reverse_iterator(_ptr - nb); }
			
				reverse_iterator &	operator+=( const difference_type & nb ) { _ptr = _ptr -nb; return *this;}

				reverse_iterator 	operator-( const difference_type & nb ) const { return reverse_iterator(_ptr + nb); }
				reverse_iterator &	operator-=( const difference_type & nb ) { _ptr = _ptr +nb; return *this;}

				reference			operator[](const difference_type & nb) const { return *(*this + nb); }

			private:
				iterator_type	_ptr;
		};


	template <class Iterator>
		reverse_iterator<Iterator> operator+ (
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it)
		{
				return (reverse_iterator<Iterator>(rev_it.base() - n));
		}

	template <class L_Iterator, class R_Iterator>
  typename reverse_iterator<L_Iterator>::difference_type operator- (
    const reverse_iterator<L_Iterator>& lhs,
    const reverse_iterator<R_Iterator>& rhs)
	{
				return (rhs.base() - lhs.base());
		}

	
	template <class L_Iterator, class R_Iterator>
		bool operator== (const reverse_iterator<L_Iterator>& lhs,
				const reverse_iterator<R_Iterator>& rhs)
		{
			return ( lhs.base() == rhs.base() );
		}

	template <class L_Iterator, class R_Iterator>
		bool operator!= (const reverse_iterator<L_Iterator>& lhs,
				const reverse_iterator<R_Iterator>& rhs)
		{
			return ( !(lhs == rhs) );
		}

	template <class L_Iterator, class R_Iterator>
		bool operator<  (const reverse_iterator<L_Iterator>& lhs,
				const reverse_iterator<R_Iterator>& rhs)
		{
			return (lhs.base() > rhs.base());
		}


	template <class L_Iterator, class R_Iterator>
		bool operator>  (const reverse_iterator<L_Iterator>& lhs,
				const reverse_iterator<R_Iterator>& rhs)
		{ 
			return (lhs.base() < rhs.base());
		}

	template <class L_Iterator, class R_Iterator>
		bool operator<= (const reverse_iterator<L_Iterator>& lhs,
				const reverse_iterator<R_Iterator>& rhs)
		{
			return ( !(lhs > rhs) );
		}

	template <class L_Iterator, class R_Iterator>
		bool operator>= (const reverse_iterator<L_Iterator>& lhs,
				const reverse_iterator<R_Iterator>& rhs)
		{
			return ( !(lhs < rhs) );
		}

	//	template <class T>
	//		class	random_access_iterator
	//		{
	//			public:
	//
	//				typedef	T								value_type;
	//				typedef ft::random_access_iterator_tag	iterator_category;
	//				typedef	ptrdiff_t						difference_type;
	//				typedef	T*								pointer;
	//				typedef T&								reference; 
	//				typedef	random_access_iterator			class_name;
	//
	//
	//				////////////////////////////////////////////////////////////////////////////////////
	//				//                                                                                //
	//				// Is default-constructible, copy-constructible, copy-assignable and destructible //
	//				//                                                                                //
	//				////////////////////////////////////////////////////////////////////////////////////
	//
	//				~random_access_iterator( void );
	//				random_access_iterator( void ) : _ptr(NULL) {}
	//				random_access_iterator( random_access_iterator<T> &to_cpy ) : _ptr(to_cpy.get_ptr()) {}
	//				random_access_iterator & operator=( const random_access_iterator<T>& asign ) { if (&asign != this)_ptr = asign.get_ptr(); }
	//
	//
	//				/////////////////////////////////////////////////////////////////////////////
	//				//                                                                         //
	//				// Can be compared for equivalence using the equality/inequality operators //
	//				//                                                                         //
	//				/////////////////////////////////////////////////////////////////////////////
	//
	//				bool	operator==( const random_access_iterator<T> &rhs ) const { return _ptr == rhs._ptr; }
	//				bool	operator!=( const random_access_iterator<T> &rhs ) const { return !(*this == rhs); }
	//
	//
	//				///////////////////////////////////////////////////////////////////////
	//				//                                                                   //
	//				// Can be dereferenced as an rvalue (if in a dereferenceable state). //
	//				//                                                                   //
	//				///////////////////////////////////////////////////////////////////////
	//
	//				reference	operator*( void ) const { return *_ptr; }
	//				pointer		operator->( void ) const { return _ptr; }
	//
	//
	//				/////////////////////////////////////////////////////////
	//				//                                                     //
	//				// Can be incremented (if in a dereferenceable state). //
	//				//                                                     //
	//				/////////////////////////////////////////////////////////
	//
	//				class_name &	operator++( void ) { ++_ptr; return *this; }
	//				class_name 		operator++( int ) { class_name to_ret = *this; ++*this; return to_ret; }
	//
	//
	//				///////////////////////////////////////////////////////////////////////////
	//				//                                                                       //
	//				// Can be decremented (if a dereferenceable iterator value precedes it). //
	//				//                                                                       //
	//				///////////////////////////////////////////////////////////////////////////
	//
	//				class_name &	operator--( void ) { --_ptr; return *this; }
	//				class_name 		operator--( int ) { class_name to_ret = *this; --*this; return to_ret; }
	//
	//
	//				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//				//                                                                                                                              //
	//				// Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another. //
	//				//                                                                                                                              //
	//				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//				//???n + a
	//				class_name &	operator+( const difference_type & nb ) { return static_cast<class_name>(_ptr + nb); }
	//
	//				class_name &	operator-( const difference_type & nb ) { return static_cast<class_name>(_ptr - nb); }
	//				difference_type &	operator-( const class_name & rai ) { return _ptr - rai._ptr; }
	//
	//				pointer get_ptr( void ) const { return _ptr; }
	//
	//
	//				/////////////////////////////////////////////////////////////////////////////
	//				//                                                                         //
	//				// Can be compared with inequality relational operators (<, >, <= and >=). //
	//				//                                                                         //
	//				/////////////////////////////////////////////////////////////////////////////
	//
	//				bool	operator<( const class_name & rhs ) const { return _ptr < rhs._ptr; }
	//				bool	operator>( const class_name & rhs ) const { return _ptr > rhs._ptr; }
	//				bool	operator<=( const class_name & rhs ) const { return !(*this > rhs); }
	//				bool	operator>=( const class_name & rhs ) const { return !(*this < rhs); }
	//
	//
	//				///////////////////////////////////////////////////////
	//				//                                                   //
	//				// Supports compound assignment operations += and -= //
	//				//                                                   //
	//				///////////////////////////////////////////////////////
	//
	//				class_name &	operator+=( const difference_type & nb ) { _ptr += nb; return *this;}
	//				class_name &	operator-=( const difference_type & nb ) { _ptr -= nb; return *this;}
	//
	//
	//				///////////////////////////////////////////////////
	//				//                                               //
	//				// Supports the offset dereference operator ([]) //
	//				//                                               //
	//				///////////////////////////////////////////////////
	//
	//				reference			operator[](const difference_type & nb) { return *(_ptr + nb); }
	//
	//			private:
	//				pointer _ptr;
	//		};
}
#endif
