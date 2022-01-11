#ifndef RBT_HPP
# define RBT_HPP

# include "utils.hpp"
# include "map_iterator.hpp"

namespace ft
{
	template <class T>
	class map_iterator;

	template <class T, class A = std::allocator<T> >
	struct RBnode
	{
		typedef T		value_type;
		typedef A		allocator_type;
		typedef RBnode	node;

		static allocator_type	n_alloc;
		
		RBnode			*parent;
		RBnode			*left;
		RBnode			*right;
		bool 			color; // RED = true, BLACK = false
		value_type		data;

		RBnode(value_type& other) : left(NULL), right(NULL), parent(NULL), data(other) {}

		RBnode(const node& n) : parent(n.parent), left(n.left), right(n.right), color(n.color), data(n.data) {}

		~RBnode() {} 

		// node& operator =(const node& n)
		// {
		// 	if (*this != n)
		// 	{
		// 		this->left = n.left;
		// 		this->right = n.right;
		// 		this->parent = n.parent;
		// 		this->value = n.value;
		// 		this->data = n.data;
		// 	}
		// 	return (*this);
		// }

		// bool operator ==(const RBnode &node)
		// {
		// 	if (this->value == node->value)
		// 		return (true);
		// 	return (false);
		// }

		// bool operator !=(const RBnode &node)
		// {
		// 	return (!(*this == node));
		// }
	};

	template <typename T>
	class tree_iterator
	{
		 	private:
				typedef tree_iterator<T>	iterator_;
				typedef RBnode<T>			node_;

			public:
				typedef T					value_type;
				typedef T&					reference;
				typedef T*					pointer;
				typedef std::ptrdiff_t		size_type;

				node_ *n_ptr;

			public:
				tree_iterator(void) : n_ptr() {};
				tree_iterator(const iterator_& iter) : n_ptr(iter.n_ptr) {};
				tree_iterator(node_ *node) : n_ptr(node) {};
				template <typename Tp>
				tree_iterator(tree_iterator<const Tp>& iter) : n_ptr(iter.n_ptr) {};
			
			iterator_&	operator=(iterator_ const& iter)
			{
				this->n_ptr = iter.n_ptr;
				return (*this);
			}

			// template	<typename _Tp>
			// iterator_&	operator=(tree_iterator<_Tp> const& iter)
			// {
			// 	this->n_ptr = ((iterator_*)(&iter))->n_ptr;
			// 	return (*this);
			// };

			reference	operator*(void)
			{
				return (this->n_ptr->data);
			};

			iterator_&	operator++(void)
			{
				if (n_ptr->right)
				{
					n_ptr = n_ptr->right;
					findleft();
					return (*this);
				}
				while (n_ptr->parent && n_ptr->parent->left != n_ptr)
					n_ptr = n_ptr->parent;
				if (n_ptr->parent)
					n_ptr = n_ptr->parent;
				else
					n_ptr = NULL;
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
				if (n_ptr->left)
				{
					n_ptr = n_ptr->left;
					findright();
					return (*this);
				}
				while (n_ptr->parent && n_ptr->parent->right != n_ptr)
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
				if (n_ptr->left)
				{
					n_ptr = n_ptr->left;
					findleft();
				}
				return (*this);
			}

			iterator_&	findright(void)
			{
				if (n_ptr->right)
				{
					n_ptr = n_ptr->right;
					findright();
				}
				return (*this);
			}	
	 };

    template <class V, class C, class A>
    class RBtree
    {
        public:
			typedef V					value_type;
			typedef C					value_compare;
			typedef A					allocator_type;
			typedef V&										reference;
			typedef const V&								const_reference;
			typedef V*										pointer;
			typedef const V*								const_pointer;
			// typedef std::ptrdiff_t								size_type;
			typedef tree_iterator<value_type>				iterator;
			typedef tree_iterator<const value_type>			const_iterator;
			typedef reverse_map_iterator<value_type>		reverse_iterator;
			typedef reverse_map_iterator<const value_type>	const_reverse_iterator;
			typedef size_t										size_type;
			typedef RBtree										tree;
			typedef RBnode<V>									node;
			typedef typename A::template rebind<node>::other	node_allocator;

		private:
			value_compare	t_comp;
			allocator_type	t_alloc;
			node_allocator	n_alloc;
			size_type		t_size;
			node			*root;

		public:
			RBtree(value_compare const& comp = value_compare(), allocator_type const& alloc = allocator_type(), node_allocator const& node_a = node_allocator())
			: t_comp(comp), t_alloc(alloc), n_alloc(node_a), t_size(0)
			{
				root = n_alloc.allocate(1);
				root->left = NULL;
				root->right = NULL;
				root->parent = NULL;
				root->color = true;
			}
			
			RBtree(const RBtree& tree) : t_comp(tree.comp), t_alloc(tree.t_alloc), n_alloc(tree.n_alloc), t_size(tree.t_size)
			{
				root = n_alloc.allocate(1);
				root->parent = NULL;
				root->color = true;
				if (t_size != 0)
				{
					node *root = n_alloc.allcate(1);
					root->parent = this->root;
					this->root->left = root;
					this->root->right = root;
					copytree(&root, tree.root.left);
				}
				else
				{
					root->left = NULL;
					root->right = NULL;
				}	
			}
			~RBtree() {};

			void	copyTree(node** n_this, node* const& n_that)
			{
				t_alloc.construct(n_this->data, n_that->data);

				if ((*n_that)->left == NULL)
					(*n_this)->left = NULL;
				else if ((*n_that)->left != NULL)
				{
					(*n_this)->left = n_alloc.allocate(1);
					(*n_this)->left->parent = (*n_this);
					copyTree((*n_this)->left, n_that->left);
				}
				if ((*n_that)->right == NULL)
					(*n_this)->right = NULL;
				else if ((*n_that)->right != NULL)
				{
					(*n_this)->right = n_alloc.allocate(1);
					(*n_this)->right->parent = (*n_this);
					copyTree((*n_this)->right, n_that->right);
				}
			};

			pair<iterator, bool>	insert(const value_type& val)
			{
				return (insertnode(val));
			};

			iterator	insert(iterator position, const value_type& val)
			{
				node*	prev = (node*)position.n_ptr;
				node*	next = (node*)(++position).n_ptr;

				if ((position.n_ptr != end().n_ptr) && (t_size && prev->data <= val && next->data >= val))
				{
					node*	n_new;
					n_new = create(val);
					if (!prev->right)
					{
						prev->right = n_new;
						n_new->parent = prev;
					}
					else
					{
						next->left = n_new;
						n_new->parent = next;
					}
				}
				return (insertnode(val).first);
			};

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				iterator it = begin();
				for (InputIterator itt = first; itt != last; ++itt)
					it = insert(it, *itt);
			};

			node *create(value_type data)
			{
				node* node = n_alloc.allocate(1);

				t_alloc.construct(&node->data, data);
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				node->color = true;
				++t_size;
				return (node);
			}

			pair<iterator, bool> insertnode(value_type val)
			{
				node *node = create(val);

				t_alloc.construct(&node->data, val);
				node->color = true;
				node->left = NULL;
				node->right = NULL;
				if (t_size == 1)
					root = node;
				insertvalue(root, node);
				insertcheck(root, node);
				return (pair<iterator, bool>(iterator(node), true));
			}

			void insertvalue(node *parent, node *node)
			{
				if (parent->data.first < node->data.first)
				{
					if (parent->right == NULL)
					{
						parent->right = node;
						node->parent = parent;
					}
					else
						insertvalue(parent->right, node);
				}
				else if (parent->data.first > node->data.first)
				{
					if (parent->left == NULL)
					{
						parent->left = node;
						node->parent = parent;
					}
					else
						insertvalue(parent->left, node);
				}
			}

			void insertcheck(node *root, node *now)
			{
				//부모가 red이면 자식은 black
				while (now != root && now->parent->color == true && now->parent->parent)
				{
					//부모 노드가 조부모의 왼쪽 자식인 경우
					if (now->parent == now->parent->parent->left)
					{
						node *uncle = now->parent->parent->right;

						//부모, 삼촌 노드가 red
						if (uncle && uncle->color == true)
						{ 
							now->parent->color = false;
							uncle->color = false;
							now->parent->parent->color = true;
							now = now->parent->parent;
						}
						else //부모는 red, 삼촌은 black
						{ 
							// 부모의 오른쪽으로 삽입되는 경우
							if (now == now->parent->right)
							{ 
								now = now->parent;
								leftrotate(root, now);
							}

							// 부모의 왼쪽으로 삽입되는 경우
							now->parent->color = false;
							now->parent->parent->color = true;
							rightrotate(root, now->parent->parent);
						}
					}
					else
					{ //부모 노드가 조부모의 오른쪽 자식인 경우 왼쪽과 반대로
						node *uncle = now->parent->parent->left;

						if (uncle && uncle->color == true)
						{
							now->parent->color = false;
							uncle->color = false;
							now->parent->parent->color = true;
							now = now->parent->parent;
						}
						else
						{
							if (now == now->parent->left)
							{
								now = now->parent;
								rightrotate(root, now);
							}
							now->parent->color = false;
							now->parent->parent->color = true;
							leftrotate(root, now->parent->parent);
						}
					}
				}
				root->color = false;
				// root 노드는 항상 black
			}

			node* minsearch(node *node)
			{
				if (node == NULL)
					return (node->parent);
				if (node->left == NULL && node->right == NULL)
					return (node);
				if (node->left == NULL)
					return (node);
				if (node->right == NULL)
					return (node->left);
				return (minsearch(node->right));
			}

			node *search(node *node, value_type data)
			{
				if (node == NULL)
					return (NULL);
				if (node->data.first > data.first)
					return (search(node->left, data));
				else if (node->data.first < data.first)
					return (search(node->right, data));
				return (node);
			}

			void deletenode(value_type data)
			{
				if (root == NULL)
					return ;

				node *del = NULL; //지워질 노드
				node *replace = NULL; //위치가 바뀌어질 노드
				node *target = search(root, data); //데이터가 바뀔 노드

				if (target == NULL)
					return;
				if (target->left == NULL || target->right == NULL)
					del = target;
				else
				{
					del = minsearch(target->left);
					target->data = del->data;
				}

				if (del->left != NULL)
					replace = del->left;
				else if (del->right != NULL)
					replace = del->right;
				else
					replace = del;
				
				replace->parent = del->parent;

				if (del->parent == NULL)
				{
					if (replace == NULL)
						root = NULL;
					else
						root = replace;
				}
				else
				{
					if (del == del->parent->left)
						del->parent->left = replace;
					else
						del->parent->right = replace;
				}

				if (del->color == false)
					checkdelete(root, replace);

				t_alloc.destroy(&del->data);
				n_alloc.deallocate(del, 1);
				del = NULL;
				--t_size;
			}

			void checkdelete(node *root, node *replace)
			{
				node *sibling = NULL;

				while (replace->parent && replace->color == false)
				{
					if (replace == replace->parent->left) // 이중 흑색 노드가 부모의 왼쪽 
					{
						sibling = replace->parent->right;

						if (replace->parent->color == true)
						{
							if (sibling->color == false && sibling->left->color == false && sibling->right->color == false)
							{
								sibling->color = true;
								replace->color = false;
							}
						}
						if (sibling->color == true) // 형제 노드가 red
						{
							sibling->color = false;
							replace->parent->color = true;
							leftrotate(root, replace->parent);
						}
						else // 형제 노드가 black
						{
							if (sibling->left->color == false && sibling->right->color == false) // 조카 노드 둘다 black
							{
								sibling->color = true;
								replace = replace->parent;
							}
							else // 조카 노드들 중 하나라도 black이 아닌 경우
							{
								if (sibling->left->color == true)
								{
									sibling->color = true;
									sibling->left->color = false;
									rightrotate(root, sibling);
									sibling = replace->parent->right;
								}
								sibling->color = replace->parent->color;
								replace->parent->color = false;
								sibling->right->color = false;
								leftrotate(root, replace->parent);
								replace = root;
							}
						}
					}
					else // 이중 흑색 노드가 부모의 오른쪽
					{
						sibling = replace->parent->left;

						if (replace->parent->color == true)
						{
							if (sibling->color == false && sibling->left->color == false && sibling->right->color == false)
							{
								sibling->color = true;
								replace->color = false;
							}
						}
						if (sibling->color == true) // 형제 노드가 red
						{
							sibling->color = false;
							replace->parent->color = true;
							rightrotate(root, replace->parent);
						}
						else // 형제 노드가 black
						{
							if (sibling->left->color == false && sibling->right->color == false) // 조카 노드 둘다 black
							{
								sibling->color = true;
								replace = replace->parent;
							}
							else // 조카 노드들 중 하나라도 black이 아닌 경우
							{
								if (sibling->right->color == true)
								{
									sibling->color = true;
									sibling->right->color = false;
									leftrotate(root, sibling);
									sibling = replace->parent->left;
								}
								sibling->color = replace->parent->color;
								replace->parent->color = false;
								sibling->left->color = false;
								rightrotate(root, replace->parent);
								replace = root;
							}
						}
					}
				}
				replace->color = false;
			}

			void leftrotate(node *root, node *now)
			{
				if (now == NULL || now->right == NULL)
					return;

				node *r_child = now->right;

				now->right = r_child->left;
				if (now->right != NULL)
					now->right->parent = now;
				r_child->parent = now->parent;
				r_child->left = now;
				if (now->parent == NULL)
					this->root = r_child;
				else
				{
					if (now == now->parent->left)
						now->parent->left = r_child;
					else
						now->parent->right = r_child;
				}	
				now->parent = r_child;
				now = r_child;
			}

			void rightrotate(node *root, node *now)
			{
				if (now == NULL || now->left == NULL)
					return;

				node *l_child = now->left;

				now->left = l_child->right;
				if (l_child->right != NULL)
					l_child->right->parent = now;
				l_child->parent = now->parent;
				l_child->right = now;
				if (now->parent == NULL)
					this->root = l_child;
				else
				{
					if (now == now->parent->left)
						now->parent->left = l_child;
					else
						now->parent->right = l_child;
				}	
				now->parent = l_child;
				now = l_child;
			}

			iterator	begin(void)
			{
				return (iterator(root).findleft());
			};

			const_iterator	begin(void) const
			{
				return (const_iterator(iterator(root)).findleft());
			};

			iterator	end(void)
			{
				return (++iterator(root).findright());
			};

			const_iterator	end(void) const
			{
				return (const_iterator(++iterator(root).findright()));
			};

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(++iterator(root).findright()));
			};

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(++iterator(root)).findright()));
			};

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(iterator(root).findleft()));
			};

			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(iterator(root).findleft()));
			};
			
			bool empty() const
			{
				return (t_size == 0);
			}

			size_type size() const
			{
				return (t_size);
			}

			size_type max_size() const
			{
				return (n_alloc.max_size());
			}

			void swap(tree& t)
			{
				node *t_tmp = root;
				size_type s_tmp = t_size;

				root = t.root;
				t.root = t_tmp;
				t_size = t.t_size;
				t.t_size = s_tmp;
			}

			void del_tree(node *n)
			{
				if (n)
				{
					del_tree(node->left);
					del_tree(node->right);
					t_alloc.destroy(&n->data);
					n_alloc.deallocate(n, 1);
				}
			}

			void clear(void)
			{
				deleteTree(root);
				root->left = NULL;
				root->right = NULL;
				t_alloc.destroy(&root->data);
				n_alloc.deallocate(root, 1);
				t_size = 0;
			}

			value_compare value_comp() const
			{
				return (t_comp);
			}

			iterator find(const value_type &val)
			{
				node *check = root;

				while (check)
				{
					if (!t_comp(check->data, val) && !t_comp(val, check->data))
						break;
					if (t_comp(check->data, val))
						check = check->right;
					else
						check = check->left;
				}
				if (!check)
					return (end());
				return (iterator(check));
			}

			const_iterator find(const value_type &val) const
			{
				node *check = root;

				while (check)
				{
					if (!t_comp(check->data, val) && !t_comp(val, check->data))
						break;
					if (t_comp(check->data, val))
						check = check->right;
					else
						check = check->left;
				}
				if (!check)
					return (end());
				return (const_iterator(iterator(check)));
			}

			size_type count (const value_type &val) const
			{
				node *check = root;

				while (check)
				{
					if (!t_comp(check->data, val) && !t_comp(val, check->data))
						break;
					if (t_comp(check->data, val))
						check = check->right;
					else
						check = check->left;
				}
				if (!check)
					return (0);
				return (1);
			}

			iterator lower_bound (const value_type &val)
			{
				iterator it = begin();

				while (t_comp(*it, val) && it.n_ptr != end().n_ptr)
					it++;
				return (it);
			}

			const_iterator lower_bound (const value_type &val) const
			{
				iterator it = begin();

				while (t_comp(*it, val) && it.n_ptr != end().n_ptr)
					it++;
				return (it);
			}

			iterator upper_bound (const value_type &val)
			{
				iterator it = begin();

				while (t_comp(*it, val) && it.n_ptr != end().n_ptr)
					it++;
				if (!t_comp(*it, val) && !t_comp(val, *it))
					it++;
				return (it);
			}

			const_iterator upper_bound (const value_type &val) const
			{
				iterator it = begin();

				while (t_comp(*it, val) && it.n_ptr != end().n_ptr)
					it++;
				if (!t_comp(*it, val) && !t_comp(val, *it))
					it++;
				return (it);
			}
     };
}

#endif