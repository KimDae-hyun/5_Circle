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

	template <typename T>
	class const_map_iterator;

	template <class T>
    class reverse_map_iterator;

    template <class T>
    class reverse_const_iterator;

	template <typename T>
	class map_iterator
	{
		 	private:
				typedef map_iterator<T>	iterator_;
				typedef RBnode<T>			node_;

			public:
				typedef T					value_type;
				typedef T&					reference;
				typedef T*					pointer;
				typedef std::ptrdiff_t		size_type;

			protected:
				node_ *n_ptr;

			public:
				map_iterator(void) : n_ptr() {};
				map_iterator(node_ *node) : n_ptr(node) {};
				map_iterator(const iterator_& iter) {*this = iter;};
				//map_iterator(const map_iterator<T>& iter) {this->n_ptr = iter.getptr();};
				template <typename _T>
				map_iterator(const map_iterator<_T>& iter) {*this = iter;};
		 		map_iterator(const reverse_map_iterator<T>& riter) {*this = riter;};
				~map_iterator() {};

				iterator_&	operator= (const iterator_ &iter)
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

                reference operator*() const{
                    return this->n_ptr->data;
                }

				iterator_&	operator++(void)
				{
					if (!n_ptr || n_ptr->right == n_ptr->nil)
						return (*this);
					if (n_ptr->right->data.first)
					{
						n_ptr = n_ptr->right;
						while (n_ptr->left->data.first)
							n_ptr = n_ptr->left;
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->right == n_ptr)
						n_ptr = n_ptr->parent;
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else
						n_ptr = n_ptr->nil;
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
					if (!n_ptr || n_ptr->left == n_ptr->nil || n_ptr->left == NULL)
						return (*this);
					if (n_ptr->left->data.first)
					{
						n_ptr = n_ptr->left;
						while (n_ptr->right->data.first)
							n_ptr = n_ptr->right;
						return (*this);
					}
					while (n_ptr->parent&& n_ptr->parent->left == n_ptr)
						n_ptr = n_ptr->parent;
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else
						n_ptr = n_ptr->nil;
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
					if (!n_ptr || n_ptr->left == n_ptr->nil)
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
					if (!n_ptr || n_ptr->right == n_ptr->nil)
						return (*this);
					else if (n_ptr->right->data.first)
					{
						n_ptr = n_ptr->right;
						findright();
					}
					return (*this);
				}

				node_*	getptr() const
				{
					return (n_ptr);
				}
	 };

	template <typename T>
	class const_map_iterator
	{
		 	private:
				typedef const_map_iterator<T>	iterator_;
				typedef RBnode<T>			node_;

			public:
				typedef T					value_type;
				typedef T&					reference;
				typedef T*					pointer;
				typedef std::ptrdiff_t		size_type;

			protected:
				node_ *n_ptr;

			public:
				const_map_iterator(void) : n_ptr() {};
				const_map_iterator(node_ *node) : n_ptr(node) {};
				const_map_iterator(const iterator_& iter) {this->n_ptr = iter.getptr();};
				const_map_iterator(iterator_& iter) {this->n_ptr = iter.getptr();};
                const_map_iterator(const map_iterator<T>& iter) {this->n_ptr = iter.getptr();};
				template <typename _T>
				const_map_iterator(const const_map_iterator<_T>& iter) {*this = iter;};
		 		const_map_iterator(const reverse_const_iterator<T>& riter) {*this = riter;};
				~const_map_iterator() {};

				iterator_&	operator= (const iterator_ &iter)
				{
					this->n_ptr = iter.getptr();
					return (*this);
				}


				bool	operator==(const iterator_ &iter)
				{
					return (this->n_ptr == iter.n_ptr);
				}

				bool	operator!=(const iterator_ &iter)
				{
					return (this->n_ptr != iter.n_ptr);
				}

				reference	operator*(void) 
				{
					return (this->n_ptr->data);
				};

				reference	operator*(void) const 
				{
					return (this->n_ptr->data);
				};

				pointer		operator->(void) const
				{
					return (&this->n_ptr->data);
				};

				iterator_&	operator++(void)
				{
					if (!n_ptr || n_ptr->right == n_ptr->nil)
						return (*this);
					if (n_ptr->right->data.first)
					{
						n_ptr = n_ptr->right;
						while (n_ptr->left->data.first)
							n_ptr = n_ptr->left;
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->right == n_ptr)
						n_ptr = n_ptr->parent;
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else
						n_ptr = n_ptr->nil;
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
					if (!n_ptr || n_ptr->left == n_ptr->nil || n_ptr->left == NULL)
						return (*this);
					if (n_ptr->left->data.first)
					{
						n_ptr = n_ptr->left;
						while (n_ptr->right->data.first)
							n_ptr = n_ptr->right;
						return (*this);
					}
					while (n_ptr->parent&& n_ptr->parent->left == n_ptr)
						n_ptr = n_ptr->parent;
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else
						n_ptr = n_ptr->nil;
					return (*this);
				};

				iterator_	operator--(int)
				{
					iterator_	temp = *this;
					--*this;
					return (temp);
				};

				iterator_&	findleft(void)
				{
					if (!n_ptr || n_ptr->left == n_ptr->nil)
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
					if (!n_ptr || n_ptr->right == n_ptr->nil)
						return (*this);
					else if (n_ptr->right->data.first)
					{
						n_ptr = n_ptr->right;
						findright();
					}
					return (*this);
				}

				node_*	getptr() const
				{
					return (n_ptr);
				}
	};

    template <class T>
    class reverse_map_iterator : public map_iterator<T>
    {
		protected:
			typedef reverse_map_iterator<T>		iterator_;
			typedef map_iterator<T>	t_iter;

        public:
			typedef typename t_iter::value_type		value_type;
			typedef typename t_iter::reference		reference;
			typedef typename t_iter::pointer		pointer;
			typedef typename t_iter::size_type		size_type;


		public:
			reverse_map_iterator(void) : t_iter() {};
			reverse_map_iterator(const t_iter& p) : t_iter(p) {};
			reverse_map_iterator(const reverse_map_iterator &iter) {*this = iter;};
			template	<class _T>
			reverse_map_iterator(const reverse_map_iterator<_T> &iter) : t_iter(iter) {};
			~reverse_map_iterator() {};

			reverse_map_iterator<T> base() const
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

       template <class T>
    class reverse_const_iterator : public const_map_iterator<T>
    {
		protected:
			typedef reverse_const_iterator<T>		iterator_;
			typedef const_map_iterator<T>	t_iter;

        public:
			typedef typename t_iter::value_type		value_type;
			typedef typename t_iter::reference		reference;
			typedef typename t_iter::pointer		pointer;
			typedef typename t_iter::size_type		size_type;


		public:
			reverse_const_iterator(void) : t_iter() {};
			reverse_const_iterator(const t_iter& p) : t_iter(p) {};
			reverse_const_iterator(const reverse_const_iterator &iter) {*this = iter;};
			template	<class _T>
			reverse_const_iterator(const reverse_const_iterator<_T> &iter) : t_iter(iter) {};
			~reverse_const_iterator() {};

			reverse_const_iterator<T> base() const
			{
				return (*this);
			}

			iterator_& operator= (const iterator_ &iter)
			{
			 	this->n_ptr = iter.n_ptr;
				return (*this);
			}

			bool	operator==(const reverse_const_iterator &iter) const
			{
				return (this->n_ptr == iter.n_ptr);
			}

			bool	operator!=(const reverse_const_iterator &iter) const
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