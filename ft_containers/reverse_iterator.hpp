#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class reverse_iterator
    {
		public:
			typedef T 									iterator_type;
			typedef ft::iterator_traits<T>				traits;
			typedef	typename traits::iterator_category	iterator_category;
			typedef	typename traits::value_type			value_type;
			typedef	typename traits::difference_type	size_type;
			typedef	typename traits::pointer			pointer;
			typedef	typename traits::reference			reference;

		private:
			iterator_type	_iter;

		public:
			reverse_iterator() : _iter() {};
			reverse_iterator (iterator_type iter) : _iter(iter) {};
			template<class Tp>
  			reverse_iterator (const reverse_iterator<Tp>& iter) : _iter(iter.base()) {};
			~reverse_iterator() {};

			iterator_type base() const
			{
				return (_iter);
			}

			template<class Tp>
			reverse_iterator& operator=(const reverse_iterator<Tp> &iter)
			{
				_iter = iter.base();
				return (*this);
			}

			bool	operator==(const reverse_iterator<const T> &iter) const
			{
				return (this->_iter == iter.base());
			}

			bool	operator!=(const reverse_iterator<const T> &iter) const
			{
				return (this->_iter != iter.base());
			}

			reference 			operator*() const
			{
				iterator_type tmp;

				tmp = base();
				return (*(--tmp));
			}

			pointer 			operator->() const
			{
				iterator_type tmp;

				tmp = base();
				return (&(*--tmp));
			}

			reverse_iterator operator+(int n) const
			{
				reverse_iterator copy(*this);
				copy._iter = copy._iter - n;
				return (copy);
			}

			reverse_iterator operator-(int n) const
			{
				reverse_iterator copy(*this);
				copy._iter = copy._iter + n;
				return (copy);
			}

			size_type operator-(const reverse_iterator& it) const
			{
				return (it._iter - _iter);
			}

			reverse_iterator& operator++()
			{
				--_iter;
				return (*this);
			}

			reverse_iterator& operator--()
			{
				++_iter;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator copy(*this);
				--_iter;
				return (copy);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator copy(*this);
				++_iter;
				return (copy);
			}

			bool	operator<(const reverse_iterator<const T> &iter) const
			{
				return (this->_iter > iter.base());
			}

			bool	operator>(const reverse_iterator<const T> &iter) const
			{
				return (this->_iter < iter.base());
			}

			bool	operator<=(const reverse_iterator<const T> &iter) const
			{
				return (this->_iter >= iter.base());
			}

			bool	operator>=(const reverse_iterator<const T> &iter) const
			{
				return (this->_iter <= iter.base());
			}
			
			reverse_iterator& operator+=(const int n)
			{
				_iter = _iter - n;
				return (*this);
			}

			reverse_iterator& operator-=(const int n)
			{
				_iter = _iter + n;
				return (*this);
			}

			reference	operator[](int n) const
			{
				return (*(*this + n));
			}
    };
	
	template <class T>
	reverse_iterator<T> operator+(size_t n, const reverse_iterator<T> &it)
	{
		return reverse_iterator<T>(it.base() - n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::size_type operator- ( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (!(lhs.base() == rhs.base()));
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename iter1, typename iter2>
	bool operator == (const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename iter1, typename iter2>
	bool operator != (const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename iter1, typename iter2>
	bool operator < (const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename iter1, typename iter2>
	bool operator <= (const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs)
	{
		return !(lhs > rhs);
	}
	
	template <typename iter1, typename iter2>
	bool operator >	(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs)
	{
		return (rhs < lhs);
	}

	template <typename iter1, typename iter2>
	bool operator >= (const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif