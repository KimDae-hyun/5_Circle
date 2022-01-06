#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "RBT.hpp"

namespace ft
{
    template <class T>
    class map_iterator
    {
        public:
			typedef T	value_type;
			typedef T&	reference;
			typedef RBnode<T>*	pointer;

		protected:
			pointer	ptr;

		public:
			map_iterator(void) : ptr(0) {};
			map_iterator(pointer p) : ptr(p) {};
			map_iterator(const map_iterator &iter) {*this = iter;};
			~map_iterator() {};
			
			operator map_iterator<const T> () const
			{
				return (map_iterator<const T>(ptr));
			}
			
			map_iterator& operator=(const map_iterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const map_iterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const map_iterator &iter) const
			{
				if (this->ptr != iter.ptr)
					return (1);
				else
					return (0);
			}

            reference	operator*() const
			{
                return (ptr->data);
            }

            pointer		operator->() const
			{
                return (ptr);
            }

			map_iterator operator+(int n) const
			{
				map_iterator copy(*this);
				copy += n;
				return (copy);
			}

			map_iterator operator-(int n) const
			{
				map_iterator copy(*this);
				copy -= n;
				return (copy);
			}

			map_iterator& operator++()
			{
				ptr = ptr + 1;
				return (*this);
			}

			map_iterator& operator--()
			{
				ptr = ptr - 1;
				return (*this);
			}

			map_iterator operator++(int)
			{
				map_iterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			map_iterator operator--(int)
			{
				map_iterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			int	operator<(const map_iterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const map_iterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const map_iterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const map_iterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			map_iterator& operator+=(const int n)
			{
				ptr = ptr + n;
				return (*this);
			}

			map_iterator& operator-=(const int n)
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
    // class const_map_iterator : public map_iterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_map_iterator(void) {};
	// 		const_map_iterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_map_iterator(const const_map_iterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_map_iterator() {};
	// 		const_map_iterator &operator=(const const_map_iterator &iter)
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
    class reverse_map_iterator
    {
        public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;

		private:
			pointer	ptr;

		public:
			reverse_map_iterator(void) : ptr(0) {}
			reverse_map_iterator(pointer p) : ptr(p) {};
			reverse_map_iterator(const reverse_map_iterator &iter) {*this = iter;};
			~reverse_map_iterator() {};
			
			operator reverse_map_iterator<const T> () const
			{
				return (reverse_map_iterator<const T>(ptr));
			}

			reverse_map_iterator& operator=(const reverse_map_iterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const reverse_map_iterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const reverse_map_iterator &iter) const
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

			reverse_map_iterator operator+(int n) const
			{
				reverse_map_iterator copy(*this);
				copy -= n;
				return (copy);
			}

			reverse_map_iterator operator-(int n) const
			{
				reverse_map_iterator copy(*this);
				copy += n;
				return (copy);
			}

			reverse_map_iterator& operator++()
			{
				ptr = ptr - 1;
				return (*this);
			}

			reverse_map_iterator& operator--()
			{
				ptr = ptr + 1;
				return (*this);
			}

			reverse_map_iterator operator++(int)
			{
				reverse_map_iterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			reverse_map_iterator operator--(int)
			{
				reverse_map_iterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			int	operator<(const reverse_map_iterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const reverse_map_iterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const reverse_map_iterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const reverse_map_iterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			reverse_map_iterator& operator+=(const int n)
			{
				ptr = ptr - n;
				return (*this);
			}

			reverse_map_iterator& operator-=(const int n)
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
    // class const_reverse_map_iterator : public reverse_map_iterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_reverse_map_iterator(void) {};
	// 		const_reverse_map_iterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_reverse_map_iterator(const const_reverse_map_iterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_reverse_map_iterator() {};
	// 		const_reverse_map_iterator &operator=(const const_reverse_map_iterator &iter)
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