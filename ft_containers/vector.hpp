#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "vec_iterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> > 
	class vector
	{
		public:
			typedef T								value_type;
			typedef Alloc							allocator_type;
			typedef T&								reference;
			typedef const T&						const_reference;
			typedef T*								pointer;
			typedef const T *						const_pointer;
			typedef size_t							size_type;
			typedef ft::vector_iterator<T>			iterator;
			typedef ft::vector_iterator<const T>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			
		private:
			pointer			v_ptr;
			size_type		v_size;
			size_type		v_capacity;
			allocator_type	v_alloc;

		//Member Funtion
		public:
		// con/destructor
			explicit vector (const allocator_type& alloc = allocator_type()) : v_ptr(NULL), v_size(0), v_capacity(0), v_alloc(alloc)
			{
				v_ptr = v_alloc.allocate(0);
			}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: v_ptr(NULL), v_size(n), v_capacity(n), v_alloc(alloc)
			{
				if (n > 0)
				{
					v_ptr = v_alloc.allocate(v_size);
					for (size_type i = 0; i < n; i++)
					{
						v_ptr[i] = val;
					}
				}
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			: v_ptr(NULL), v_size(0), v_capacity(0), v_alloc(alloc)
			{
				v_ptr = v_alloc.allocate(0);
				for (; first != last; first++)
            		push_back(*first);
				pointer v_new = v_alloc.allocate(v_size); // capacity등을 최대값과 맞춰주기 위한 과정이 필요
				for (size_type i = 0; i < v_size; i++)
					v_new[i] = v_ptr[i];
				v_alloc.deallocate(v_ptr, v_capacity);
				v_ptr = v_new;
				v_capacity = v_size;
			}
			vector (const vector &vec) : v_size(vec.v_size), v_capacity(vec.v_capacity), v_alloc(vec.v_alloc)
			{
				size_type i;

				v_ptr = v_alloc.allocate(v_capacity);
				i = -1;
				while (++i < v_size)
					v_ptr[i] = vec.v_ptr[i];
			}
			
			~vector(void)
			{
				v_alloc.deallocate(v_ptr, v_capacity);
			};

			vector &operator=(const vector &vec)
			{
				if (v_ptr != 0)
					v_alloc.deallocate(v_ptr, v_capacity);
				v_alloc = vec.v_alloc;
				v_capacity = 0;
				v_size = 0;
				v_ptr = v_alloc.allocate(0);
				assign(vec.begin(), vec.end());
				return (*this);
			};

		// Member Funtion

		// Iterator
			iterator begin()
			{
				return (iterator(v_ptr));
			}

			const_iterator begin() const
			{
				return (const_iterator(v_ptr));
			}

			iterator end()
			{
				return (iterator(v_ptr + v_size));
			}

			const_iterator end() const
			{
				return (const_iterator(v_ptr + v_size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(v_ptr + v_size));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(v_ptr + v_size));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(v_ptr));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(v_ptr));
			}

		// Capacity
			size_type size() const
			{
				return (v_size);
			}

			size_type max_size() const
			{
				return (v_alloc.max_size());
			}

			void resize (size_type n, value_type val = value_type())
			{
				while (n < v_size)
					pop_back();
				if (n > v_size)
				{
					reserve(n);
					for(size_type i = v_size; i < n; i++)
						push_back(val);
				}
			}

			size_type capacity() const
			{
				return (v_capacity);
			}
			
			bool empty() const
			{
				return (v_size == 0);
			}

			void reserve(size_type n)
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

		// Element acces
			reference operator[](size_type n)
			{
				return (v_ptr[n]);
			};

			const_reference operator[](size_type n) const
			{
				return (v_ptr[n]);
			};

			reference at (size_type n)
			{
				if (n >= v_size || n < 0)
					throw std::out_of_range("Out of range!");
				return v_ptr[n];
			}

			const_reference at (size_type n) const
			{
				if (n >= v_size || n < 0)
					throw std::out_of_range("Out of range!");
				return v_ptr[n];
			}

			reference front()
			{
				return (*v_ptr);
			}

			const_reference front() const
			{
				return (*v_ptr);
			}

			reference back()
			{
				return (v_ptr[v_size - 1]);
			}

			const_reference back() const
			{
				return (v_ptr[v_size - 1]);
			}

		// Modifiers
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				clear();
				insert(begin(), first, last);
			}

			void assign(size_type n, const value_type &val)
			{
				clear();
				insert(begin(), n, val);
			}

			void push_back(const value_type& val)
			{
				size_type v_ms = max_size();
				size_type v_cap = capacity();
				size_type new_size = v_size + 1;
				
				if (v_size == v_capacity)
				{
					if (v_cap >= v_ms / 2)
						new_size = v_ms;
					if (new_size < v_cap * 2)
						new_size = v_cap * 2;
					reserve(new_size);
				}
				v_size++;
				v_ptr[v_size - 1] = val;
			}

			void pop_back(void)
			{
				if (v_size)
					v_size--;
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type i = 0;
				iterator iter = begin();
				while (iter + i != position && i < v_size)
					i++;
				if (v_size + 1 > v_capacity)
					reserve(v_capacity + 1);
				size_type j = v_capacity - 1;
				while (j > i)
				{
					v_ptr[j] = v_ptr[j - 1];
					j--;
				}
				v_ptr[i] = val;
				v_size++;
				return (iterator(&v_ptr[i]));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type i = 0;
				iterator iter = begin();
				while (iter + i != position && i < v_size)
					i++;
				if (v_size + n > v_capacity)
					reserve(v_size + n);
				size_type j = i;
				while (j < i + n)
				{
					v_ptr[j + n] = v_ptr[j];
					j++;
				}
				while (i < j)
					v_ptr[i++] = val;
				v_size += n;
				position = &v_ptr[i - 1];
			}

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				while (first != last)
				{
					position = insert(position, *first) + 1;
					++first;
				}
			}

			iterator erase (iterator position)
			{
				iterator present = position;
				while (present + 1 != end())
				{
					*present = *(present + 1);
					present++;
				}
				v_size--;
				return (iterator(position));
			}

			iterator erase (iterator first, iterator last)
			{
				while (first != last)
				{
					erase(first);
					last--;
				}
				return (iterator(first));
			}

			void swap (vector& x)
			{
				pointer			p_tmp;
				size_type		s_tmp;
				size_type		c_tmp;

				p_tmp = v_ptr;
				v_ptr = x.v_ptr;
				x.v_ptr = p_tmp;
				s_tmp = v_size;
				v_size = x.v_size;
				x.v_size = s_tmp;
				c_tmp = v_capacity;
				v_capacity = x.v_capacity;
				x.v_capacity = c_tmp;
			}

			void clear(void)
			{
				erase(begin(), end());
			};

			allocator_type get_allocator() const
			{
				return (allocator_type());
			}
	};

	// Non member funtions
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		size_t i = -1;
		while (++i < lhs.size())
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}
	
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		size_t	size;
		size_t	i;

		if (lhs.size() > rhs.size())
			size = rhs.size();
		else
			size = lhs.size();
		i = -1;
		while (++i < size)
		{
			if (lhs.at(i) != rhs.at(i))
				return (lhs.at(i) < rhs.at(i));
		}
		return (lhs.size() < rhs.size());
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}
	
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		size_t	size;
		size_t	i;

		if (lhs.size() > rhs.size())
			size = rhs.size();
		else
			size = lhs.size();
		i = -1;
		while (++i < size)
		{
			if (lhs.at(i) != rhs.at(i))
				return (lhs.at(i) > rhs.at(i));
		}
		return (lhs.size() > rhs.size());
	}
	
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif