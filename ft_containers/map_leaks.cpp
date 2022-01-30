#include "map.hpp"
#include <map>

#define ns ft

struct A {
	std::string* a;
    A();
	A(std::string str);
	A(const A& a);
	A&	operator=(const A& a);
	~A();
};

A::A() {
	a = new std::string("test");
}

A::A(std::string str) {
	a = new std::string(str);
}

A::A(const A& a) {
	this->a = new std::string(*a.a);
}

A& A::operator=(const A& a) {
	delete this->a;
	this->a = new std::string(*a.a);
	return *this;
}

A::~A() {
	delete a;
}

int main() {
	{
		std::string str = "asdfasdfsadfs";
		ft::map<int, A>	a = ft::map<int, A>();
        a.insert(ft::make_pair(3, A(str)));
        a.insert(ft::make_pair(8, A(str)));
        a.insert(ft::make_pair(2, A(str)));
        a.insert(ft::make_pair(7, A(str)));
        a.insert(ft::make_pair(5, A(str)));
        a.insert(ft::make_pair(1, A(str)));
        a.insert(ft::make_pair(6, A(str)));
        a.insert(ft::make_pair(4, A(str)));
		a.clear();

		a = ft::map<int, A>();


	}
    
	ft::map<int, A> t;
	system("leaks a.out");
}