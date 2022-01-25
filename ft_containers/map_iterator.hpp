#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "utils.hpp"
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

	template <class T>
    class reverse_map_iterator;

    template <class T>
    class reverse_const_iterator;

	template <typename T>
	class map_iterator
	{
		public:
			typedef ft::iterator_traits<T*> m_traits;
			typedef map_iterator<T>			iterator_;
			typedef RBnode<T>				node_;

		public:
			typedef typename m_traits::value_type		value_type;
			typedef typename m_traits::reference		reference;
			typedef	typename m_traits::pointer			pointer;
			typedef typename m_traits::difference_type	size_type;

			protected:
				node_ *n_ptr;

			public:
				map_iterator(void) : n_ptr() {};
				map_iterator(node_ *node) : n_ptr(node) {};
				map_iterator(const iterator_& iter) {*this = iter;};
				map_iterator(const const_map_iterator<T>& iter) {this->n_ptr = iter.getptr();};
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
					return (this->n_ptr == iter.getptr());
				}

				bool	operator!=(const iterator_ &iter) const
				{
					return (this->n_ptr != iter.getptr());
				}

				reference	operator*(void)
				{
					return (this->n_ptr->data);
				};

                reference operator*() const
				{
                    return this->n_ptr->data;
                }

				iterator_&	operator++(void)
				{
					node_ *tmp = n_ptr;

					if (!n_ptr || (!n_ptr->parent && !n_ptr->right && !n_ptr->left)) // 클리어 된 경우 (root == NULL)  '||' 은 tree 기본 생성자 호출 후 end()인 경우 root와 nil 구분을 위해 추가  
						return (*this);
					if (n_ptr->right && n_ptr->right->parent && n_ptr->right->parent->data.first == n_ptr->data.first)
					{
						n_ptr = n_ptr->right;
						while (n_ptr->left && n_ptr->left->parent && n_ptr->left->parent->data.first == n_ptr->data.first)
						{
							if (!n_ptr->left->left) // 마지막 값에서 더 내려가는거 방지
								break;
							n_ptr = n_ptr->left;
						}
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->right == n_ptr)
					{
						n_ptr = n_ptr->parent;
						if (!n_ptr->parent)
						{ //n_ptr이 마지막 값인 경우 nil의 부모가 마지막 값을 가리켜서 --를 가능하게 해준다. findright().getptr() 필요한가?
							n_ptr = tmp; 
							n_ptr->right->parent = n_ptr;
							n_ptr = n_ptr->right;
							return (*this);
						}
					}
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else if (!n_ptr->parent) 
					{
						n_ptr = tmp;
						n_ptr->right->parent = n_ptr;
						n_ptr = n_ptr->right;
						return (*this);
					}
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
					node_ *tmp = n_ptr;
					
					if (!n_ptr)
						return (*this);
					if (!n_ptr->left && !n_ptr->right)
					{
						n_ptr = n_ptr->parent;
						n_ptr->right->parent = NULL;
						return (*this);
					}
					if (n_ptr->left && n_ptr->left->parent)
					{
						n_ptr = n_ptr->left;
						while (n_ptr->right && n_ptr->right->parent)
							n_ptr = n_ptr->right;
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->left == n_ptr)
					{
						n_ptr = n_ptr->parent;
						if (!n_ptr->parent) //findright().getptr() 필요한가?
						{
							n_ptr = tmp;
							n_ptr->left = NULL;
							n_ptr->left->parent = n_ptr; //제일 작은 값에서 --시 segfault유발
							return (*this);
						}
					}
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else if (!n_ptr->parent) //findright().getptr() 필요한가?
					{
						n_ptr = tmp;
						n_ptr->left = NULL;
						n_ptr->left->parent = n_ptr;
						return (*this);
					}
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
					if (n_ptr->left->left)
					{
						n_ptr = n_ptr->left;
						findleft();
					}
					return (*this);
				}

				iterator_&	findright(void)
				{
					if (!n_ptr|| !n_ptr->right)
					 	return (*this);
					/*if (!n_ptr || n_ptr->right == n_ptr->nil)
						return (*this);
					else */if (n_ptr->right->right)
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
		public:
			typedef ft::iterator_traits<T*> m_traits;
			typedef const_map_iterator<T>	iterator_;
			typedef RBnode<T>			node_;

		public:
			typedef typename m_traits::value_type		value_type;
			typedef typename m_traits::reference		reference;
			typedef	typename m_traits::pointer			pointer;
			typedef typename m_traits::difference_type	size_type;

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
				
				bool	operator==(const iterator_ &iter) const
				{
					return (this->n_ptr == iter.getptr());
				}

				bool	operator!=(const iterator_ &iter) const
				{
					return (this->n_ptr != iter.getptr());
				}

				reference	operator*(void)
				{
					return (this->n_ptr->data);
				};

                reference operator*() const
				{
                    return this->n_ptr->data;
                }

				iterator_&	operator++(void)
				{
					node_ *tmp = n_ptr;

					if (!n_ptr || (!n_ptr->parent && !n_ptr->right && !n_ptr->left)) // 클리어 된 경우 (root == NULL)  '||' 은 tree 기본 생성자 호출 후 end()인 경우 root와 nil 구분을 위해 추가  
						return (*this);
					if (n_ptr->right && n_ptr->right->parent && n_ptr->right->parent->data.first == n_ptr->data.first)
					{
						n_ptr = n_ptr->right;
						while (n_ptr->left && n_ptr->left->parent && n_ptr->left->parent->data.first == n_ptr->data.first)
						{
							if (!n_ptr->left->left) // 마지막 값에서 더 내려가는거 방지
								break;
							n_ptr = n_ptr->left;
						}
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->right == n_ptr)
					{
						n_ptr = n_ptr->parent;
						if (!n_ptr->parent)
						{ //n_ptr이 마지막 값인 경우 nil의 부모가 마지막 값을 가리켜서 --를 가능하게 해준다. findright().getptr() 필요한가?
							n_ptr = tmp; 
							n_ptr->right->parent = n_ptr;
							n_ptr = n_ptr->right;
							return (*this);
						}
					}
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else if (!n_ptr->parent) 
					{
						n_ptr = tmp;
						n_ptr->right->parent = n_ptr;
						n_ptr = n_ptr->right;
						return (*this);
					}
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
					node_ *tmp = n_ptr;
					
					if (!n_ptr)
						return (*this);
					if (!n_ptr->left && !n_ptr->right)
					{
						n_ptr = n_ptr->parent;
						n_ptr->right->parent = NULL;
						return (*this);
					}
					if (n_ptr->left && n_ptr->left->parent)
					{
						n_ptr = n_ptr->left;
						while (n_ptr->right && n_ptr->right->parent)
							n_ptr = n_ptr->right;
						return (*this);
					}
					while (n_ptr->parent && n_ptr->parent->left == n_ptr)
					{
						n_ptr = n_ptr->parent;
						if (!n_ptr->parent) //findright().getptr() 필요한가?
						{
							n_ptr = tmp;
							n_ptr->left = NULL;
							n_ptr->left->parent = n_ptr; //제일 작은 값에서 --시 segfault유발
							return (*this);
						}
					}
					if (n_ptr->parent)
						n_ptr = n_ptr->parent;
					else if (!n_ptr->parent) //findright().getptr() 필요한가?
					{
						n_ptr = tmp;
						n_ptr->left = NULL;
						n_ptr->left->parent = n_ptr;
						return (*this);
					}
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
					if (n_ptr->left && n_ptr->left->parent)
					{
						n_ptr = n_ptr->left;
						findleft();
					}
					return (*this);
				}

				iterator_&	findright(void)
				{
					if (!n_ptr|| !n_ptr->right)
					 	return (*this);
					if (n_ptr->right && n_ptr->right->parent)
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
    class reverse_map_iterator
    {
		public:
			typedef ft::iterator_traits<T*> m_traits;
			typedef reverse_map_iterator<T>	iterator_;
			typedef RBnode<T>				node_;

		public:
			typedef typename m_traits::value_type		value_type;
			typedef typename m_traits::reference		reference;
			typedef	typename m_traits::pointer			pointer;
			typedef typename m_traits::difference_type	size_type;
		
			protected:
				node_ *n_ptr;

		public:
			reverse_map_iterator(void){};
			reverse_map_iterator(const iterator_& p) : n_ptr(p.getptr()) {};
			reverse_map_iterator(const map_iterator<T> &iter) : n_ptr(iter.getptr()) {};
			template	<class _T>
			reverse_map_iterator(const reverse_map_iterator<const _T> &iter) : iterator_(iter) {};
			~reverse_map_iterator() {};

			map_iterator<T> base() const
			{
				return (this->n_ptr);
			}

			iterator_& operator= (const iterator_ &iter)
			{
			 	this->n_ptr = iter.getptr();
				return (*this);
			}

			bool	operator==(const reverse_map_iterator &iter) const
			{
				return (this->n_ptr == iter.getptr());
			}

			bool	operator!=(const reverse_map_iterator &iter) const
			{
				return (this->n_ptr != iter.getptr());
			}
 
            reference	operator*() const
			{
	            return (*(--base()));
            }

            pointer		operator->() const
			{
                return (&(*base()));
            }

			iterator_& operator++()
			{
				node_ *tmp = n_ptr;
				
				if (n_ptr->left && n_ptr->left->parent)
				{
					n_ptr = n_ptr->left;
					while (n_ptr->right && n_ptr->right->parent)
						n_ptr = n_ptr->right;
					return (*this);
				}
				while (n_ptr->parent && n_ptr->parent->left == n_ptr)
				{
					n_ptr = n_ptr->parent;
					if (!n_ptr->parent && findleft().getptr() == tmp)
					{
						n_ptr = tmp->left;
						return (*this);
					}
				}
				if (n_ptr->parent)
					n_ptr = n_ptr->parent;
				return (*this);
			}

			iterator_& operator--()
			{ 
				if (n_ptr->right && n_ptr->right->parent)
				{
					n_ptr = n_ptr->right;
					while (n_ptr->left && n_ptr->left->parent)
						n_ptr = n_ptr->left;
					return (*this);
				}
				while (n_ptr->parent && n_ptr->parent->right == n_ptr)
					n_ptr = n_ptr->parent;
				if (n_ptr->parent)
					n_ptr = n_ptr->parent;
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

			iterator_&	findleft(void)
			{
				if (!n_ptr || !n_ptr->left)
					return (*this);
				if (n_ptr->left && n_ptr->left->parent)
				{
					n_ptr = n_ptr->left;
					findleft();
				}
				return (*this);
			}

			iterator_&	findright(void)
			{
				if (!n_ptr|| !n_ptr->right)
					return (*this);
				if (n_ptr->right && n_ptr->right->parent)
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
    class reverse_const_iterator
    {
		public:
			typedef ft::iterator_traits<T*>		m_traits;
			typedef reverse_const_iterator<T>	iterator_;
			typedef RBnode<T>					node_;

		public:
			typedef typename m_traits::value_type		value_type;
			typedef typename m_traits::reference		reference;
			typedef	typename m_traits::pointer			pointer;
			typedef typename m_traits::difference_type	size_type;

			protected:
				node_ *n_ptr;

		public:
			reverse_const_iterator(void) : iterator_() {};
			reverse_const_iterator(const iterator_& p) : n_ptr(p.getptr()) {};
			reverse_const_iterator(const map_iterator<T> &iter) : n_ptr(iter.getptr()) {};
			reverse_const_iterator(const const_map_iterator<T> &iter) : n_ptr(iter.getptr()) {};
			reverse_const_iterator(const reverse_map_iterator<T> &iter) : n_ptr(iter.getptr()) {};
			template	<class _T>
			reverse_const_iterator(const reverse_const_iterator<const _T> &iter) : n_ptr(iter.getptr()) {};
			~reverse_const_iterator() {};

			map_iterator<T> base() const
			{
				return (this->n_ptr);
			}

			iterator_& operator= (const iterator_ &iter)
			{
			 	this->n_ptr = iter.getptr();
				return (*this);
			}

			bool	operator==(const reverse_const_iterator &iter) const
			{
				return (this->n_ptr == iter.getptr());
			}

			bool	operator!=(const reverse_const_iterator &iter) const
			{
				return (this->n_ptr != iter.getptr());
			}
 
            reference	operator*() const
			{
				return (*(--base()));
            }

            pointer		operator->() const
			{
                return (&(operator*()));
            }

			iterator_& operator++()
			{
				node_ *tmp = n_ptr;
				
				if (n_ptr->left && n_ptr->left->parent)
				{
					n_ptr = n_ptr->left;
					while (n_ptr->right && n_ptr->right->parent)
						n_ptr = n_ptr->right;
					return (*this);
				}
				while (n_ptr->parent&& n_ptr->parent->left == n_ptr)
				{
					n_ptr = n_ptr->parent;
					if (!n_ptr->parent && findleft().getptr() == tmp)
					{
						n_ptr = tmp->left;
						return (*this);
					}
				}
				if (n_ptr->parent)
					n_ptr = n_ptr->parent;
				return (*this);
			}

			iterator_& operator--()
			{
				if (n_ptr->right && n_ptr->right->parent)
				{
					n_ptr = n_ptr->right;
					while (n_ptr->left && n_ptr->left->parent)
						n_ptr = n_ptr->left;
					return (*this);
				}
				while (n_ptr->parent && n_ptr->parent->right == n_ptr)
					n_ptr = n_ptr->parent;
				if (n_ptr->parent)
					n_ptr = n_ptr->parent;
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

			iterator_&	findleft(void)
			{
				if (!n_ptr || !n_ptr->left)
				 	return (*this);
				if (n_ptr->left && n_ptr->left->parent)
				{
					n_ptr = n_ptr->left;
					findleft();
				}
				return (*this);
			}

			iterator_&	findright(void)
			{
				if (!n_ptr|| !n_ptr->right)
					return (*this);
				if (n_ptr->right && n_ptr->right->parent)
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
}

#endif