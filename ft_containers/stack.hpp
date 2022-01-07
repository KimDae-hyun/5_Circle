#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
		public:
        	typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type	cont;

		public:
			explicit stack (const container_type& ctnr = container_type()) : cont(ctnr) {};
			// vec_iterator.hpp 161 컴파일 에러 -> g++이 아닌 clang++로 컴파일
			// segmentation fault -> vector의 복사생성자 수정
			bool empty() const {return (cont.empty());}
			size_type size() const {return (cont.size());}
			value_type& top() {return (cont.back());}
			const value_type& top() const {return (cont.back());}
			void push (const value_type& val) {cont.push_back(val);}
			void pop() {cont.pop_back();};
    };

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont == rhs.cont);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont != rhs.cont);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont < rhs.cont);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont <= rhs.cont);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont > rhs.cont);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cont >= rhs.cont);
	}
}

#endif