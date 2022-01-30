#include <iostream>
#include <vector>
#include <sys/time.h>
#include "vector.hpp"

int main()
{
    // {
    // struct timeval t;
    // unsigned int start;
    // unsigned int end;

    // gettimeofday(&t, NULL);
    // start = t.tv_usec;
    // printf("start : %d\n", start);

    // std::vector<int> t1(3, 10);
    // std::vector<int> t2(t1.begin(), t1.end());

    // std::cout << "t1 " << t1.size() << " " << t1.capacity() << std::endl;
    // for(std::vector<int>::iterator i = t1.begin(); i != t1.end(); i++)
    //     std::cout << *i << ' ';
    // std::cout << '\n';

    // std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;
    // for(std::vector<int>::iterator i = t2.begin(); i != t2.end(); i++)
    //     std::cout << *i << ' ';
    // std::cout << '\n';

    // t2[1] = 1;
    // t2[2] = 5;
    // for(int i = 0; i < 3; i++)
    //     std::cout << t1[i] << " / " << t2[i] << '\n';


    // t2.insert(t2.begin() + 1, t2.rbegin(), t2.rend());
    // std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;
    // t2.push_back(1);
    // std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;

    // for(size_t i = 0; i < t2.size(); i++)
    //     std::cout << t2[i] << ' ';
    // std::cout << '\n';

    // std::vector<int> t3(3, 10);
    // std::vector<int> t4(2, 7);

    // t3.resize(5, 3);
    // t3.swap(t4);

    // for (unsigned i=0; i<t3.size(); i++)
    //     std::cout << t3.at(i) << ' ';
    // std::cout << '\n';
    // std::cout << "front, back " << t3.front() << ' ' << t3.back() << std::endl;
    // std::cout << "t3 " << t3.size() << " " << t3.capacity() << std::endl;
    // for(std::vector<int>::iterator i = t3.begin(); i != t3.end(); i++)
    //     std::cout << *i << ' ';
    // std::cout << '\n';

    // std::vector<int>::reverse_iterator rit = t4.rbegin();
    // std::vector<int>::reverse_iterator ritt = t4.rbegin();

    // ++ritt;
    // std::cout << "reverse comp "<< (rit != ritt) << std::endl;

    // std::cout << "reverse - " << ritt - rit << std::endl;

    // gettimeofday(&t, NULL);
    // end = t.tv_usec;
    // printf("start : %d, end : %d, %d\n", start, end, end - start);
    // }
    struct timeval t;
    unsigned int start;
    unsigned int end;

    gettimeofday(&t, NULL);
    start = t.tv_usec;
    printf("start : %d\n", start);

    ft::vector<int> t1(3, 10);
    ft::vector<int> t2(t1.begin(), t1.end());

    std::cout << "t1 " << t1.size() << " " << t1.capacity() << std::endl;
    for(ft::vector<int>::iterator i = t1.begin(); i != t1.end(); i++)
        std::cout << *i << ' ';
    std::cout << '\n';

    std::cout << "t2 " << t2.size() << " " << t2.capacity() << std::endl;
    for(ft::vector<int>::iterator i = t2.begin(); i != t2.end(); i++)
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

    ft::vector<int> t3(3, 10);
    ft::vector<int> t4(2, 7);

    t3.resize(5, 3);
    t3.swap(t4);

    for (unsigned i=0; i<t3.size(); i++)
        std::cout << t3.at(i) << ' ';
    std::cout << '\n';
    std::cout << "front, back " << t3.front() << ' ' << t3.back() << std::endl;
    std::cout << "t3 " << t3.size() << " " << t3.capacity() << std::endl;
    for(ft::vector<int>::iterator i = t3.begin(); i != t3.end(); i++)
        std::cout << *i << ' ';
    std::cout << '\n';

    ft::vector<int>::reverse_iterator rit = t4.rbegin();
    ft::vector<int>::reverse_iterator ritt = t4.rbegin();

    ++ritt;
    std::cout << "reverse comp "<< (rit != ritt) << std::endl;

    std::cout << "reverse - " << ritt - rit << std::endl;

    gettimeofday(&t, NULL);
    end = t.tv_usec;
    printf("start : %d, end : %d, %d\n", start, end, end - start);
    system("leaks a.out");
    return (0);
}