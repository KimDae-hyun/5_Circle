#ifndef VEC_ITERATOR_HPP
# define VEC_ITERATOR_HPP

# include <iostream>
# include "utils.hpp"

namespace ft
{
    template <class T>
    class vector_iterator
    {
        protected:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;

		protected:
			pointer	ptr;

		public:
			vector_iterator(void) : ptr(0) {};
			vector_iterator(pointer p) : ptr(p) {};
			vector_iterator(const vector_iterator &iter) {*this = iter;};
			~vector_iterator() {};
			operator vector_iterator<const T> () const
			{
				return (vector_iterator<const T>(ptr));
			}
			
			vector_iterator& operator=(const vector_iterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const vector_iterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const vector_iterator &iter) const
			{
				if (this->ptr != iter.ptr)
					return (1);
				else
					return (0);
			}

            reference	operator*() const
			{
                return (*ptr);
            }

            pointer		operator->() const
			{
                return (ptr);
            }

			vector_iterator operator+(int n) const
			{
				vector_iterator copy(*this);
				copy += n;
				return (copy);
			}

			vector_iterator operator-(int n) const
			{
				vector_iterator copy(*this);
				copy -= n;
				return (copy);
			}

			vector_iterator& operator++()
			{
				ptr = ptr + 1;
				return (*this);
			}

			vector_iterator& operator--()
			{
				ptr = ptr - 1;
				return (*this);
			}

			vector_iterator operator++(int)
			{
				vector_iterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			vector_iterator operator--(int)
			{
				vector_iterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			int	operator<(const vector_iterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const vector_iterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const vector_iterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const vector_iterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			vector_iterator& operator+=(const int n)
			{
				ptr = ptr + n;
				return (*this);
			}

			vector_iterator& operator-=(const int n)
			{
				ptr = ptr - n;
				return (*this);
			}

			reference	operator[](int n) const
			{
				return (*(ptr + n));
			}
    };

	// template <class T>
    // class const_vector_iterator : public vector_iterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_vector_iterator(void) {};
	// 		const_vector_iterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_vector_iterator(const const_vector_iterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_vector_iterator() {};
	// 		const_vector_iterator &operator=(const const_vector_iterator &iter)
	// 		{
	// 			if (this != &iter)
	// 				this->ptr = iter.ptr;
	// 			return (*this);
	// 		};
	// 		const value_type &operator*(void)
	// 		{
	// 			return (*this->ptr);
	// 		};
	// 		const value_type &operator[](int n) const
	// 		{
	// 			return (*(this->ptr + n));
	// 		};
	// };

    template <class T>
    class reverse_iterator
    {
        public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;

		private:
			pointer	ptr;

		public:
			reverse_iterator(void) : ptr(0) {}
			reverse_iterator(pointer p) : ptr(p) {};
			reverse_iterator(const reverse_iterator &iter) {*this = iter;};
			~reverse_iterator() {};
			operator reverse_iterator<const T> () const
			{
				return (reverse_iterator<const T>(ptr));
			}
			
			reverse_iterator& operator=(const reverse_iterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const reverse_iterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const reverse_iterator &iter) const
			{
				if (this->ptr != iter.ptr)
					return (1);
				else
					return (0);
			}

            reference	operator*() const
			{
                return (*ptr);
            }

            pointer		operator->() const
			{
                return (ptr);
            }

			reverse_iterator operator+(int n) const
			{
				reverse_iterator copy(*this);
				copy -= n;
				return (copy);
			}

			reverse_iterator operator-(int n) const
			{
				reverse_iterator copy(*this);
				copy += n;
				return (copy);
			}

			reverse_iterator& operator++()
			{
				ptr = ptr - 1;
				return (*this);
			}

			reverse_iterator& operator--()
			{
				ptr = ptr + 1;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			int	operator<(const reverse_iterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const reverse_iterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const reverse_iterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const reverse_iterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			reverse_iterator& operator+=(const int n)
			{
				ptr = ptr - n;
				return (*this);
			}

			reverse_iterator& operator-=(const int n)
			{
				ptr = ptr + n;
				return (*this);
			}

			reference	operator[](int n) const
			{
				return (*(ptr - n));
			}
    };

	// template <class T>
    // class const_reverse_iterator : public reverse_iterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_reverse_iterator(void) {};
	// 		const_reverse_iterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_reverse_iterator(const const_reverse_iterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_reverse_iterator() {};
	// 		const_reverse_iterator &operator=(const const_reverse_iterator &iter)
	// 		{
	// 			if (this != &iter)
	// 				this->ptr = iter.ptr;
	// 			return (*this);
	// 		};
	// 		const value_type &operator*(void)
	// 		{
	// 			return (*this->ptr);
	// 		};
	// 		const value_type &operator[](int n) const
	// 		{
	// 			return (*(this->ptr - n));
	// 		};
	// };
}

#endif