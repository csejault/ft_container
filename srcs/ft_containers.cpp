/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_containers.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:45:07 by csejault          #+#    #+#             */
/*   Updated: 2022/02/09 18:07:14 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"
#include <utility>      // std::pair, std::make_pair
#include <algorithm>    // std::lexicographical_compare std::equal
#include <string>       // std::string
#include <vector>       // std::vector
#include <iostream>     // std::cout, std::boolalpha
#include <cctype>       // std::tolower

void	print_title(std::string to_print)
{
	int i = -1 ;
	while ( ++i < static_cast<int>(to_print.size()))
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "LIB_NAME = ft - " <<  to_print << " - CHECK" << std::endl;
	i = 1;
	while ( ++i < static_cast<int>(to_print.size()))
		std::cout << "#";
	std::cout << std::endl;
}

bool mypredicate (int i, int j) {
	return (i==j);
}

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

namespace LIB = ft;
int main ()
{
	////////////////
	//            //
	// Check Pair //
	//            //
	////////////////

	print_title("Pair");
	LIB::pair <std::string,double> product1;                     // default constructor
	LIB::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	LIB::pair <std::string,double> product3 (product2);          // copy constructor

	product1 = LIB::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double

	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';


	///////////
	//       //
	// Equal //
	//       //
	///////////

	print_title("Equal");
	int myints[] = {
		20,40,60,80,100};               //   myints: 20 40 60 80 100
	std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( LIB::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( LIB::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";


	/////////////////////////////
	//                         //
	// Lexicographical_compare //
	//                         //
	/////////////////////////////
	
	print_title("Lexicographical_compare");

	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << LIB::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << LIB::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';

	
	////////////////////////////
	//                        //
	// Random_access_iterator //
	//                        //
	////////////////////////////

	print_title("Random_access_iterator");
	print_title("TO_UPGRADE");
	
	std::vector<int>v1(5,5);
	std::vector<int>v2(10,10);
	std::cout << v1.end() - v1.begin() << std::endl;
	return 0;
}
