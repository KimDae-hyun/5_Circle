#include <map>
#include "map.hpp"

int main(void)
{
	{
    std::map<char, int> first;

	first['a'] = 10;
	first['b'] = 20;
	
	std::map<char, int> second (first.begin(), first.end());

	first.erase('a');
	first.erase('b');

	for (std::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
	{
		std::cout << "here\n";
		std::cout << i->first << " = " << i->second << '\n';
	}
	}

	std::cout << "==============\n";

	ft::map<char, int> first;


	first['b'] = 10;
	first['a'] = 20;
	first['c'] = 30;

	ft::map<char, int> second (first.begin(), first.end());

	//first.erase('a');
	//first.erase('a');
	for (ft::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
		std::cout << i->first << " = " << i->second << '\n';

	// std::cout << (first.begin() == first.end()) << " ??\n";

	// ft::map<char, int>::iterator i = first.begin();
	// std::cout << i->first << '\n';
	// i++;
	// std::cout << i->first << '\n';
	// i++;
	// std::cout << i->first << '\n';

	// ft::map<char, int>::iterator it = first.end();
	// std::cout << it->first << '\n';
	// std::cout << "==============\n";


	// ft::map<std::string, int> origin;

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
	// std::cout << ret.first->first << std::endl;
	// std::cout << ret.first->second << std::endl;


	// std::cout << "==============\n";


	// ft::map<int, int> t;
	// t.insert(ft::pair<int, int>(3, 4));

	// for (ft::map<int, int>::iterator it = t.begin(); it != t.end(); it++)
	// 	std::cout << it->first << " / " << it->second << std::endl;

	return 0;
}