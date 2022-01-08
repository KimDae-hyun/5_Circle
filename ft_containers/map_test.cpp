#include <iostream>
#include <map>
#include "map.hpp"

int main(void)
{
	// {
    // std::map<char, int> first;

	// first['a'] = 10;
	// first['b'] = 20;
	
	// std::map<char, int> second (first.begin(), first.end());

	// for (std::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
	// 	std::cout << i->first << " = " << i->second << '\n';
	// }

	// ft::map<char, int> first;

	// std::cout << "1\n";

	// first['a'] = 10;
	// first['b'] = 20;
					
	// std::cout << "1\n";
	// ft::map<char, int> second (first.begin(), first.end());
	// std::cout << "1\n";
	// for (ft::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
	// 	std::cout << i->data.first << " = " << i->data.second << '\n';



	ft::map<std::string, int> origin;

	// ft::pair<ft::map<std::string, int>::iterator, bool> ret;

	// ret = origin.insert( ft::pair<std::string, int>("test123", 1) );

	// if (ret.second == false)
	// {
	// 	if (ret.second == true)
	// 	{
	// 		std::cout << "insert fail. second value is true" << std::endl;
	// 	}
	// 	else if (ret.second == false)
	// 	{
	// 		std::cout << "insert sucess. second value is false" << std::endl;
	// 	}
	// }

	// //만약 반환된 이터레이터의 요소에 접근하려면
	// std::cout << ret.first->data.first << std::endl;
	// std::cout << ret.first->data.second << std::endl;

	// ft::map<int, int> t;
	// t.insert(ft::pair<int, int>(3, 4));
	// for (ft::map<int, int>::iterator it = t.begin(); it != t.end(); it++)
	// 	std::cout << it->data.first << " / " << it->data.second << std::endl;


	return 0;
}