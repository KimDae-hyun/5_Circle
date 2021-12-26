#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <limits>
# include "iterator.hpp"
//# include "utils.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> > 
	class vector
	{
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef T*										pointer;
			typedef const T *								const_pointer;
			typedef size_t									size_type;
			typedef ft::vector_iterator<T>					iterator;
			typedef ft::const_vector_iterator<T>			const_iterator;
			//typedef ft::reverse_iterator<iterator>				reverse_iterator;
			//typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			
		private:
			pointer			v_ptr;
			size_type		v_size;
			size_type		v_capacity;
			allocator_type	v_alloc;

		//Member Funtion
		public:
		// con/destructor
			vector (const allocator_type& alloc = allocator_type()) : v_ptr(NULL), v_size(0), v_capacity(0), v_alloc(alloc)
			{
				v_ptr = v_alloc.allocator(0);
				std::cout << "__1"<< std::endl;
			}
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: v_ptr(NULL), v_size(n), v_capacity(n), v_alloc(alloc)
			{
				std::cout << "__2"<< std::endl;
				if (n > 0)
				{
					v_ptr = v_alloc.allocate(v_size);
					for (size_type i = 0; i < n; i++)
					{
						v_ptr[i] = val;
						std::cout << v_ptr[i] << std::endl;
					}
				}
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			: v_ptr(NULL), v_size(0), v_capacity(0), v_alloc(alloc)
			{
				std::cout << "__3" << std::endl;
				v_ptr = v_alloc.allocate(0);
				assign(first, last);
			}
			vector (const vector &vec)
			{
				std::cout << "__4"<< std::endl;
				if (this != &vec)
					*this = vec;
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

			reference operator[](size_type n)
			{
				return (v_ptr[n]);
			};
			const_reference operator[](size_type n) const
			{
				return (v_ptr[n]);
			};
		//Member Funtion

		// con/destructor
		/*	template <class T, class Alloc>
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
			}*/

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
				return (iterator(&v_ptr[v_size]));
			}

			const_iterator end() const
			{
				return (const_iterator(&v_ptr[v_size]));
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

			size_type capacity() const
			{
				return (v_capacity);
			}

			size_type add_size(size_type new_size)
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

		// Modifiers
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				std::cout << "here??" << std::endl;
				clear();
				insert(begin(), first, last);
			}

			void assign(size_type n, const value_type &val)
			{
				clear();
				insert(begin(), n, val);
			};

			void push_back(const value_type& val)
			{
				if (v_size == v_capacity)
					reserve(add_size(v_size + 1));
				v_size++;
				v_ptr[v_size - 1] = val;
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
				std::cout << "i = "<< i << " j = "<< j << " val = " << val << std::endl;
				while (j > i)
				{
					v_ptr[j] = v_ptr[j - 1];
					j--;
					std::cout << "v_ptr[j] "<< v_ptr[j] << std::endl;
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
    		void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_type i = 0;
				iterator iter = begin();
				while (iter + i != position && i < v_size)
					i++;
				while (first != last)////
				{
					std::cout << "insert " << v_ptr[i] << " i = " << i << std::endl;
					position = insert(position, v_ptr[i++]) + 1;
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
				while (first != last)////
				{
					erase(first);
					last--;
				}
				return (iterator(first));
			}

			void clear(void)
			{
				erase(begin(), end());
			};
	};
}

#endif