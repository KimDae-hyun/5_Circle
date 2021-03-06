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
			bool empty() const {return (cont.empty());}
			size_type size() const {return (cont.size());}
			value_type& top() {return (cont.back());}
			const value_type& top() const {return (cont.back());}
			void push (const value_type& val) {cont.push_back(val);}
			void pop() {cont.pop_back();};
			container_type	getcont() const {return (cont);}
    };

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getcont() == rhs.getcont());
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getcont() != rhs.getcont());
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getcont() < rhs.getcont());
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getcont() <= rhs.getcont());
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getcont() > rhs.getcont());
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getcont() >= rhs.getcont());
	}
}

#endif