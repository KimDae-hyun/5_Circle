#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "RBT.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	struct RBnode;

    template <class V, class C, class A>
    class RBtree;

	template <typename T>
	class const_map_iterator;

	template <typename T>
	class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef map_iterator<T>			iterator_;
			typedef RBnode<T>				node_type;

		public:
			typedef bidirectional_iterator_tag  iterator_category;
			typedef T                           value_type;
			typedef value_type&                 reference;
			typedef std::ptrdiff_t              difference_type;
			typedef T*                          pointer;

			protected:
				node_type *n_ptr;

				node_type* min_search(node_type *node)
				{
					if (node->left == NULL)
						return (node);
					return (min_search(node->left));
				}
				
				node_type* max_search(node_type *node)
				{
					if (node->right == NULL)
						return (node);
					return (max_search(node->right));
				}

			public:
				map_iterator(void) : n_ptr() {};
				map_iterator(node_type *node) : n_ptr(node) {};
				map_iterator(const iterator_& iter) : n_ptr(iter.getptr()) {};
				virtual ~map_iterator() {};

				iterator_&	operator= (const iterator_ &iter)
				{
					if (this != &iter)
						this->n_ptr = iter.getptr();
					return (*this);
				}
				
				bool	operator==(const iterator_ &iter) const
				{
					return (this->n_ptr == iter.getptr());
				}

				bool	operator!=(const iterator_ &iter) const
				{
					return (this->n_ptr != iter.getptr());
				}

				bool	operator==(const const_map_iterator<T> &iter) const
				{
					return (this->n_ptr == iter.getptr());
				}

				bool	operator!=(const const_map_iterator<T> &iter) const
				{
					return (this->n_ptr != iter.getptr());
				}

				iterator_&	operator++(void)
				{
					if (n_ptr->parent == NULL)
						n_ptr = NULL;
					if (n_ptr->right != NULL)
					{
						n_ptr = min_search(n_ptr->right);
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
					if (n_ptr->left != NULL)
					{
						n_ptr = max_search(n_ptr->left);
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

                reference operator*() const
				{
                    return (n_ptr->data);
                }

				pointer		operator->() const
				{
					return (&n_ptr->data);
				};

				node_type*	getptr() const
				{
					return (n_ptr);
				}
	 };

	template <typename T>
	class const_map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef const_map_iterator<T>		iterator_;
			typedef RBnode<T>					node_type;

		public:
			typedef bidirectional_iterator_tag  iterator_category;
			typedef T                           value_type;
			typedef const value_type&           reference;
			typedef std::ptrdiff_t              difference_type;
			typedef const T*                    pointer;

			protected:
				node_type *n_ptr;

				node_type* min_search(node_type *node)
				{
					if (node->left == NULL)
						return (node);
					return (min_search(node->left));
				}
				
				node_type* max_search(node_type *node)
				{
					if (node->right == NULL)
						return (node);
					return (max_search(node->right));
				}

			public:
				const_map_iterator(void) : n_ptr() {};
				const_map_iterator(node_type *node) : n_ptr(node) {};
				const_map_iterator(const iterator_& iter) : n_ptr(iter.getptr()) {};
				const_map_iterator(const map_iterator<T>& iter) : n_ptr(iter.getptr()) {};
				~const_map_iterator() {};

				iterator_&	operator= (const iterator_ &iter)
				{
					if (this != &iter)
						this->n_ptr = iter.getptr();
					return (*this);
				}
				
				bool	operator==(const iterator_ &iter) const
				{
					return (this->n_ptr == iter.getptr());
				}

				bool	operator!=(const iterator_ &iter) const
				{
					return (this->n_ptr != iter.getptr());
				}

				bool	operator==(const map_iterator<T> &iter) const
				{
					return (this->n_ptr == iter.getptr());
				}

				bool	operator!=(const map_iterator<T> &iter) const
				{
					return (this->n_ptr != iter.getptr());
				}

				iterator_&	operator++(void)
				{
					if (n_ptr->parent == NULL)
						n_ptr = NULL;
					if (n_ptr->right != NULL)
					{
						n_ptr = min_search(n_ptr->right);
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
					if (n_ptr->left != NULL)
					{
						n_ptr = max_search(n_ptr->left);
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

                reference operator*() const
				{
                    return (n_ptr->data);
                }

				pointer	operator->() const
				{
					return (&n_ptr->data);
				};

				node_type*	getptr() const
				{
					return (n_ptr);
				}
	};
}

#endif