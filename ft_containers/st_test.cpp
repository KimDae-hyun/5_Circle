#include <deque>
#include <stack>
#include "Stack.hpp"

int main()
{
    std::deque<int> t1(3, 10);
    ft::Vector<int> t2(2, 20);

    std::cout << "std stack\n";
    std::stack<int> first (t1);

    std::cout << first.top() << " " << first.size() << std::endl;
    first.push(1);
    std::cout << first.top() << " " << first.size() << std::endl;
    first.pop();
    std::cout << first.top() << " " << first.size() << std::endl;

    std::cout << "ft stack\n";
    ft::Stack<int> second (t2);
    
    std::cout << second.top() << " " << second.size() << std::endl;
    second.push(0);
    std::cout << second.top() << " " << second.size() << std::endl;
    second.pop();
    std::cout << second.top() << " " << second.size() << std::endl;

    std::cout << first.empty() << std::endl;
    std::cout << second.empty() << std::endl;
}