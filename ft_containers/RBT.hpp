#ifndef RBT_HPP
# define RBT_HPP

# include "utils.hpp"
# include "map_iterator.hpp"

namespace ft
{
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

		RBnode(value_type& other) : left(nullptr), right(nullptr), parent(nullptr), data(other) {}

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
				{ return (&this->n_ptr->data); };


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

			//value_type		t_val;
			value_compare	t_comp;
			allocator_type	t_alloc;
			node_allocator	n_alloc;
			size_type		size;
			node			*root;
			//node			*NULL;

		public:
			RBtree(value_compare const& comp = value_compare(), allocator_type const& alloc = allocator_type(), node_allocator const& node_a = node_allocator())
			: t_comp(comp), t_alloc(alloc), n_alloc(node_a), size(0)
			{
				root = n_alloc.allocate(1);
				root->left = NULL;
				root->right = NULL;
				root->parent = NULL;
				root->color = true;
			}
			
			RBtree(const RBtree& tree) : t_comp(tree.comp), t_alloc(tree.t_alloc), n_alloc(tree.n_alloc), size(tree.size)
			{
				root = n_alloc.allocate(1);
				root->parent = NULL;
				root->color = true;
				if (tree.root.left != NULL)
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

				if ((position != end()) && (size && prev->data <= val && next->data >= val))
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
				node->left = NULL;
				node->right = NULL;
				node->color = true;
				++size;
				return (node);
			}

			pair<iterator, bool> insertnode(value_type val)
			{
				node *innode;
				
				if (!root->left)
				{
					innode = n_alloc.allocate(1);
					t_alloc.construct(&innode->data, val);
					innode->color = false;
					innode->parent = root;
					innode->left = NULL;
					innode->right = NULL;
					root->left = innode;
					root->right = innode;
					innode->parent = root;
					size++;
					return (pair<iterator, bool>(iterator(innode), true));
				}
				node *next = root->left;
				node *n_parent;
				while (next)
				{
					n_parent = next;
					if (t_comp(next->data, val))
						next = next->right;
					else
					{
						if (!t_comp(next->data, val) && !t_comp(val, next->data))
							return (pair<iterator, bool>(iterator(next), false));
						next = next->left;
					}
				}
				innode = create(val);
				innode->parent = n_parent;
				if (innode->parent->right == next)
					innode->parent->right = innode;
				else
					innode->parent->left = innode;
				if (innode->parent->color == true)
					insertcheck(root, innode);/// 기존 코드 사용 
				return (pair<iterator, bool>(iterator(innode), true));
			}

			void insertvalue(node *parent, node *node)
			{
				if (parent == nullptr)
					parent = node;
				if (parent->data < node->data)
				{
					if (parent->right == NULL)
					{
						parent->right = node;
						node->parent = parent;
					}
					else
						insertvalue(parent->right, node);
				}
				else if (parent->data > node->data)
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
				while (now != root && now->parent->color == true)
				{ 
					//부모 노드가 조부모의 왼쪽 자식인 경우
					if (now->parent == now->parent->parent->left)
					{ 
						node *uncle = now->parent->parent->right;

						//부모, 삼촌 노드가 red
						if (uncle->color == true)
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

						if (uncle->color == true)
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

			node *search(node *node, value_type data)
			{
				if (node == nullptr)
					return (nullptr);
				if (node->data > data)
					return (search(node->left, data));
				else if (node->data < data)
					return (search(node->right, data));
				return (node);
			}

			// void minsearch(node *node)
			// {
			// 	if (node == nullptr)
			// 		return ;
			// 	if (node == NULL)
			// 		return (NULL);
			// 	if (node->left == NULL && node->right == NULL)
			// 		return (node);
			// 	if (node->left == NULL)
			// 		return (node->right);
			// 	if (node->right == NULL)
			// 		return (node);
			// 	return (minsearch(node->right));
			// }

			void deletenode(value_type data)
			{
				if (root == nullptr)
					return ;

				node *del = nullptr;
				node *replace = nullptr;
				node *target = search(root, data);

				if (target == nullptr)
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
				else
					replace = del->right;

				replace->parent = del->parent;

				if (del->parent == nullptr)
				{
					if (replace == NULL)
						root = nullptr;
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

				n_alloc.deallocate(del);
				del = 0;
			}

			void checkdelete(node *root, node *replace)
			{
				node *sibling = nullptr;

				while (replace->parent && replace->color == false)
				{
					if (replace == replace->parent->left) // 이중 흑색 노드가 부모의 왼쪽 
					{
						sibling = replace->parent->right;

						if (replace->parent->color == true)
						{
							if (sibling->color == false && sibling->left->color == false && sibling->right->color == false)
							{
								sibling->color == true;
								replace->color == false;
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
							if (sibling->left->color == false && sibling->right->colot == false) // 조카 노드 둘다 black
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
								sibling->color == true;
								replace->color == false;
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
							if (sibling->left->color == false && sibling->right->colot == false) // 조카 노드 둘다 black
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
				if (now->parent == nullptr)
					root = r_child;
				else
				{
					if (now == now->parent->left)
						now->parent->left = r_child;
					else
						now->parent->right = r_child;
				}	
				r_child->left = now;
				now->parent = r_child;
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
				if (now->parent == nullptr)
					root = l_child;
				else
				{
					if (now == now->parent->left)
						now->parent->left = l_child;
					else
						now->parent->right = l_child;
				}	
				l_child->right = now;
				now->parent = l_child;
			}

			node* find_min(node* node)
			{
				if (node == nullptr)
					return (nullptr);
				if (node == NULL)
					return (NULL);
				else if (node->left == NULL)
					return (node);
				else
					return (find_min(node->left));
			}

			// node* begin(void)
			// {
			// 	return (find_min(root));
			// }

			node* find_max(node* node)
			{
				if (node == nullptr)
					return (nullptr);
				if (node == NULL)
					return (NULL);
				else if (node->right == NULL)
					return (node);
				else
					return (find_max(node->right));
			}

			// node* end(void)
			// {
			// 	return (find_max(root));
			// }

			iterator	begin(void)
				{ return (iterator(root).findleft()); };
			const_iterator	begin(void) const
				{ return (const_iterator(iterator(root)).findleft()); };
			iterator	end(void)
				{ return (iterator(root)); };
			const_iterator	end(void) const
				{ return (const_iterator(iterator(root))); };
			reverse_iterator	rbegin(void)
				{ return (reverse_iterator(iterator(root))); };
			const_reverse_iterator	rbegin(void) const
				{ return (const_reverse_iterator(iterator(root))); };
			reverse_iterator	rend(void)
				{ return (reverse_iterator(iterator(root).findleft())); };
			const_reverse_iterator	rend(void) const
				{ return (const_reverse_iterator(iterator(root).findleft())); };
     };
}

#endif