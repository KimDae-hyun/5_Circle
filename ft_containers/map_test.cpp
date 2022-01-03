#include <iostream>
#include <map>
#include "map.hpp"

int main(void)
{
	{
    std::map<char, int> first;

	first['a'] = 10;
	first['b'] = 20;
	
	std::map<char, int> second (first.begin(), first.end());

	for (std::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
		std::cout << i->first << " = " << i->second << '\n';
	}
	ft::map<char, int> first;

	first['a'] = 10;
	first['b'] = 20;
	
	ft::map<char, int> second (first.begin(), first.end());

	for (ft::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
		std::cout << i->data << " = " << i->data << '\n';
}