#include "vector.hpp"
#include <vector>

#define ns ft

struct A {
	std::string* a;
	A(std::string str);
	A(const A& a);
	A&	operator=(const A& a);
	~A();
};

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
		std::string str = "abcdefg";
		ft::vector<A>	a = ft::vector<A>(4, A(str));
		a.clear();
	}
	ft::vector<int> t;
	system("leaks a.out");
}