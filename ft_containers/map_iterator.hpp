#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "utils.hpp"
# include "RBT.hpp"
# include "map.hpp"

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
			map_iterator(iterator_ &iter) : t_iter(iter) {};
			template	<class _T>
			map_iterator(const map_iterator<const _T> &iter) : t_iter(iter) {};
			map_iterator(const reverse_map_iterator<iterator_>& riter) : t_iter(riter) {};
			~map_iterator() {};

			operator map_iterator<const T> () const
			{
				return (map_iterator<const T>());
			}

			iterator_& operator=(const iterator_ &iter)
			{
				// if (this != &iter)
				 	this->n_ptr = iter.n_ptr;
				// *static_cast<t_iter*>(this) = static_cast<t_iter>(iter);
				return (*this);
			}

			bool	operator==(const map_iterator &iter) const
			{
				return (this->n_ptr == iter.n_ptr);
			}

			bool	operator!=(const map_iterator &iter) const
			{
				// std::cout << "this " << this->n_ptr << " / iter " << iter.n_ptr << std::endl;
				// std::cout << (this->n_ptr != iter.n_ptr) << " ??" << std::endl;
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
				// if (this->n_ptr->right->data.first)
				// {
				// 	this->n_ptr = this->n_ptr->right;
				// 	while (this->n_ptr->left->data.first)
				// 		this->n_ptr = this->n_ptr->left;
				// 	return (*this);
				// }
				// while (this->n_ptr->parent && this->n_ptr->parent->right == this->n_ptr)
				// 	this->n_ptr = this->n_ptr->parent;
				// if (this->n_ptr->parent)
				// 	this->n_ptr = this->n_ptr->parent;
				// else
				// {
				// 	this->n_ptr->nil->parent = this->n_ptr;
				// 	this->n_ptr = this->n_ptr->nil;
				// }
				++*static_cast<t_iter*>(this);
				return (*this);
			}

			iterator_& operator--()
			{
				// if (this->n_ptr->left->data.first)
				// {
				// 	this->n_ptr = this->n_ptr->left;
				// 	while (this->n_ptr->right->data.first)
				// 		this->n_ptr = this->n_ptr->right;
				// 	return (*this);
				// }
				// while (this->n_ptr->parent&& this->n_ptr->parent->left == this->n_ptr)
				// 	this->n_ptr = this->n_ptr->parent;
				// if (this->n_ptr->parent)
				// 	this->n_ptr = this->n_ptr->parent;
				// else
				// 	this->n_ptr = this->n_ptr->nil;
				--*static_cast<t_iter*>(this);
				return (*this);
			}

			iterator_ operator++(int)
			{
				iterator_	temp = *this;

				// ++*this;
				// if (this->n_ptr->right->data.first)
				// {
				// 	this->n_ptr = this->n_ptr->right;
				// 	while (this->n_ptr->left->data.first)
				// 		this->n_ptr = this->n_ptr->left;
				// 	return (temp);
				// }

				// while (this->n_ptr->parent && this->n_ptr->parent->right == this->n_ptr)
				// 	this->n_ptr = this->n_ptr->parent;
				// if (this->n_ptr->parent)
				// 	this->n_ptr = this->n_ptr->parent;
				// else
				// 	this->n_ptr = this->n_ptr->nil;
				++*this;
				return (temp);
			}

			iterator_ operator--(int)
			{
				iterator_	temp = *this;

				--*this;
				// if (this->n_ptr->left->data.first)
				// {
				// 	this->n_ptr = this->n_ptr->left;
				// 	while (this->n_ptr->right->data.first)
				// 		this->n_ptr = this->n_ptr->right;
				// 	return (temp);
				// }
				// while (this->n_ptr->parent&& this->n_ptr->parent->left == this->n_ptr)
				// 	this->n_ptr = this->n_ptr->parent;
				// if (this->n_ptr->parent)
				// 	this->n_ptr = this->n_ptr->parent;
				// else
				// 	this->n_ptr = this->n_ptr->nil;
				return (temp);
			}
    };

	// template <class T>
	// bool	operator==(const map_iterator<T> &it1, const map_iterator<T> &it2)
	// {
	// 	return (it1.n_ptr == it2.n_ptr);
	// }

	// template <class T>
   	// bool operator!=(const map_iterator<T>& it1, const map_iterator<T>& it2)
	// {
	// 	return (it1.n_ptr != it2.n_ptr);
	// }

    template <class T>
    class reverse_map_iterator : public tree_iterator<T>
    {
		protected:
			typedef reverse_map_iterator<T>		iterator_;
			typedef tree_iterator<T>	t_iter;

        public:
			typedef typename t_iter::value_type		value_type;
			typedef typename t_iter::reference		reference;
			typedef typename t_iter::pointer		pointer;
			typedef typename t_iter::size_type		size_type;


		public:
			reverse_map_iterator(void) : t_iter() {};
			reverse_map_iterator(const t_iter& p) : t_iter(p) {};
			reverse_map_iterator(iterator_ &iter) : t_iter(iter) {};
			template	<class _T>
			reverse_map_iterator(const reverse_map_iterator<const _T> &iter) : t_iter(iter) {};
			~reverse_map_iterator() {};

			operator reverse_map_iterator<const T> () const
			{
				return (reverse_map_iterator<const T>());
			}
			
			reverse_map_iterator<T> base() const
			{
				return (*this);
			}

			reverse_map_iterator& operator=(const reverse_map_iterator &iter)
			{
			 	this->n_ptr = iter.n_ptr;
				return (*this);
			}

			bool	operator==(const reverse_map_iterator<T> &iter) const
			{
				return (this->n_ptr == iter.n_ptr);
			}

			bool	operator!=(const reverse_map_iterator<T> &iter) const
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

			reverse_map_iterator& operator++()
			{
				--*static_cast<t_iter*>(this);
				return (*this);
			}

			reverse_map_iterator& operator--()
			{
				++*static_cast<t_iter*>(this);
				return (*this);
			}

			reverse_map_iterator operator++(int)
			{
				iterator_	temp = *this;

				++*this;
				return (temp);
			}

			reverse_map_iterator operator--(int)
			{
				iterator_	temp = *this;

				++*this;
				return (temp);
			}

			reference	operator[](int n) const
			{
				return (*(*this + n));
			}
    };
	template <class T>
   	bool operator!=(const reverse_map_iterator<const T>& it1, const reverse_map_iterator<const T>& it2)
	{
		return (it1.n_ptr != it2.n_ptr);
	}
}
#endif