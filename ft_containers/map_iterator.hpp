#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "utils.hpp"
# include "RBT.hpp"

namespace ft
{
	template	<typename Tp>
	class	tree_iterator;

	template <class T>
    class reverse_map_iterator;

	template <class T>
    class map_iterator : public tree_iterator<T>
    {
		protected:
			typedef map_iterator<T>		iterator_;
			typedef tree_iterator<T>	t_iter;

        public:
			typedef typename t_iter::value_type		value_type;
			typedef typename t_iter::reference		reference;
			typedef typename t_iter::pointer			pointer;
			typedef typename t_iter::size_type		size_type;


		public:
			map_iterator(void) : t_iter() {};
			map_iterator(const t_iter& p) : t_iter(p) {};
			map_iterator(const iterator_ &iter) : t_iter(iter) {};
			template	<class _T>
			map_iterator(const map_iterator<const _T> &iter) : t_iter(iter) {};
			map_iterator(const reverse_map_iterator<iterator_>& riter) : t_iter(riter) {};
			~map_iterator() {};

			// operator iterator_<const T> () const
			// {
			// 	return (iterator_<const T>(ptr));
			// }
			
			iterator_& operator=(const iterator_ &iter)
			{
				// if (this != &iter)
				// 	ptr = iter.ptr;
				*static_cast<t_iter*>(this) = static_cast<t_iter>(iter);
				return (*this);
			}

			// bool	operator==(const map_iterator &iter) const
			// {
			// 	if (*this == iter)
			// 		return (1);
			// 	else
			// 		return (0);
			// }

			// bool	operator!=(const map_iterator &iter) const
			// {
			// 	if (*this != iter)
			// 		return (1);
			// 	else
			// 		return (0);
			// }
 
            reference	operator*() const
			{
				return (*(static_cast<t_iter>(*this)));
            }

            pointer		operator->() const
			{
                return (&(*(static_cast<t_iter>(*this))));
            }

			iterator_& operator++()
			{
				++(*static_cast<t_iter*>(this));
				return (*this);
			}

			iterator_& operator--()
			{
				--(*static_cast<t_iter*>(this));
				return (*this);
			}

			iterator_ operator++(int)
			{
				iterator_	temp = *this;
				++*this;
				return (temp);
			}

			iterator_ operator--(int)
			{
				iterator_	temp = *this;
				--*this;
				return (temp);
			}
    };

	template <class T>
	bool	operator==(const map_iterator<T> &it1, const map_iterator<T> &it2)
	{
		return (it1.n_ptr == it2.n_ptr);
	}

	template <class T>
   	bool operator!=(const map_iterator<T>& it1, const map_iterator<T>& it2)
	{
		return (it1.n_ptr != it2.n_ptr);
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
			reverse_map_iterator(const ft::map_iterator<T> &iter)
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

			// bool	operator!=(const reverse_map_iterator<const T> &iter) const
			// {
			// 	if (this->ptr != iter.getptr())
			// 		return (1);
			// 	else
			// 		return (0);
			// }

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

			reference	operator[](int n) const
			{
				return (*(*this + n));
			}
    };
	
	template <class T>
   	bool operator!=(const reverse_map_iterator<T>& it1, const reverse_map_iterator<T>& it2)
	{
		return (it1.n_ptr != it2.n_ptr);
	}
}
#endif