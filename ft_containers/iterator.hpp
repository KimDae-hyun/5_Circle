#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>

namespace ft
{
/*	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	};

	template <class Iter>
	class iterators_traits
	{
        public:
            typedef	typename Iter::difference_type		difference_type;
            typedef	typename Iter::value_type			value_type;
            typedef typename Iter::pointer				pointer;
            typedef	typename Iter::reference			reference;
            typedef	typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	class iterators_traits<T*>
	{
        public:
            typedef	ptrdiff_t						difference_type;
            typedef	T								value_type;
            typedef T*								pointer;
            typedef	T&								reference;
            typedef	random_access_iterator_tag		iterator_category;
	};

	template <class T>
	class iterators_traits<const T*>
	{
        public:
            typedef	ptrdiff_t						difference_type;
            typedef	T								value_type;
            typedef const T*						pointer;
            typedef	const T&						reference;
            typedef	random_access_iterator_tag		iterator_category;
	};
*/
    template <class T>
    class vector_iterator
    {
        public:
        	// typedef	ft::iterator<ft::random_access_iterator_tag, T, ptrdiff_t, T*, T&>	iter;
            // typedef	typename iter::value_type											value_type;
            // typedef	typename iter::difference_type										difference_type;
            // typedef typename iter::pointer												pointer;
            // typedef	typename iter::reference											reference;
            // typedef	typename iter::iterator_category									iterator_category;
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;

		private:
			pointer	ptr;

		public:
			vector_iterator(void) : ptr(0) {}
			vector_iterator(pointer p) : ptr(p) {};
			vector_iterator(const vector_iterator &iter) {*this = iter;};
			~vector_iterator() {};
			
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

            reference           operator*() const
			{
                return (*ptr);
            }

            pointer             operator->() const
			{
                return (ptr);
            }

			value_type &operator*(void)
			{
				return (*ptr);
			}

			value_type *operator->(void)
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

	template <class T>
    class const_vector_iterator : public vector_iterator<T>
    {
		public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;
			const_vector_iterator(void) {};
			const_vector_iterator(pointer p)
			{
				this->ptr = p;
			};
			const_vector_iterator(const const_vector_iterator &iter)
			{
				*this = iter;
			};
			~const_vector_iterator() {};
			const_vector_iterator &operator=(const const_vector_iterator &iter)
			{
				if (this != &iter)
					this->ptr = iter.ptr;
				return (*this);
			};
			const value_type &operator*(void)
			{
				return (*this->ptr);
			};
			const value_type &operator[](int n) const
			{
				return (*(this->ptr + n));
			};
	};

}

#endif