#include "map.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <map>
int main()
{
    {
        std::cout << "namespace ft의 결과" << std::endl;
        std::__1::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        ft::map<int, int> test;
        for (int  i =0; i < 500000 ; i++){
            test.insert(ft::make_pair(i, i));
        }
        std::cout << "reach" << std::endl;
        test.find(499999);
        // Some computation here
        std::__1::chrono::system_clock::time_point end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
              << "[elapsed time: " << elapsed_seconds.count() << "s]\n";
        std::cout << std::endl;
        std::cout << std::endl;

    }

    {
        std::cout << "namespace std의 결과" << std::endl;
        std::__1::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        std::map<int, int> test;
        for (int  i =0; i < 500000 ; i++){
            test.insert(std::make_pair(i, i));
        }
        std::cout << "reach" << std::endl;
        test.find(499999);
        // Some computation here
        std::__1::chrono::system_clock::time_point end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time)
              << "[elapsed time: " << elapsed_seconds.count() << "s]\n";
    }
}