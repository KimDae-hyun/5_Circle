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
			typedef T*	pointer;
			typedef std::ptrdiff_t	size_type;

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

			bool	operator==(const map_iterator<const T> &iter) const
			{
				if (this->ptr == iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator!=(const map_iterator<const T> &iter) const
			{
				if (this->ptr != iter.getptr())
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

			map_iterator operator+(int n) const
			{
				map_iterator copy(*this);
				copy.ptr = copy.ptr + n;
				return (copy);
			}

			map_iterator operator-(int n) const
			{
				map_iterator copy(*this);
				copy.ptr = copy.ptr - n;
				return (copy);
			}

			size_type operator-(const map_iterator& it) const
			{
				return (ptr - it.ptr);
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

			bool	operator<(const map_iterator<const T> &iter) const
			{
				if (this->ptr < iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator>(const map_iterator<const T> &iter) const
			{
				if (this->ptr > iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator<=(const map_iterator<const T> &iter) const
			{
				if (this->ptr <= iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator>=(const map_iterator<const T> &iter) const
			{
				if (this->ptr >= iter.getptr())
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

			pointer	getptr() const
			{
				return (ptr);
			}
    };
	
	template <class T>
	map_iterator<T> operator+(size_t n, const map_iterator<T> &it)
	{
		return (it.getptr() + n);
	}

    template <class T>
    class reverse_map_iterator
    {
        public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;
			typedef std::ptrdiff_t	size_type;

		private:
			pointer	ptr;

		public:
			reverse_map_iterator(void) : ptr(0) {}
			reverse_map_iterator(const reverse_map_iterator &iter) {*this = iter;};
			reverse_map_iterator(const map_iterator<T> &iter)
			{
				ptr = iter.getptr();
			};
			~reverse_map_iterator() {};

			operator reverse_map_iterator<const T> () const
			{
				return (reverse_map_iterator<const T>(ptr));
			}
			
			map_iterator<T> base() const
			{
				return (this->ptr);
			}

			reverse_map_iterator& operator=(const reverse_map_iterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			bool	operator==(const reverse_map_iterator<const T> &iter) const
			{
				if (this->ptr == iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator!=(const reverse_map_iterator<const T> &iter) const
			{
				if (this->ptr != iter.getptr())
					return (1);
				else
					return (0);
			}

            reference	operator*()
			{
				pointer base;
				base = ptr;
                return (*(--base));
            }

            pointer		operator->()
			{
                return (&(operator*()));
            }

			reverse_map_iterator operator+(int n) const
			{
				reverse_map_iterator copy(*this);
				copy.ptr = copy.ptr - n;
				return (copy);
			}

			reverse_map_iterator operator-(int n) const
			{
				reverse_map_iterator copy(*this);
				copy.ptr = copy.ptr + n;
				return (copy);
			}

			size_type operator-(const reverse_map_iterator& it) const
			{
				return (it.ptr - ptr);
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

			bool	operator<(const reverse_map_iterator<const T> &iter) const
			{
				if (this->ptr > iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator>(const reverse_map_iterator<const T> &iter) const
			{
				if (this->ptr < iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator<=(const reverse_map_iterator<const T> &iter) const
			{
				if (this->ptr >= iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator>=(const reverse_map_iterator<const T> &iter) const
			{
				if (this->ptr <= iter.getptr())
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
				return (*(*this + n));
			}
			
			pointer	getptr() const
			{
				return (ptr);
			}
    };
	
	template <class T>
	reverse_map_iterator<T> operator+(size_t n, const reverse_map_iterator<T> &it)
	{
		return reverse_map_iterator<T>(it.getptr() - n);
	}
}
#endif