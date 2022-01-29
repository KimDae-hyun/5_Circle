#ifndef RBT_HPP
# define RBT_HPP

# include "utils.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template <class T>
	class map_iterator;
	
	// template <class T>
    // class reverse_iterator;

	template <class T>
	struct RBnode
	{
		typedef T		value_type;
		typedef RBnode	node;

		RBnode			*parent;
		RBnode			*left;
		RBnode			*right;
		Color 			color; // RED = true, BLACK = false
		value_type		data;
	};

    template <class V, class C, class A>
    class RBtree
    {
        public:
			typedef V									value_type;
			typedef C									value_compare;
			typedef A									allocator_type;
			typedef V&									reference;
			typedef const V&							const_reference;
			typedef V*									pointer;
			typedef const V*							const_pointer;
			typedef ft::map_iterator<value_type>			iterator;
			typedef ft::const_map_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef std::ptrdiff_t						difference_type;
			typedef size_t								size_type;
			typedef RBtree								tree;
			typedef RBnode<V>							node_type;
			typedef std::allocator<node_type>				node_allocator;

		private:
			value_compare	t_comp;
			allocator_type	t_alloc;
			node_allocator	n_alloc;
			size_type		t_size;
			node_type		*nil;

		public:
			RBtree(value_compare const& comp = value_compare(), allocator_type const& alloc = allocator_type(), node_allocator const& node_a = node_allocator())
			: t_comp(comp), t_alloc(alloc), n_alloc(node_a), t_size(0)
			{
				nil = n_alloc.allocate(1);
				nil->left = NULL;
				nil->right = NULL;
				nil->parent = NULL;
				nil->color = RED;
				n_alloc.construct(nil, node_type());
			}
			
			RBtree(const RBtree& tree) : t_comp(tree.t_comp), t_alloc(tree.t_alloc), n_alloc(tree.n_alloc), t_size(0)
			{
				const_iterator it = tree.begin();
				nil = n_alloc.allocate(1);
				nil->left = NULL;
				nil->right = NULL;
				nil->parent = NULL;
				nil->color = RED;
				n_alloc.construct(nil, node_type());

				for (size_type i = 0; i < tree.t_size; i++)
					insert(*it++);
			}
			~RBtree() {};

			RBtree& operator=(const RBtree &tree)
			{
				const_iterator it = tree.begin();

				if (this == &tree)
					return (*this);
				this->clear();
				this->t_comp = tree.t_comp;
				this->t_alloc = tree.t_alloc;
				this->n_alloc = tree.n_alloc;
				for (size_type i = 0; i < tree.t_size; i++)
					insert(*it++);
				// copyTree(tree.get_root());
				this->t_size = tree.t_size;
				return (*this);
			}

			Color get_color(node_type *node)
			{
				if (node == NULL)
					return (BLACK);
				return (node->color);
			}

			void set_color(node_type *node, Color color)
			{
				if (node == NULL)
					return ;
				node->color = color;
			}

			node_type *get_root(void) const
			{
				return (nil->left);
			}

			void	set_root(node_type *node) const
			{
				nil->left = node;
				nil->right = node;
				if (node != NULL)
					node->parent = nil;
			}

			node_type *create(value_type data)
			{
				node_type* node = n_alloc.allocate(1);

				t_alloc.construct(&node->data, data);

				//node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				node->color = RED;
				++t_size;
				return (node);
			}

			pair<iterator, bool> insertnode(value_type val)
			{
				node_type *node = create(val);
                bool b;

				if (t_size == 1)
					set_root(node);
				b = insertvalue(get_root(), node);
                if (b == true)
					insertcheck(node);
				return (pair<iterator, bool>(iterator(node), b));
			}

			bool insertvalue(node_type *parent, node_type *node)
			{
				//  std::cout << parent->data.first << " / " << parent->data.second << "  //  " <<
				//  node->data.first << " / " << node->data.second << std::endl;
				if (t_comp(parent->data, node->data))
				{
					if (parent->right == NULL)
					{
						//std::cout << "c " << node->data.first << std::endl;
						parent->right = node;
						node->parent = parent;
					}
					else
						return (insertvalue(parent->right, node));
				}
				else if (t_comp(node->data, parent->data))
				{
					if (parent->left == NULL)
					{
						parent->left = node;
						node->parent = parent;
					}
					else
						return (insertvalue(parent->left, node));
				}
                else
				{					
					if (t_size == 1)
						return (true);
					// std::cout << "????" << parent->data.first << " / " << node->data.first << std::endl;
					node->data.second = parent->data.second;
					n_alloc.destroy(node);
					n_alloc.deallocate(node, 1);
					t_size--;
                    return (false);
                }
                return (true);
			}

			void insertcheck(node_type *now)
			{
				//부모가 red이면 자식은 black
				while (now != get_root() && get_color(now) == RED && get_color(now->parent) == RED)
				{
					//부모 노드가 조부모의 왼쪽 자식인 경우
					if (now->parent == now->parent->parent->left)
					{
						node_type *uncle = now->parent->parent->right;

						//부모, 삼촌 노드가 red
						if (uncle && get_color(uncle) == RED)
						{ 
							now->parent->color = BLACK;
							uncle->color = BLACK;
							now->parent->parent->color = RED;
							now = now->parent->parent;
						}
						else //부모는 red, 삼촌은 black
						{ 
							// 부모의 오른쪽으로 삽입되는 경우
							if (now == now->parent->right)
							{ 
								now = now->parent;
								leftrotate(now);
							}
							// 부모의 왼쪽으로 삽입되는 경우
							now->parent->color = BLACK;
							now->parent->parent->color = RED;
							rightrotate(now->parent->parent);
						}
					}
					else
					{ //부모 노드가 조부모의 오른쪽 자식인 경우 왼쪽과 반대로
						node_type *uncle = now->parent->parent->left;
						
						if (uncle && get_color(uncle) == RED)
						{
							now->parent->color = BLACK;
							uncle->color = BLACK;
							now->parent->parent->color = RED;
							now = now->parent->parent;
						}
						else
						{
							if (now == now->parent->left)
							{
								now = now->parent;
								rightrotate(now);
							}
							now->parent->color = BLACK;
							now->parent->parent->color = RED;
							leftrotate(now->parent->parent);
						}
					}
				}
				set_color(get_root(), BLACK);
				// root 노드는 항상 black
			}

			node_type* minsearch(node_type *node)
			{
				if (node == NULL)
					return (node);
				if (node->left != NULL)
					return (minsearch(node->left));
				return (node);
			}

			node_type *search(node_type *node, value_type data)
			{
				if (node == NULL)
					return (NULL);
				if (node->data.first > data.first)
					return (search(node->left, data));
				else if (node->data.first < data.first)
					return (search(node->right, data));
				return (node);
			}

			void		deleteRootCase(node_type *root)
			{
				if (root->right)
					set_root(root->right);
				else
					set_root(root->left);
				n_alloc.destroy(root);
				n_alloc.deallocate(root, 1);
				set_color(get_root(), BLACK);
				return ;
			}

			void		deleteRedCase(node_type *node)
			{
				node_type *child = node->left != NULL ? node->left : node->right;
				if (node == node->parent->left)
					node->parent->left = child;
				else
					node->parent->right = child;
				if (child != NULL)
					child->parent = node->parent;
				set_color(child, BLACK);
				n_alloc.destroy(node);
				n_alloc.deallocate(node, 1);
			}

			void		deleteCase1(node_type *s, node_type *p)
			{
				if (s == p->right)
					leftrotate(p);
				if (s == p->left)
					rightrotate(p);
				set_color(s, BLACK);
				set_color(p, RED);
			}

			void		deleteCase2(node_type *s, node_type *p, node_type *node)
			{
				set_color(s, RED);
				if (get_color(p) == RED)
					set_color(p, BLACK); // extra black 제거
				else
					set_color(p, DBLACK); // dblack
				node = p; // 위로 올리기
			}

			void		deleteCase3(node_type *s, node_type *p)
			{
				if (s == p->right)
				{
					rightrotate(s);
					set_color(s->left, BLACK);
					set_color(s, RED);
					s = p->right; // 형제 재정의
				}
				if (s == p->left)
				{
					leftrotate(s);
					set_color(s->right, BLACK);
					set_color(s, RED);
					s = p->left;
				}
			}

			void		deleteCase4(node_type *s, node_type *p)
			{
				if (s == p->right)
				{
					leftrotate(p);
					set_color(s, get_color(p));
					set_color(p, BLACK);
					set_color(s->right, BLACK);
				}
				if (s == p->left)
				{
					rightrotate(p);
					set_color(s, get_color(p));
					set_color(p, BLACK);
					set_color(s->left, BLACK);
				}
			}

			void checkdelete(node_type *node)
			{
				if (node == NULL)
					return ;
				if (node == get_root())
				{
					deleteRootCase(node);
					return ;
				}
				if (get_color(node) == RED || get_color(node->left) == RED || get_color(node->right) == RED)
				{
					deleteRedCase(node);
					return ;
				}
				node_type *sibling = NULL;
				node_type *parent = NULL;
				node_type *tmp = node;
				set_color(tmp, DBLACK);
				
				while (tmp != get_root() && get_color(tmp) == DBLACK)
				{
					parent = tmp->parent;
					sibling = (tmp == parent->left) ? parent->right : parent->left;
					if (get_color(sibling) == RED)
						deleteCase1(sibling, parent); // 형제가 RED일 때 두발 전진을 위한 한발 후퇴
					else if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK)
						deleteCase2(sibling, parent, tmp); // 형제의 자식들이 BLACK일 때
					else
					{
						if ((tmp == parent->left && get_color(sibling->right) == BLACK)
						|| (tmp == parent->right && get_color(sibling->left) == BLACK))
							deleteCase3(sibling, parent);
						deleteCase4(sibling, parent);
						break;
					}
				}
				if (node == node->parent->left)
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
				n_alloc.destroy(node);
				n_alloc.deallocate(node, 1);
				set_color(get_root(), BLACK);
			}

			node_type *del_search(node_type *node, const value_type &val)
			{
				if (node == NULL)
					return (node);
				if (t_comp(node->data, val)) // 삭제하고자하는 위치 찾기
					return (del_search(node->right, val));
				if (t_comp(val, node->data))
					return (del_search(node->left, val));
				if (node->left == NULL || node->right == NULL)
					return (node);
				node_type *tmp = min_search(node->right);
				if (tmp->parent == node) //tmp left가 null
				{
					if (node->parent && node->parent->left == node)
						node->parent->left = tmp;
					if (node->parent && node->parent->right == node)
						node->parent->right = tmp;
					tmp->left = node->left;
					node->left->parent = tmp;
					node->left = NULL; // 529번째줄로 return하기 위한 조건
					tmp->parent = node->parent;
					node->parent = tmp;
					node->right = tmp->right;
					tmp->right = node;
					std::swap(tmp->color, node->color);
				}
				else
				{
					if (node->parent && node->parent->left == node)
						node->parent->left = tmp;
					if (node->parent && node->parent->right == node)
						node->parent->right = tmp;
					if (tmp->parent->left == tmp)
						tmp->parent->left = node;
					if (tmp->parent->right == tmp)
						tmp->parent->right = node;
					node_type *tmp2 = tmp->parent;
					node->right->parent = tmp;
					tmp->parent = node->parent;
					node->parent = tmp2;
					tmp->left = node->left;
					node->left->parent = tmp;
					node->left = NULL;
					node_type *tmp3 = tmp->right;
					tmp->right = node->right;
					node->right = tmp3;
					std::swap(tmp->color, node->color);
				}
				return (del_search(tmp->right, val));
			}

			size_type deletenode(const value_type &data)
			{
				node_type *target = del_search(get_root(), data);
				if (target == NULL)
					return (0);
				checkdelete(target);
				--t_size;
				return (1);
			}

			void leftrotate(node_type *now)
			{
				node_type *r_child = now->right;

				now->right = now->right->left;
				if (now->right != NULL)
					now->right->parent = now;
				r_child->left = now;
				r_child->parent = now->parent;
				if (now->parent == NULL)
					set_root(r_child);
				else
				{
					if (now == now->parent->left)
						now->parent->left = r_child;
					else
						now->parent->right = r_child;
				}
				now->parent = r_child;
				//now = r_child;
			}

			void rightrotate(node_type *now)
			{
				node_type *l_child = now->left;

				now->left = now->left->right;
				if (now->left != NULL)
					now->left->parent = now;
				l_child->right = now;	
				l_child->parent = now->parent;
				if (now->parent == NULL)
					set_root(l_child);
				else
				{
					if (now == now->parent->left)
						now->parent->left = l_child;
					else
						now->parent->right = l_child;
				}
				now->parent = l_child;
				//now = l_child;
			}

			node_type* min_search(node_type *node) const
			{
				if (node == NULL)
					return (node);
				if (node->left == NULL)
					return (node);
				return (min_search(node->left));
			}

			iterator	begin(void)
			{
				return (iterator(min_search(nil)));
			};

			const_iterator	begin(void) const
			{
				return (const_iterator(min_search(nil)));
			};

			iterator	end(void)
			{
				return (iterator(nil));
			};

			const_iterator	end(void) const
			{
				return (const_iterator(nil));
			};

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(end()));
			};

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(end()));
			};

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(begin()));
			};

			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(begin()));
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
				if (n_alloc.max_size() < (size_t)std::numeric_limits<difference_type>::max())
					return (n_alloc.max_size());
				return (std::numeric_limits<difference_type>::max());
				//return (n_alloc.max_size());
			}

			pair<iterator, bool>	insert(const value_type& val)
			{
				return (insertnode(val));
			}

			iterator	insert(iterator position, const value_type& val)
			{
				(void)position;
				return (iterator(insertnode(val).first));
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			};

			void erase (iterator position)
			{
				deletenode(*position);
			}

			size_type erase (const value_type &val)
			{
				return (deletenode(val));
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					deletenode(*first);
					first++;
				}
			}

			void swap(tree& t)
			{
				value_compare	tmp_comp = t_comp;
				allocator_type	tmp_alloc = t_alloc;
				node_allocator	tmp_n_all = n_alloc;
				size_type		tmp_size = t_size;
				node_type 		*tmp_nil = nil;

				t_comp = t.t_comp;
				t.t_comp = tmp_comp;

				t_alloc = t.t_alloc;
				t.t_alloc = tmp_alloc;

				n_alloc = t.n_alloc;
				t.n_alloc = tmp_n_all;

				t_size = t.t_size;
				t.t_size = tmp_size;

				nil = t.nil;
				t.nil = tmp_nil;			
			}

			void del_tree(node_type *n)
			{
				if (n)
				{
					del_tree(n->left);
					del_tree(n->right);

					t_alloc.destroy(&n->data);
					n_alloc.deallocate(n, 1);
				}
			}

			void clear(void)
			{
				if (get_root())
				{
					del_tree(get_root());
					get_root()->left = NULL;
					get_root()->right = NULL;
					nil->left = NULL;
					nil->right = NULL;
				}
				t_size = 0;
			}

			iterator find(const value_type &val)
			{
				node_type *check = get_root();

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
				node_type *check = get_root();

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
				node_type *check = get_root();

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
				iterator it1 = begin();
				iterator it2 = end();

				while (it1 != it2)
				{
					if (t_comp(*it1, val) == false)
						break;
					++it1;
				}
				return (it1);
			}

			const_iterator lower_bound (const value_type &val) const
			{
				const_iterator it1 = begin();
				const_iterator it2 = end();

				while (it1 != it2)
				{
					if (t_comp(*it1, val) == false)
						break;
					++it1;
				}
				return (it1);
			}

			iterator upper_bound (const value_type &val)
			{
				iterator it1 = begin();
				iterator it2 = end();

				while (it1 != it2)
				{
					if (t_comp(val, *it1) == true)
						break;
					++it1;
				}
				return (it1);
			}

			const_iterator upper_bound (const value_type &val) const
			{
				const_iterator it1 = begin();
				const_iterator it2 = end();

				while (it1 != it2)
				{
					if (t_comp(val, *it1) == true)
						break;
					++it1;
				}
				return (it1);
			}

			// value_compare getcomp() const
			// {
			// 	return (t_comp);
			// }

			allocator_type getalloc() const
			{
				return (t_alloc);
			}
    };
}

#endif