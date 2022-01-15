#include <map>
#include "map.hpp"

int main(void)
{
  	// {
	// 	std::map<int, std::string> first;

	// 	// first['a'] = 10;
	// 	// first['b'] = 20;
	// 	// first['c'] = 30;
	// 	// first['d'] = 40;
	// 	// first['e'] = 50;
	// 	first[42] = "fgzgxfn";
	// 	first[25] = "funny";
	// 	first[80] = "hey";
	// 	first[12] = "no";
	// 	first[27] = "bee";
	// 	first[90] = "8";

	// 	for (std::map<int, std::string>::iterator i = first.begin(); i != first.end(); i++)
	// 		std::cout << i->first << " : " << i->second << std::endl;
		//std::cout << first.max_size() << std::endl;
		// first.erase('a');
		// first.erase('b');
		// first.erase('c');
	
	// std::map<char, int>::iterator i = first.begin(), it = first.end();
	// std::cout << "begin "<< &i << "  end " << &it << std::endl;

// 		std::map<char, int> second (first.begin(), first.end());
// 		// first.erase('a');
// 		// first.erase('b');
	// for (; i != it; i++)
	// {	std::cout << "begin "<< &i << "  end " << &it << std::endl;

	// 	std::cout << "for "<< " : " << i->first << " / " << &i << std::endl;
	// }
	// 	std::cout << "begin "<< &i << "  end " << &it << std::endl;

	// std::cout << " : " << i->first << " / " << &i << std::endl;
	// i = first.end();
	// std::cout << " : " << i->first << " / " << &i << std::endl;
	// i--;
	// std::cout << " : " << i->first << " / " << &i << std::endl;

	// i = first.begin();
	// first.insert(std::pair<char, int>('a', 0));
	// std::cout << "insert " << " : " << i->first << std::endl;
// 		std::map<char, int>::iterator it = first.begin();
// 		std::cout << it->first << &it << '\n';
// 		it++;
// 		std::cout << it->first << &it << '\n';
// 		it++;
// 		std::cout << it->first << &it << '\n';
//  	}

 	std::cout << "==============\n";

	ft::map<char, int> first;
	//ft::map<char, int> second;
	first['a'] = 10;
	first['b'] = 20;
	first['c'] = 30;
	first['d'] = 40;
	first['e'] = 50;

// ft::map<int, std::string> first;

	// 	first[42] = "fgzgxfn";
	// 	first[25] = "funny";
	// 	first[80] = "hey";
	// 	first[12] = "no";
	// 	first[27] = "bee";
	// 	first[90] = "8";

	ft::map<char, int>::iterator i1;

	std::cout << "before \n";

	for (i1 = first.begin(); i1 != first.end(); i1++)
		std::cout << "???" << i1->first << " : " << i1->second << std::endl;
	std::cout << "after \n";
	std::cout << first.max_size() << std::endl;
	// ft::map<char, int>::iterator i = first.upper_bound('a');
	//std::cout << i->first << std::endl;
	ft::map<char, int> second (first.begin(), first.end());

	first.erase('a');
	first.erase('b');
	first.erase('c');
	first.erase('d');
	first.erase('e');
	std::cout << "123\n";
	ft::map<char, int>::const_iterator i;
	std::cout << "123\n";
	i = first.begin();
	std::cout << "1\n";
	ft::map<char, int>::const_iterator it = first.end();
	std::cout << "1\n";
	std::cout << "begin " << &i << " end " << &it << std::endl;
	std::cout << "1\n";
	for (; i != it; ++i)
	{	
		std::cout << "for ?? " << " : " << i->first << " / " << &i << std::endl;
	}

	std::cout << "begin " << &i << " end " << &it << std::endl;

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