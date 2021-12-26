#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> > 
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef ft::vector_iterator<pointer>				iterator;
			typedef ft::vector_iterator<const_pointer>			const_iterator;
			//typedef ft::reverse_iterator<iterator>				reverse_iterator;
			//typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			
		private:
			pointer			v_ptr;
			size_type		v_size;
			size_type		v_capacity;
			allocator_type	v_alloc;

			size_type   add_size(size_type new_size);

		//Member Funtion
		public:
		// con/destructor
			vector (const allocator_type& alloc = allocator_type());
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value>::type* = 0);
			vector (const vector &vec);

		// Iterator
			iterator		begin();
			const_iterator	begin() const;
            iterator		end();
            const_iterator	end() const;

		// Capacity
			size_type		size() const;
			size_type		max_size() const;
			size_type       capacity() const;
			void			reserve(size_type n);

		// Modifiers
			void			push_back(const value_type& val);

			
	};
}

namespace ft
{
//Member Funtion

// con/destructor
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc) : v_ptr(NULL), v_size(0), v_capacity(0), v_alloc(alloc) {}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc)\
	: v_ptr(NULL), v_size(n), v_capacity(n), v_alloc(alloc)
	{
		if (n > 0)
		{
			v_ptr = v_alloc.allocate(v_size);
			for (size_type i = 0; i < n; i++)
				v_ptr[i] = val;
		}
	}

	template <class T, class Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector (InputIterator first, InputIterator last, const allocator_type& alloc, typename enable_if<!is_integral<InputIterator>::value>::type*) : v_alloc(alloc)
	{
		v_size = last - first;
		v_capacity = last - first;
		v_ptr = v_alloc.allocate(v_capacity);
		for (int i = 0; first != last; first++)
			v_ptr[i++] = *first;
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(const vector& vec)
	{
		if (this != &vec)
			*this = vec;
	}

// Iterator
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::begin()
	{
        return (iterator(v_ptr));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const
	{
        return (const_iterator(v_ptr));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::end()
	{
        return (iterator(&v_ptr[v_size]));
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const
	{
        return (const_iterator(&v_ptr[v_size]));
    }

// Capacity
	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
	{
		return (v_size);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
	{
		return (v_alloc.max_size());
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
	{
		return (v_capacity);
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::add_size(size_type new_size)
	{
		size_type v_ms = max_size();
		size_type v_cap = capacity();
		if (v_cap >= v_ms / 2)
			return (v_ms);
		if (new_size < v_cap * 2)
			return (v_cap * 2);
		else
			return (new_size);
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::reserve(size_type n)
	{
		if (n > v_capacity)
		{
			pointer v_new = v_alloc.allocate(n);
			for (size_type i = 0; i < v_size; i++)
				v_new[i] = v_ptr[i];
			v_alloc.deallocate(v_ptr, v_capacity);
			v_ptr = v_new;
			v_capacity = n;
		}
	}

// Modifiers
	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& val)
	{
		if (v_size == v_capacity)
			reserve(add_size(v_size + 1));
		v_size++;
		v_ptr[v_size - 1] = val;
	}
}

#endif