#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "RBT.hpp"

namespace ft
{
    template <class T>
    class MapIterator
    {
        public:
			typedef T	value_type;
			typedef T&	reference;
			typedef RBnode<T>*	pointer;

		protected:
			pointer	ptr;

		public:
			MapIterator(void) : ptr(0) {};
			MapIterator(pointer p) : ptr(p) {};
			MapIterator(const MapIterator &iter) {*this = iter;};
			~MapIterator() {};
			
			operator MapIterator<const T> () const
			{
				return (MapIterator<const T>(ptr));
			}
			
			MapIterator& operator=(const MapIterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const MapIterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const MapIterator &iter) const
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

			MapIterator operator+(int n) const
			{
				MapIterator copy(*this);
				copy += n;
				return (copy);
			}

			MapIterator operator-(int n) const
			{
				MapIterator copy(*this);
				copy -= n;
				return (copy);
			}

			MapIterator& operator++()
			{
				ptr = ptr + 1;
				return (*this);
			}

			MapIterator& operator--()
			{
				ptr = ptr - 1;
				return (*this);
			}

			MapIterator operator++(int)
			{
				MapIterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			MapIterator operator--(int)
			{
				MapIterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			int	operator<(const MapIterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const MapIterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const MapIterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const MapIterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			MapIterator& operator+=(const int n)
			{
				ptr = ptr + n;
				return (*this);
			}

			MapIterator& operator-=(const int n)
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
    // class const_MapIterator : public MapIterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_MapIterator(void) {};
	// 		const_MapIterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_MapIterator(const const_MapIterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_MapIterator() {};
	// 		const_MapIterator &operator=(const const_MapIterator &iter)
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
    class ReverseMapIterator
    {
        public:
			typedef T	value_type;
			typedef T&	reference;
			typedef T*	pointer;

		private:
			pointer	ptr;

		public:
			ReverseMapIterator(void) : ptr(0) {}
			ReverseMapIterator(pointer p) : ptr(p) {};
			ReverseMapIterator(const ReverseMapIterator &iter) {*this = iter;};
			~ReverseMapIterator() {};
			
			operator ReverseMapIterator<const T> () const
			{
				return (ReverseMapIterator<const T>(ptr));
			}

			ReverseMapIterator& operator=(const ReverseMapIterator &iter)
			{
				if (this != &iter)
					ptr = iter.ptr;
				return (*this);
			}

			int	operator==(const ReverseMapIterator &iter) const
			{
				if (this->ptr == iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator!=(const ReverseMapIterator &iter) const
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

			ReverseMapIterator operator+(int n) const
			{
				ReverseMapIterator copy(*this);
				copy -= n;
				return (copy);
			}

			ReverseMapIterator operator-(int n) const
			{
				ReverseMapIterator copy(*this);
				copy += n;
				return (copy);
			}

			ReverseMapIterator& operator++()
			{
				ptr = ptr - 1;
				return (*this);
			}

			ReverseMapIterator& operator--()
			{
				ptr = ptr + 1;
				return (*this);
			}

			ReverseMapIterator operator++(int)
			{
				ReverseMapIterator copy(*this);
				ptr = ptr - 1;
				return (copy);
			}

			ReverseMapIterator operator--(int)
			{
				ReverseMapIterator copy(*this);
				ptr = ptr + 1;
				return (copy);
			}

			int	operator<(const ReverseMapIterator &iter) const
			{
				if (this->ptr < iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>(const ReverseMapIterator &iter) const
			{
				if (this->ptr > iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator<=(const ReverseMapIterator &iter) const
			{
				if (this->ptr <= iter.ptr)
					return (1);
				else
					return (0);
			}

			int	operator>=(const ReverseMapIterator &iter) const
			{
				if (this->ptr >= iter.ptr)
					return (1);
				else
					return (0);
			}
			
			ReverseMapIterator& operator+=(const int n)
			{
				ptr = ptr - n;
				return (*this);
			}

			ReverseMapIterator& operator-=(const int n)
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
    // class const_ReverseMapIterator : public ReverseMapIterator<T>
    // {
	// 	public:
	// 		typedef T	value_type;
	// 		typedef T&	reference;
	// 		typedef T*	pointer;
	// 		const_ReverseMapIterator(void) {};
	// 		const_ReverseMapIterator(pointer p)
	// 		{
	// 			this->ptr = p;
	// 		};
	// 		const_ReverseMapIterator(const const_ReverseMapIterator &iter)
	// 		{
	// 			*this = iter;
	// 		};
	// 		~const_ReverseMapIterator() {};
	// 		const_ReverseMapIterator &operator=(const const_ReverseMapIterator &iter)
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