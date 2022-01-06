#include <iostream>
#include <vector>
#include "Vector.hpp"

int main()
{
    ft::Vector<int> t1(3, 10);
    ft::Vector<int> t2(t1.begin(), t1.end());

    std::cout << "t1 " << t1.size() << " " << t1.capacity() << std::endl;
    for(ft::Vector<int>::iterator i = t1.begin(); i != t1.end(); i++)
        std::cout << *i << ' ';
    std::cout << '\n';

    std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;
    for(ft::Vector<int>::iterator i = t2.begin(); i != t2.end(); i++)
        std::cout << *i << ' ';
    std::cout << '\n';

    t2[1] = 1;
    t2[2] = 5;
    for(int i = 0; i < 3; i++)
        std::cout << t1[i] << " / " << t2[i] << '\n';


    t2.insert(t2.begin() + 1, t2.rbegin(), t2.rend());
    std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;
    t2.push_back(1);
    std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;

    for(size_t i = 0; i < t2.size(); i++)
        std::cout << t2[i] << ' ';
    std::cout << '\n';

    ft::Vector<int> t3(3, 10);
    ft::Vector<int> t4(2, 7);

    t3.resize(5, 3);
    t3.swap(t4);

    for (unsigned i=0; i<t3.size(); i++)
        std::cout << t3.at(i) << ' ';
    std::cout << '\n';
    std::cout << "front, back " << t3.front() << ' ' << t3.back() << std::endl;
    std::cout << "t3 " << t3.size() << " " << t3.capacity() << std::endl;
    for(ft::Vector<int>::iterator i = t3.begin(); i != t3.end(); i++)
        std::cout << *i << ' ';
    std::cout << '\n';

    int *p;

    p = t3.get_allocator().allocate(3);
    for (int i = 0; i < 3; i++)
        p[i] = i;
    for(int i = 0; i < 3; i++)
        std::cout << p[i] << ' ';
    t3.get_allocator().deallocate(p, 3);

    return (0);
}