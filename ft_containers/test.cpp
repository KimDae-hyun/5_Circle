#include <iostream>
//#include <vector>
#include "Vector2.hpp"

int main()
{
    ft::Vector<int> t1(5, 10);
    ft::Vector<int> t2(t1.begin(), t1.end());

    std::cout << "t1 " << t1.size() << " " << t1.capacity() << std::endl;
    for(ft::Vector<int>::iterator i = t1.begin(); i != t1.end(); i++)
        std::cout << *i << std::endl;
    std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;
    for(ft::Vector<int>::iterator i = t2.begin(); i != t2.end(); i++)
        std::cout << *i << std::endl;

    t2[1] = 1;
    t2[2] = 5;
    for(int i = 0; i < 5; i++)
        std::cout << t1[i] << " / " << t2[i] << std::endl;

    t2.insert(t2.begin() + 2, t2.begin(), t2.end());
    std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;
    t2.push_back(1);
        std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;

    for(int i = 0; i < t2.size(); i++)
        std::cout << t2[i] << std::endl;
    return (0);
}