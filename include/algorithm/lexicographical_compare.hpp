/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:16:53 by csejault          #+#    #+#             */
/*   Updated: 2022/02/07 12:02:55 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {
	template<class InputIt1, class InputIt2>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2)
		{
			for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
				if (*first1 < *first2) return true;
				if (*first2 < *first1) return false;
			}
			return (first1 == last1) && (first2 != last2);
		}

	template<class InputIt1, class InputIt2, class Compare>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2,
				Compare comp)
		{
			for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
				if (comp(*first1, *first2)) return true;
				if (comp(*first2, *first1)) return false;
			}
			return (first1 == last1) && (first2 != last2);
		}
}
