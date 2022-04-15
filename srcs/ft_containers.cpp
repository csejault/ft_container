/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_containers.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:45:07 by csejault          #+#    #+#             */
/*   Updated: 2022/04/15 17:24:01 by csejault         ###   ########.fr       */
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
	std::cout << "Size = " << vct.size() << std::endl;
	while (it != vct.end())
	{
		std::cout << "[" << i << "]";
		std::cout << it->first;
		std::cout << "(" << it->second << ") - ";
		i++;
		it++;
	}
	std::cout << "END PRINT MAP REF" << std::endl;
	std::cout << std::endl;
}

template <class K, class V>
void print_map_noref(LIB::map<K,V> vct)
{
	typename LIB::map<K,V>::iterator it = vct.begin();
	int i = 0;
	std::cout << "PRINT MAP NOREF" << std::endl;
	std::cout << "Size = " << vct.size() << std::endl;
	while (it != vct.end())
	{
		std::cout << "[" << i << "]";
		std::cout << it->first;
		std::cout << "(" << it->second << ") - ";
		i++;
		it++;
	}
	std::cout << "END PRINT MAP NOREF" << std::endl;
	std::cout << std::endl;
}


template <class k, class v>
	void check_map_insert_val(LIB::map<k,v>& MapToInsert, LIB::pair<k,v> p)
{
	LIB::pair<typename LIB::map<k,v>::iterator, bool> check = MapToInsert.insert(p);
	std::cout << "Insert : " << p.first << std::endl;
	if (MapToInsert.begin() != check.first)
		std::cout << "Begin != check.first" << std::endl;
	std::cout << (check.first)->first << std::endl;
	if (check.second)
		std::cout << "insert true" << std::endl;
	else
		std::cout << "insert false" << std::endl;
	print_map_noref<k,v>(MapToInsert);
	print_map_ref<k,v>(MapToInsert);
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
	m.clear();
	check_map_insert_val(m, LIB::pair<k,v>(3,"trois"));
	check_map_insert_val(m, LIB::pair<k,v>(0,"zero"));
	check_map_insert_val(m, LIB::pair<k,v>(1,"un"));

	std::cout << "size = " << m.size() << std::endl;
	check_map_insert_val(m, LIB::pair<k,v>(2,"deux"));
	check_map_insert_val(m, LIB::pair<k,v>(-1,"moins un"));

	std::cout << "Map insert double value - 3" << std::endl;
	check_map_insert_val(m, LIB::pair<k,v>(3,"deuxieme trois"));
	std::cout << "Map insert double value - 0" << std::endl;
	check_map_insert_val(m, LIB::pair<k,v>(0,"deuxieme zero"));

	map_t	m2(m.begin(),m.end());
	print_map_ref<k,v>(m2);
	print_map_noref<k,v>(m2);

	std::cout << "Map clear - check print and size" << std::endl;
	m.clear();
	print_map_ref<k,v>(m);
	print_map_noref<k,v>(m);
	m.clear();
	print_map_ref<k,v>(m);
	print_map_noref<k,v>(m);
	m = m2;
	print_map_ref<k,v>(m);
	print_map_noref<k,v>(m);
	m.clear();
	print_map_ref<k,v>(m);
	print_map_noref<k,v>(m);
	m = m2;
	print_map_ref<k,v>(m);
	print_map_noref<k,v>(m);

	map_t	m3(m.begin(),m.end());
	print_map_ref<k,v>(m3);
	print_map_noref<k,v>(m3);

	
	std::cout << "k 3 value " << m[3] << std::endl;
	std::cout << "find [3] - " << m.find(3)->second << std::endl;
	std::cout << "modif [3]" << std::endl;
	m[3] = "trois []";
	std::cout << m[3] << std::endl;
	print_map_ref<k,v>(m);
	print_map_noref<k,v>(m);
	std::cout << m[99] << std::endl;
	m[99] = "99 []";
	std::cout << m[99] << std::endl;
	std::cout << "count = " << m.count(99) << std::endl;
	std::cout << "count = " << m.count(98) << std::endl;
	std::cout << "count = " << m.count(3) << std::endl;
	std::cout << "lower bound key 0 = " << (m.lower_bound(0))->second << std::endl;
	std::cout << "upper bound key 0 = " << (m.upper_bound(0))->second << std::endl;
	std::cout << "lower bound key 2 = " << (m.lower_bound(2))->second << std::endl;
	std::cout << "upper bound key 2 = " << (m.upper_bound(2))->second << std::endl;
	std::cout << "lower bound key 90 = " << (m.lower_bound(90))->second << std::endl;
	std::cout << "upper bound key 90 = " << (m.upper_bound(90))->second << std::endl;
	std::cout << "lower bound key -100= " << (m.lower_bound(-100))->second << std::endl;
	std::cout << "upper bound key -100 = " << (m.upper_bound(-100))->second << std::endl;
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(-2); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(-1); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(0); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(1); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(2); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(3); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(4); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(5); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(6); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}
	for (LIB::pair<map_t::iterator, map_t::iterator> it = m.equal_range(7); it.first != it.second; it.first++) {std::cout << "equal range first = " << (it.first)->first << std::endl;}




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
