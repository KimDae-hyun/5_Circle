#ifndef VEC_ITERATOR_HPP
# define VEC_ITERATOR_HPP

# include <iostream>
# include "Utils.hpp"

namespace ft
{
    template <class T>
    class VectorIterator
    {
        protected:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;

		protected:
			pointer	ptr;

		public:
			VectorIterator(void) : ptr(0) {};
			VectorIterator(pointer p) : ptr(p) {};
			VectorIterator(const VectorIterator &iter) {*this = iter;};
			~VectorIterator() {};
			operator VectorIterator<const T> () const
			{
				return (VectorIterator<const T>(ptr));
			}
			
			VectorIterator& operator=(const VectorIterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const VectorIterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const VectorIterator &iter) const
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

			VectorIterator operator+(int n) const
			{
				VectorIterator copy(*this);
				copy += n;
				return (copy);
			}

			VectorIterator operator-(int n) const
			{
				VectorIterator copy(*this);
				copy -= n;
				return (copy);
			}

			VectorIterator& operator++()
			{
				ptr = ptr + 1;
				return (*this);
			}

			VectorIterator& operator--()
			{
				ptr = ptr - 1;
				return (*this);
			}

			VectorIterator operator++(int)
			{
				VectorIterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			VectorIterator operator--(int)
			{
				VectorIterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			int	operator<(const VectorIterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const VectorIterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const VectorIterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const VectorIterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			VectorIterator& operator+=(const int n)
			{
				ptr = ptr + n;
				return (*this);
			}

			VectorIterator& operator-=(const int n)
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
    // class const_VectorIterator : public VectorIterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_VectorIterator(void) {};
	// 		const_VectorIterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_VectorIterator(const const_VectorIterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_VectorIterator() {};
	// 		const_VectorIterator &operator=(const const_VectorIterator &iter)
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
    class ReverseIterator
    {
        public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;

		private:
			pointer	ptr;

		public:
			ReverseIterator(void) : ptr(0) {}
			ReverseIterator(pointer p) : ptr(p) {};
			ReverseIterator(const ReverseIterator &iter) {*this = iter;};
			~ReverseIterator() {};
			operator ReverseIterator<const T> () const
			{
				return (ReverseIterator<const T>(ptr));
			}
			
			ReverseIterator& operator=(const ReverseIterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const ReverseIterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const ReverseIterator &iter) const
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

			ReverseIterator operator+(int n) const
			{
				ReverseIterator copy(*this);
				copy -= n;
				return (copy);
			}

			ReverseIterator operator-(int n) const
			{
				ReverseIterator copy(*this);
				copy += n;
				return (copy);
			}

			ReverseIterator& operator++()
			{
				ptr = ptr - 1;
				return (*this);
			}

			ReverseIterator& operator--()
			{
				ptr = ptr + 1;
				return (*this);
			}

			ReverseIterator operator++(int)
			{
				ReverseIterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			ReverseIterator operator--(int)
			{
				ReverseIterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			int	operator<(const ReverseIterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const ReverseIterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const ReverseIterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const ReverseIterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			ReverseIterator& operator+=(const int n)
			{
				ptr = ptr - n;
				return (*this);
			}

			ReverseIterator& operator-=(const int n)
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
    // class const_ReverseIterator : public ReverseIterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_ReverseIterator(void) {};
	// 		const_ReverseIterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_ReverseIterator(const const_ReverseIterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_ReverseIterator() {};
	// 		const_ReverseIterator &operator=(const const_ReverseIterator &iter)
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