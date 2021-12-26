#include <iostream>
#include <vector>
#include "vector.hpp"

int main()
{
    std::vector<int> t1(5, 10);
    std::vector<int> t2(t1.begin(), t1.end());

    std::cout << "t1 " << t1.size() << " " << t1.capacity() << std::endl;
    for(std::vector<int>::iterator i = t1.begin(); i != t1.end(); i++)
        std::cout << *i << std::endl;
    std::cout << "t2 " << t1.size() << " " << t1.capacity() << std::endl;
    for(std::vector<int>::iterator i = t2.begin(); i != t2.end(); i++)
        std::cout << *i << std::endl;

    t2[2] = 5;
    for(int i = 0; i < 5; i++)
        std::cout << t1[i] << " / " << t2[i] << std::endl;
    return (0);
}