#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "utils.hpp"
# include "RBT.hpp"
//# include "map.hpp"

namespace ft
{
	template	<typename Tp, bool B>
	class	tree_iterator;

	template <class T, bool B>
    class reverse_map_iterator;

	template <class T, bool B>
    class map_iterator : public tree_iterator<T, B>
    {
		protected:
			typedef map_iterator<T, B>		iterator_;
			typedef tree_iterator<T, B>		t_iter;

        public:
			typedef typename t_iter::value_type		value_type;
			typedef typename t_iter::reference		reference;
			typedef typename t_iter::pointer		pointer;
			typedef typename t_iter::size_type		size_type;


		public:
			map_iterator(void) : t_iter() {};
			map_iterator(const t_iter& p) : t_iter(p) {};
			map_iterator(const map_iterator<T, false> &iter) : t_iter(iter) {};
			template	<class _T>
			map_iterator(const map_iterator<_T, true> &iter) : t_iter(iter) {};
			map_iterator(const reverse_map_iterator<T, false>& riter) : t_iter(riter) {};
			~map_iterator() {};

			iterator_& operator=(const iterator_ &iter)
			{
			 	this->n_ptr = iter.n_ptr;
				return (*this);
			}

			bool	operator==(const map_iterator &iter) const
			{
				return (this->n_ptr == iter.n_ptr);
			}

			bool	operator!=(const map_iterator &iter) const
			{
				return (this->n_ptr != iter.n_ptr);
			}
 
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
				++*static_cast<t_iter*>(this);
				return (*this);
			}

			iterator_& operator--()
			{
				--*static_cast<t_iter*>(this);
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

	// template <class T>
	// bool	operator==(const map_iterator<T, B> &it1, const map_iterator<T, B> &it2)
	// {
	// 	return (it1.n_ptr == it2.n_ptr);
	// }

	// template <class T>
   	// bool operator!=(const map_iterator<T, B>& it1, const map_iterator<T, B>& it2)
	// {
	// 	return (it1.n_ptr != it2.n_ptr);
	// }

    template <class T, bool B>
    class reverse_map_iterator : public tree_iterator<T, B>
    {
		protected:
			typedef reverse_map_iterator<T, B>		iterator_;
			typedef tree_iterator<T, B>	t_iter;

        public:
			typedef typename t_iter::value_type		value_type;
			typedef typename t_iter::reference		reference;
			typedef typename t_iter::pointer		pointer;
			typedef typename t_iter::size_type		size_type;


		public:
			reverse_map_iterator(void) : t_iter() {};
			reverse_map_iterator(const t_iter& p) : t_iter(p) {};
			template	<class _T, bool _B>
			reverse_map_iterator(const reverse_map_iterator<_T, _B> &iter) : t_iter(iter) {};
			~reverse_map_iterator() {};

			reverse_map_iterator<T, B> base() const
			{
				return (*this);
			}

			iterator_& operator=(const iterator_ &iter)
			{
			 	this->n_ptr = iter.n_ptr;
				return (*this);
			}

			bool	operator==(const reverse_map_iterator &iter) const
			{
				return (this->n_ptr == iter.n_ptr);
			}

			bool	operator!=(const reverse_map_iterator &iter) const
			{
				return (this->n_ptr != iter.n_ptr);
			}
 
            reference	operator*() const
			{
				// t_iter base;
				// base = this;
                // return (*(--base));
				return (*(static_cast<t_iter>(--base())));
            }

            pointer		operator->() const
			{
                return (&(*(static_cast<t_iter>(*this))));
            }

			iterator_& operator++()
			{
				--*static_cast<t_iter*>(this);
				return (*this);
			}

			iterator_& operator--()
			{
				++*static_cast<t_iter*>(this);
				return (*this);
			}

			iterator_ operator++(int)
			{
				iterator_	temp = *this;

				--*this;
				return (temp);
			}

			iterator_ operator--(int)
			{
				iterator_	temp = *this;

				++*this;
				return (temp);
			}
    };
	// template <class T>
   	// bool operator!=(const reverse_map_iterator<T, true>& it1, const reverse_map_iterator<T, true>& it2)
	// {
	// 	return (it1.n_ptr != it2.n_ptr);
	// }
}
#endif