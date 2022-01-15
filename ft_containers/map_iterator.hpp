#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "utils.hpp"
# include "RBT.hpp"

namespace ft
{
	template <class T>
	struct RBnode;

    template <class V, class C, class A>
    class RBtree;

	template <class T, bool B>
    class reverse_map_iterator;

	template <typename T, bool B>
	class map_iterator
	{
		 	private:
				typedef map_iterator<T, B>	iterator_;
				typedef RBnode<T>			node_;

			public:
				typedef T					value_type;
				typedef T&					reference;
				typedef T*					pointer;
				typedef std::ptrdiff_t		size_type;

			protected:
				node_ *n_ptr;
				node_ *end;

			public:
				map_iterator(void) : n_ptr(), end() {};
				map_iterator(node_ *node) : n_ptr(node) {};
				//map_iterator(const map_iterator& iter) {*this = iter;};
				template <typename _T, bool _B>
				map_iterator(const map_iterator<_T, _B>& iter) {*this = iter;};
		 		map_iterator(const reverse_map_iterator<T, false>& riter) {*this = riter;};
				~map_iterator() {};

				template <typename _T, bool _B>
				iterator_&	operator= (const map_iterator<_T, _B> &iter)
				{
					this->n_ptr = iter.getptr();
					return (*this);
				}
				
				bool	operator==(const iterator_ &iter) const
				{
					return (this->n_ptr == iter.n_ptr);
				}

				bool	operator!=(const iterator_ &iter) const
				{
					return (this->n_ptr != iter.n_ptr);
				}

				reference	operator*(void)
				{
					return (this->n_ptr->data);
				};

				iterator_&	operator++(void)
				{
					// if ((!n_ptr || !n_ptr->right) && n_ptr->parent)
					// 	return (*this);
					// if (n_ptr->right->data.first)
					// {
					// 	n_ptr = n_ptr->right;
					// 	while (n_ptr->left->data.first)
					// 		n_ptr = n_ptr->left;
					// 	return (*this);
					// }
					// while (n_ptr->parent && n_ptr->parent->right == n_ptr)
					// 	n_ptr = n_ptr->parent;
					// if (n_ptr->parent)
					// 	n_ptr = n_ptr->parent;
					// else
					// 	n_ptr = NULL;
					// return (*this);

					if (n_ptr->right)
					{
						n_ptr = n_ptr->right;
						findleft();
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->right == n_ptr)
						n_ptr = n_ptr->parent;
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					return (*this);
				};

				iterator_	operator++(int)
				{
					iterator_	temp = *this;
					++*this;
					return (temp);
				};

				iterator_&	operator--(void)
				{
					// if (!n_ptr || !n_ptr->left)
					// {
					// 	findright();
					// 	return (*this);
					// }
					// if (n_ptr->left->data.first)
					// {
					// 	n_ptr = n_ptr->left;
					// 	while (n_ptr->right->data.first)
					// 		n_ptr = n_ptr->right;
					// 	return (*this);
					// }
					// while (n_ptr->parent&& n_ptr->parent->left == n_ptr)
					// 	n_ptr = n_ptr->parent;
					// if (n_ptr->parent)
					// 	n_ptr = n_ptr->parent;
					// else
					// 	n_ptr = NULL;
					// return (*this);

					if (n_ptr->left)
					{
						n_ptr = n_ptr->left;
						findright();
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->left == n_ptr)
						n_ptr = n_ptr->parent;
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else
						n_ptr = NULL;
					return (*this);
				};

				iterator_	operator--(int)
				{
					iterator_	temp = *this;
					--*this;
					return (temp);
				};

				pointer		operator->(void) const
				{
					return (&this->n_ptr->data);
				};

				iterator_&	findleft(void)
				{
					if (!n_ptr || !n_ptr->left)
						return (*this);
					if (n_ptr->left && n_ptr->left->left)
					{
						n_ptr = n_ptr->left;
						findleft();
					}
					return (*this);
				}

				iterator_&	findright(void)
				{
					if (!n_ptr || !n_ptr->right)
					{
						if (!end)
							n_ptr = end;
						return (*this);
					}
					else if (n_ptr->right->data.first)
					{
						n_ptr = n_ptr->right;
						findright();
					}
					if (!n_ptr->right)
						end = n_ptr;
					return (*this);
				}

				node_*	getptr() const
				{
					return (n_ptr);
				}
	 };

    template <class T, bool B>
    class reverse_map_iterator : public map_iterator<T, B>
    {
		protected:
			typedef reverse_map_iterator<T, B>		iterator_;
			typedef map_iterator<T, B>	t_iter;

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

			iterator_& operator= (const iterator_ &iter)
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
}
#endif