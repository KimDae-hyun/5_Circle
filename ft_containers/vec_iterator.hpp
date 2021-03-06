#ifndef VEC_ITERATOR_HPP
# define VEC_ITERATOR_HPP

# include "utils.hpp"
# include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class vector_iterator : public ft::iterator< random_access_iterator_tag, T >
    {
        public:
			typedef typename vector_iterator::iterator_category	iterator_category;
			typedef typename vector_iterator::value_type		value_type;
			typedef typename vector_iterator::reference			reference;
			typedef	typename vector_iterator::pointer			pointer;
			typedef typename vector_iterator::difference_type	size_type;

		protected:
			pointer	ptr;

		public:
			vector_iterator(void) : ptr(0) {};
			vector_iterator(pointer p) : ptr(p) {};
			vector_iterator(const vector_iterator &iter) : ptr(iter.getptr()) {};
			template<class Tp>
			vector_iterator(const vector_iterator<Tp> &iter) : ptr(iter.getptr()) {};
			~vector_iterator() {};
			
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
}

#endif