#include <deque>
#include <stack>
#include "stack.hpp"

int main(void)
{
    std::deque<int> t1(3, 10);
    ft::vector<int> t2(2, 20);

    std::stack<int> first (t1);
    ft::stack<int> second (t2);

    std::cout << first.empty() << std::endl;
    std::cout << second.empty() << std::endl;

}