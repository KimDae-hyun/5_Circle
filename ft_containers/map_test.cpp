#include <map>
#include "map.hpp"

int main(void)
{
//   	{
// 		std::map<char, int> first;

// 		first['a'] = 10;
// 		first['b'] = 20;
// 		first['c'] = 30;
		
// // // 		std::map<char, int> second (first.begin(), first.end());

// // // 		// first.erase('a');
// // // 		// first.erase('b');
// 		std::map<char, int>::iterator i;
// 	for (i = first.begin(); i != first.end(); i++)
// 		std::cout << "for "<< " : " << i->first << " / " << &i << std::endl;
// 	std::cout << " : " << i->first << " / " << &i << std::endl;
// 	i = first.end();
// 	std::cout << " : " << i->first << " / " << &i << std::endl;
// 	i--;
// 	std::cout << " : " << i->first << " / " << &i << std::endl;

// // 		std::map<char, int>::iterator it = first.begin();
// // 		std::cout << it->first << &it << '\n';
// // 		it++;
// // 		std::cout << it->first << &it << '\n';
// // 		it++;
// // 		std::cout << it->first << &it << '\n';
//   	}

 	std::cout << "==============\n";

	ft::map<char, int> first;

	first['a'] = 10;
	first['b'] = 20;
	first['c'] = 30;
	first['d'] = 40;
	first['e'] = 50;


	//ft::map<char, int>::iterator i = first.upper_bound('a');

//	std::cout << i->first << std::endl;
	//ft::map<char, int> second (first.begin(), first.end());


	//first.erase('a');
	//first.erase('b');
	//int n = 0;
	ft::map<char, int>::iterator i;

	//std::cout << i->second << std::endl;
	for (i = first.begin(); i != first.end(); i++)
	{
		//n++;
		std::cout << "for " << " : " << i->first << " / " << &i << std::endl;
		std::cout << (i != first.end()) << " ??\n";

		// if (n > 4)
		// 	break;
	}
	// std::cout << "for " << " : " << i->first << " / " << &i << std::endl;

	// std::cout << (i != first.end()) << " ??\n";

	// std::cout << n << " : " << i->first << " / " << &i << std::endl;
	// i = first.end();
	// std::cout << " : " << i->first << " / " << &i << std::endl;
	//++i;
	// --i;
	// std::cout << " : " << i->first << " / " << &i << std::endl;

	// 	//std::cout << i->first << " = " << i->second << '\n';
		

	// ft::map<char, int>::iterator it = first.begin();
	// std::cout << it->first  << " / " << &i << '\n';
	// it++;
	// std::cout << it->first << " / " << &i << '\n';
	// it++;
	// std::cout << it->first << " / " << &i << '\n';
	// it++;
	// std::cout << it->first << " / " << &i << '\n';
	// it++;
	// std::cout << it->first << " / " << &i << '\n';
	// it++;
	// std::cout << it->first << " / " << &i << '\n';
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