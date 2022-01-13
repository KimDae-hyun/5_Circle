#include <map>
#include "map.hpp"

int main(void)
{
//   	{
// 		std::map<char, int> first;

// 		first['a'] = 10;
// 		first['b'] = 20;
// 		first['c'] = 30;
		
// 		first.erase('a');
// 		first.erase('b');
// 		first.erase('c');
	
// 	std::map<char, int>::iterator i;
// // // 		std::map<char, int> second (first.begin(), first.end());

// // // 		// first.erase('a');
// // // 		// first.erase('b');
// 	for (i = first.begin(); i != first.end(); i++)
// 		std::cout << "for "<< " : " << i->first << " / " << &i << std::endl;
// 	// std::cout << " : " << i->first << " / " << &i << std::endl;
// 	// i = first.end();
// 	// std::cout << " : " << i->first << " / " << &i << std::endl;
// 	// i--;
// 	// std::cout << " : " << i->first << " / " << &i << std::endl;

// 	// i = first.begin();
// 	// first.insert(std::pair<char, int>('a', 0));
// 	// std::cout << "insert " << " : " << i->first << std::endl;
// // 		std::map<char, int>::iterator it = first.begin();
// // 		std::cout << it->first << &it << '\n';
// // 		it++;
// // 		std::cout << it->first << &it << '\n';
// // 		it++;
// // 		std::cout << it->first << &it << '\n';
//   	}

 	std::cout << "==============\n";

	ft::map<char, int> first;
	ft::map<char, int> second;

	first['a'] = 10;
	first['b'] = 20;
	first['c'] = 30;
	first['d'] = 40;
	first['e'] = 50;


	// // ft::map<char, int>::iterator i = first.upper_bound('a');

	// // std::cout << i->first << std::endl;
	// // ft::map<char, int> second (first.begin(), first.end());


	first.erase('a');
	first.erase('b');
	first.erase('c');
	first.erase('d');
	first.erase('e');

	ft::map<char, int>::iterator i;

	i = first.begin();
	std::cout << "1\n";

	i = first.end();
	std::cout << "1\n";
	//std::cout << i->second << std::endl;
	for (i = first.begin(); i != first.end(); i++)
	{	
		std::cout << "for " << " : " << i->first << " / " << &i << std::endl;
	}


	std::cout << "for " << " : " << " / " << &i << std::endl;

	 i = first.end();
	std::cout << (i != first.end()) << " ??\n";
	//std::cout << i->first << " / " << &i << std::endl;
	i = first.end();
	std::cout << " / " << &i << std::endl;
	// ++i;
	// --i;
	std::cout << " / " << &i << std::endl;

	std::cout << "empty " << first.empty() << std::endl;
	std::cout << "size " << first.size() << std::endl;
	std::cout << "max_size " << first.max_size() << std::endl;

	second.insert(ft::pair<char, int>('f', 60));
	second.insert(ft::pair<char, int>('g', 60));

	first.swap(second);
	for (ft::map<char, int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << "for " << " : " << it->first << " / " << &it << std::endl;
	std::cout << "==============\n";
	for (ft::map<char, int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << "for " << " : " << it->first << " / " << &it << std::endl;

	std::cout << "==============\n";

	second.clear();

	second['n'] = 0;
	for (ft::map<char, int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << "for " << " : " << it->first << " / " << &it << std::endl;
	std::cout << second.size() << std::endl;
	return 0;
}