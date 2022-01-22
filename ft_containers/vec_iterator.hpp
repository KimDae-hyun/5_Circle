#ifndef VEC_ITERATOR_HPP
# define VEC_ITERATOR_HPP

# include <iostream>
# include "utils.hpp"
# include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class vector_iterator
    {
		public:
			typedef ft::iterator_traits<T*> v_traits;

        public:
			typedef typename v_traits::value_type		value_type;
			typedef typename v_traits::reference		reference;
			typedef	typename v_traits::pointer			pointer;
			typedef typename v_traits::difference_type	size_type;

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

			bool	operator==(const vector_iterator<const T> &iter) const
			{
				if (this->ptr == iter.getptr())
					return (1);
				else
					return (0);
			}

			bool	operator!=(const vector_iterator<const T> &iter) const
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

			vector_iterator operator+(int n) const
			{
				vector_iterator copy(*this);
				copy.ptr = copy.ptr + n;
				return (copy);
			}

			vector_iterator operator-(int n) const
			{
				vector_iterator copy(*this);
				copy.ptr = copy.ptr - n;
				return (copy);
			}

			size_type operator-(const vector_iterator& it) const
			{
				return (ptr - it.ptr);
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

			bool	operator<(const vector_iterator<const T> &iter) const
			{
				return (this->ptr < iter.getptr());
			}

			bool	operator>(const vector_iterator<const T> &iter) const
			{
				return (this->ptr > iter.getptr());
			}

			bool	operator<=(const vector_iterator<const T> &iter) const
			{
				return (this->ptr <= iter.getptr());
			}

			bool	operator>=(const vector_iterator<const T> &iter) const
			{
				return (this->ptr >= iter.getptr());
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

			pointer	getptr() const
			{
				return (ptr);
			}
    };
	
	template <class T>
	vector_iterator<T> operator+(size_t n, const vector_iterator<T> &it)
	{
		return (it.getptr() + n);
	}

    template <class T>
    class reverse_iterator
    {
		public:
			typedef ft::iterator_traits<T*> v_traits;

        public:
			typedef typename v_traits::value_type		value_type;
			typedef typename v_traits::reference		reference;
			typedef	typename v_traits::pointer			pointer;
			typedef typename v_traits::difference_type	size_type;

		private:
			pointer	ptr;

		public:
			reverse_iterator(void) : ptr(0) {}
			reverse_iterator(const reverse_iterator &iter) {*this = iter;};
			reverse_iterator(const vector_iterator<T> &iter) {ptr = iter.getptr();};
			~reverse_iterator() {};

			operator reverse_iterator<const T> () const
			{
				return (reverse_iterator<const T>(ptr));
			}
			
			vector_iterator<T> base() const
			{
				return (this->ptr);
			}

			reverse_iterator& operator=(const reverse_iterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			bool	operator==(const reverse_iterator<const T> &iter) const
			{
				return (this->ptr == iter.getptr());
			}

			bool	operator!=(const reverse_iterator<const T> &iter) const
			{
				return (this->ptr != iter.getptr());
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

			reverse_iterator operator+(int n) const
			{
				reverse_iterator copy(*this);
				copy.ptr = copy.ptr - n;
				return (copy);
			}

			reverse_iterator operator-(int n) const
			{
				reverse_iterator copy(*this);
				copy.ptr = copy.ptr + n;
				return (copy);
			}

			size_type operator-(const reverse_iterator& it) const
			{
				return (it.ptr - ptr);
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

			bool	operator<(const reverse_iterator<const T> &iter) const
			{
				return (this->ptr > iter.getptr());
			}

			bool	operator>(const reverse_iterator<const T> &iter) const
			{
				return (this->ptr < iter.getptr());
			}

			bool	operator<=(const reverse_iterator<const T> &iter) const
			{
				return (this->ptr >= iter.getptr());
			}

			bool	operator>=(const reverse_iterator<const T> &iter) const
			{
				return (this->ptr <= iter.getptr());
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
				return (*(*this + n));
			}
			
			pointer	getptr() const
			{
				return (ptr);
			}
    };
	
	template <class T>
	reverse_iterator<T> operator+(size_t n, const reverse_iterator<T> &it)
	{
		return reverse_iterator<T>(it.getptr() - n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::size_type operator- ( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.getptr() - rhs.getptr());
	}

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.getptr() == rhs.getptr());
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (!(lhs.getptr() == rhs.getptr()));
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.getptr() > rhs.getptr());
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.getptr() >= rhs.getptr());
	}

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.getptr() < rhs.getptr());
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.getptr() <= rhs.getptr());
	}	
}

#endif