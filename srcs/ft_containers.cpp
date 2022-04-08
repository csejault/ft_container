/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_containers.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:45:07 by csejault          #+#    #+#             */
/*   Updated: 2022/04/08 17:01:13 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"

namespace LIB = ft;

void	print_title(std::string to_print)
{
	int i = 0;
	std::cout << std::endl;
	while ( ++i < 10)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "LIB_NAME = ft - " <<  to_print << " - CHECK" << std::endl;
	i = 0;
	while ( ++i < 10 )
		std::cout << "#";
	std::cout << std::endl;
}

bool mypredicate (int i, int j) {
	return (i==j);
}

template <class K, class V>
void print_map_ref(LIB::map<K,V> &vct)
{
	typename LIB::map<K,V>::iterator it = vct.begin();
	int i = 0;
	std::cout << "PRINT MAP REF" << std::endl;
	while (it != vct.end())
	{
		std::cout << i << "" << std::endl;
		std::cout << "K: " << it->first << std::endl;
		std::cout << "V: " << it->second << std::endl;
		i++;
		it++;
	}
	std::cout << "END PRINT MAP REF" << std::endl;
}

template <class K, class V>
void print_map_noref(LIB::map<K,V> vct)
{
	typename LIB::map<K,V>::iterator it = vct.begin();
	int i = 0;
	std::cout << "PRINT MAP NOREF" << std::endl;
	while (it != vct.end())
	{
		std::cout << i << "" << std::endl;
		std::cout << "K: " << it->first << std::endl;
		std::cout << "V: " << it->second << std::endl;
		i++;
		it++;
	}
	std::cout << "END PRINT MAP NOREF" << std::endl;
}

void print_vector(LIB::vector<int> vct)
{
	LIB::vector<int>::iterator it = vct.begin();
	int i = 0;
	while (it != vct.end())
	{
		std::cout << i << " = " << *it << std::endl;
		i++;
		it++;
	}
}

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

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


	////////////
	//        //
	// Vector //
	//        //
	////////////

	print_title("Vector");
	LIB::vector<int> vi(50,12);

	std::cout << "vi - max_size() : " << vi.max_size() << std::endl;
	std::cout << "vi - size() : " << vi.size() << std::endl;
	std::cout << "vi - capacity() : " <<vi.capacity() << std::endl;

	LIB::vector<int> va;
	va.push_back(5);
	std::cout << "va - max_size() : " << va.max_size() << std::endl;
	std::cout << "va - size() : " << va.size() << std::endl;
	std::cout << "va - capacity() : " <<va.capacity() << std::endl;

	LIB::vector<int> vb(va);
	std::cout << "vb - max_size() : " << vb.max_size() << std::endl;
	std::cout << "vb - size() : " << vb.size() << std::endl;
	std::cout << "vb - capacity() : " <<vb.capacity() << std::endl;
	vb = va;
	std::cout << "vb - max_size() : " << vb.max_size() << std::endl;
	std::cout << "vb - size() : " << vb.size() << std::endl;
	std::cout << "vb - capacity() : " <<vb.capacity() << std::endl;
	vb = vi;
	std::cout << "vb - max_size() : " << vb.max_size() << std::endl;
	std::cout << "vb - size() : " << vb.size() << std::endl;
	std::cout << "vb - capacity() : " <<vb.capacity() << std::endl;
	vb.clear();
	std::cout << "vb - max_size() : " << vb.max_size() << std::endl;
	std::cout << "vb - size() : " << vb.size() << std::endl;
	std::cout << "vb - capacity() : " <<vb.capacity() << std::endl;

	try {
		std::cout << "vi - acces_ok : " << vi.at(vi.capacity() -1) << std::endl;
		std::cout << "vb - bad_acces : " << vb.at(vb.capacity()) << std::endl;
	}
	catch ( std::exception &e)
	{
		std::cerr << "EXCEPTION CATCHED - > " << e.what() << std::endl;
	}

	std::cout << "vi - operator [3] : " << vi[3] << std::endl;
	vi[3] += 30;
	std::cout << "vi - operator [3] after new assign : " << vi[3] << std::endl;

	std::cout << "vi - int &ref = vi.front() = " << vi.front() << std::endl;
	int &ref = vi.front();
	ref = 0;
	std::cout << "vi - vi.front() after ref = 0 = " << vi.front() << std::endl;

	std::cout << "back on vi = " << vi.back() << std::endl;
	int & ref2 = vi.back();
	ref2 = 666;
	std::cout << "back on vi after changing value = " << vi.back() << std::endl;

	LIB::vector<int>::iterator it = vi.begin();
	it += 3;

	std::cout << std::distance (vi.insert(it, 44444), vi.begin())<< std::endl;
	print_vector(vi);

	LIB::vector<int> vii;
	it = vii.begin();

	std::cout << std::distance(vii.insert(it, 0), vii.begin())<< std::endl;
	//vii.insert( it, 10 , 10);
	print_vector(vii);

	vi.resize(20);
	print_vector(vi);


	std::cout << "vinserta with input iterator" << std::endl;

	LIB::vector<int> vinserta;
	vinserta.push_back(1);
	vinserta.push_back(2);
	vinserta.push_back(3);
	LIB::vector<int> vinsertb;
	vinsertb.push_back(11);
	vinsertb.push_back(22);
	vinsertb.push_back(33);
	vinserta.insert(vinserta.begin() +1, vinsertb.begin(), vinsertb.end());
	print_vector(vinserta);
	std::cout << "vinserta assign with insertb begin-end" << std::endl;
	vinserta.assign(vinsertb.begin(), vinsertb.end());
	print_vector(vinserta);




	print_title("Map");
	typedef	int	k;
	typedef	std::string v;
	typedef LIB::map<k,v>	map_t;
	map_t	m;
	(void)m;
	LIB::pair<map_t::iterator, bool> p = m.insert(LIB::pair<k,v>(1,"un"));
	//if (m.begin() != p.first)
	//	std::cout << "Begin != p.first" << std::endl;
	//print_map_noref<k,v>(m);
	//print_map_ref<k,v>(m);
	//std::cout << (p.first)->first << std::endl;
	////p = m.insert(LIB::pair<int, std::string>(2,"deux"));
	////p = m.insert(LIB::pair<int, std::string>(3,"trois"));
	//std::cout << (p.first)->first << std::endl;
	//print_map_noref<k,v>(m);
	//print_map_ref<k,v>(m);
	//map_t	m2(m.begin(),m.end());
	//print_map_ref<k,v>(m2);
	//print_map_noref<k,v>(m2);




	//tree->insert_node(std::make_pair(1,"un"));
	//tree->insert_node(std::make_pair(4,"quatre"));
	//tree->insert_node(std::make_pair(12, "douze"));
	//tree->insert_node(std::make_pair(2, "deux"));
	//tree->insert_node(std::make_pair(6, "six"));
	//tree->insert_node(std::make_pair(10, "dix"));
	//tree->insert_node(std::make_pair(14, "quatorze"));
	//tree->insert_node(std::make_pair(3, "trois"));
	//tree->insert_node(std::make_pair(5, "cinq"));
	//tree->insert_node(std::make_pair(7, "sept"));
	//tree->insert_node(std::make_pair(9, "neuf"));
	//tree->insert_node(std::make_pair(11, "onze"));
	//tree->insert_node(std::make_pair(13, "treize"));
	//tree->insert_node(std::make_pair(15, "quinze"));
	//tree->inorder_walk();
	//std::cout << std::endl;
	////tree->inorder_walk();
	//tree->delete_node(std::make_pair(15, "quinze"));
	//tree->inorder_walk();
	////tree->inorder_walk();
	//std::cout << std::endl;

	//rbt<type>::node_pointer ptr = tree->minimum();
	//for (rbt<type>::iterator it(ptr); it != tree->get_t_null(); it++)
	//{
	//	std::cout << "it = " <<  it->first << std::endl;
	//}
	//std::cout << std::endl;
	//std::cout << std::endl;
	//tree->inorder_walk();
	return 0;

}
