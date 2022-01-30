#ifndef RBT_HPP
# define RBT_HPP

# include "utils.hpp"
# include "tree_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
    template<class T>
    struct RBnode
    {
        T		value;
        RBnode*	parent;
        RBnode*	left;
        RBnode*	right;
        Color	color;

        RBnode() : value(), parent(NULL), left(NULL), right(NULL), color(RED) {};
        RBnode(const T& val, RBnode *parent = NULL, RBnode *left = NULL, RBnode *right = NULL, Color color = RED)
            : value(val), parent(parent), left(left), right(right), color(color) {};
        ~RBnode() {};
    };

    template <class T, class Compare, class Alloc = std::allocator<T> >
    class RBtree
    {
        private:
            typedef ft::RBnode<T>							node_type;
            typedef ft::RBnode<T>*							node_pointer;
			typedef std::allocator<node_type>				node_alloc_type;

        public:
			typedef	T										value_type;
			typedef	Compare									value_compare;
			typedef	Alloc									allocate_type;
			typedef	std::size_t								size_type;
			typedef	std::ptrdiff_t							difference_type;
			typedef	typename allocate_type::reference		reference;
			typedef	typename allocate_type::const_reference	const_reference;
			typedef	typename allocate_type::pointer			pointer;
			typedef	typename allocate_type::const_pointer	const_pointer;
			typedef	ft::tree_iterator<value_type>			iterator;
			typedef	ft::const_tree_iterator<value_type>		const_iterator;
			typedef	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			value_compare	t_comp;
			allocate_type	t_alloc;
			node_alloc_type	n_alloc;
			node_pointer	base_node;
			size_type		t_size;

		public:
			RBtree(value_compare const &comp, allocate_type const &alloc, node_alloc_type const &node = node_alloc_type())
				: t_comp(comp), t_alloc(alloc), n_alloc(node), base_node(NULL), t_size(0)
			{
				base_node = n_alloc.allocate(1);
				n_alloc.construct(base_node, node_type());
			}

			RBtree(const RBtree &tree) : t_comp(tree.t_comp), t_alloc(tree.t_alloc), n_alloc(tree.n_alloc), base_node(NULL), t_size(0)
			{
				base_node = n_alloc.allocate(1);
				n_alloc.construct(base_node, node_type());
				tree_copy(tree.get_root());
			}

			~RBtree() {};

			RBtree& operator=(const RBtree &tree)
			{
				if (this == &tree)
					return (*this);
				clear();
				t_comp = tree.t_comp;
				t_alloc = tree.t_alloc;
				n_alloc = tree.n_alloc;
				tree_copy(tree.get_root());
				t_size = tree.t_size;
				return (*this);
			}

			void tree_copy(node_pointer node)
			{
				if (node != NULL)
				{
					insert_node(node->value);
					tree_copy(node->left);
					tree_copy(node->right);
				}
				return ;
			}

			iterator 					begin() { return (iterator(min_search(base_node))); }
			const_iterator				begin() const { return (const_iterator(min_search(base_node))); }
			iterator					end() { return (iterator(base_node)); }
			const_iterator				end() const { return ( const_iterator(base_node)); }
			reverse_iterator 			rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator		rbegin() const { return ( const_reverse_iterator(end())); }
			reverse_iterator			rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator		rend() const { return (const_reverse_iterator(begin())); }

			bool						empty() const { return (t_size == 0); }
			size_type					size() const { return (t_size); }
			size_type					max_size() const { return (n_alloc.max_size()); }

			node_pointer min_search(node_pointer node) const
			{
				if (node == NULL)
					return (node);
				while (node->left != NULL)
					node = node->left;
				return (node);
			}

			pair<iterator,bool> insert (const value_type& val)
			{
				return (insert_node(val));
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (insert_node(val).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first);
					++first;
				}
			}

			void erase (const_iterator position) { delete_value(*position); }
			size_type erase (const value_type &val) { return (delete_value(val)); }
			void erase (const_iterator first, const_iterator last)
			{
				for (const_iterator it = first; it != last; )
					erase(it++);
			}

			void swap(RBtree &tree)
			{
				value_compare	tmp_comp = tree.t_comp;
				allocate_type	tmp_t_alloc = tree.t_alloc;
				node_alloc_type tmp_n_alloc = tree.n_alloc;
				node_pointer	tmp_base_node = tree.base_node;
				size_type 		tmp_size = tree.t_size;

				tree.t_comp = t_comp;
				tree.t_alloc = t_alloc;
				tree.n_alloc = n_alloc;
				tree.base_node = base_node;
				tree.t_size = t_size;

				t_comp = tmp_comp;
				t_alloc = tmp_t_alloc;
				n_alloc = tmp_n_alloc;
				base_node = tmp_base_node;
				t_size = tmp_size;
			}

			void deleteTree(node_pointer node)
			{
				if (node != NULL)
				{
					deleteTree(node->left);
					deleteTree(node->right);
					n_alloc.destroy(node);
					n_alloc.deallocate(node, 1);
				}
			}

			void clear()
			{
				deleteTree(get_root());
				set_root(NULL);
				t_size = 0;
			}

			node_pointer find (const value_type& val) const
			{
				node_pointer tmp;

				tmp = get_root();
				while (tmp != NULL)
				{
					if (!t_comp(tmp->value, val) && !t_comp(val, tmp->value))
						break;
					else if (t_comp(tmp->value, val))
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				if (tmp == NULL)
					return (base_node);
				return (tmp);
			}

			size_type count(const value_type& val) const
			{
				iterator tmp;

				tmp = find(val);
				if (tmp == end())
					return (0);
				return (1);
			}

			iterator lower_bound (const value_type& val)
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

			iterator upper_bound (const value_type& val)
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

			const_iterator lower_bound (const value_type& val) const
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

			const_iterator upper_bound (const value_type& val) const
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

		private:
			node_pointer get_root(void) const
			{
				return (base_node->left);
			}

			void	set_root(node_pointer node) const
			{
				base_node->left = node;
				base_node->right = node;
				if (node != NULL)
					node->parent = base_node;
				return ;
			}

			Color get_color(node_pointer node)
			{
				if (node == NULL)
					return (BLACK);
				return (node->color);
			}

			void set_color(node_pointer node, Color color)
			{
				if (node == NULL)
					return ;
				node->color = color;
			}

			void rotate_left(node_pointer node)
			{
				node_pointer r_child = node->right;

				node->right = node->right->left;
				if (node->right != NULL)
					node->right->parent = node;
				r_child->left = node;
				r_child->parent = node->parent;
				if (node->parent == NULL)
					set_root(r_child);
				else
				{
					if (node == node->parent->left)
						node->parent->left = r_child;
					else
						node->parent->right = r_child;
				}
				node->parent = r_child;
				return ;
			}

			void rotate_right(node_pointer node)
			{
				node_pointer l_child = node->left;

				node->left = node->left->right;
				if (node->left != NULL)
					node->left->parent = node;
				l_child->right = node;	
				l_child->parent = node->parent;
				if (node->parent == NULL)
					set_root(l_child);
				else
				{
					if (node == node->parent->left)
						node->parent->left = l_child;
					else
						node->parent->right = l_child;
				}
				node->parent = l_child;
				return ;
			}

			pair<iterator, bool> insert_node(const value_type &val)
			{
				node_pointer node =	n_alloc.allocate(1);
				n_alloc.construct(node, node_type(val));
				pair<iterator, bool> ret = check_value(node);

				if (ret.second == false)
				{
					n_alloc.destroy(node);
					n_alloc.deallocate(node, 1);
				}
				else
				{
					t_size++;
					insert_check(node);
				}
				return (ret);
			}

			pair<iterator, bool> check_value(node_pointer node)
			{
				node_pointer tmp = get_root();
				node_pointer parent;

				if (tmp == NULL)
				{
					set_root(node);
					return (ft::make_pair(iterator(node), true));
				}
				while (tmp)
				{
					if (t_comp(tmp->value, node->value))
					{
						parent = tmp;
						tmp = tmp->right;
					}
					else if (t_comp(node->value, tmp->value))
					{
						parent = tmp;
						tmp = tmp->left;
					}
					else
						return (ft::make_pair(iterator(tmp), false));
				}
				if (t_comp(parent->value, node->value))
				{
					parent->right = node;
					node->parent = parent;
				}
				else
				{
					parent->left = node;
					node->parent = parent;
				}
				return (ft::make_pair(iterator(node), true));
			}

			node_pointer get_parent(node_pointer node) const
			{
				if (node == NULL)
					return (NULL);
				if (node->parent == base_node)
					return (NULL);
				return (node->parent);
			}

			node_pointer get_grandparent(node_pointer node)
			{
				node_pointer pr = get_parent(node);

				if (pr == NULL)
					return (NULL);
				return (get_parent(pr));
			}

			node_pointer get_sibling(node_pointer node)
			{
				node_pointer pr = get_parent(node);

				if (pr == NULL)
					return (NULL);
				if (node == pr->left)
					return (pr->right);
				return (pr->left);
			}

			node_pointer get_uncle(node_pointer node)
			{
				node_pointer pr = get_parent(node);

				if (pr == NULL)
					return (NULL);
				return (get_sibling(pr));
			}

			void parent_rotate(node_pointer& node, node_pointer &p)
			{
				if (p == get_grandparent(node)->left)
				{
					rotate_left(p);
					node = p;
					p = get_parent(node);
				}
				else if (p == get_grandparent(node)->right)
				{
					rotate_right(p);
					node = p;
					p = get_parent(node);
				}
				return ;
			}

			void grandp_rotate(node_pointer& node, node_pointer p, node_pointer g)
			{
				if (p == g->left)
					rotate_right(g);
				else if (p == g->right)
					rotate_left(g);
				std::swap(p->color, g->color);
				node = p;
				return ;
			}

			void insert_check(node_pointer node)
			{
				node_pointer	parent;
				node_pointer	grandparent;
				node_pointer	uncle;

				while (node != get_root() && get_color(node) == RED && get_color(get_parent(node)) == RED)
				{
					parent = get_parent(node);
					grandparent = get_grandparent(node);
					uncle = get_uncle(node);

					if(get_color(uncle) == RED)
					{
						set_color(parent, BLACK);
						set_color(uncle, BLACK);
						set_color(grandparent, RED);
						node = get_grandparent(node);
					}
					else if (parent == grandparent->left)
					{
						if (node == parent->right)
							parent_rotate(node, parent);
						grandp_rotate(node, parent, grandparent);
					}
					else if (parent == grandparent->right)
					{
						if (node == parent->left)
							parent_rotate(node, parent);
						grandp_rotate(node, parent, grandparent);
					}
				}
				set_color(get_root(), BLACK);
				return ;
			}

			void		delete_root(node_pointer root)
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

			void		delete_red(node_pointer &node)
			{
				node_pointer child;
				
				if (node->left != NULL)
					child =  node->left;
				else
					child = node->right;

				if (node == node->parent->left)
					node->parent->left = child;
				else
					node->parent->right = child;
				if (child != NULL)
					child->parent = node->parent;
				set_color(child, BLACK);
				n_alloc.destroy(node);
				n_alloc.deallocate(node, 1);
				return ;
			}

			void		parent_rotate_red(node_pointer &s, node_pointer &p)
			{
				if (s == p->right)
					rotate_left(p);
				if (s == p->left)
					rotate_right(p);
				set_color(s, BLACK);
				set_color(p, RED);
				return ;
			}

			void		sibling_recolor(node_pointer s, node_pointer p, node_pointer &node)
			{
				set_color(s, RED);
				if (get_color(p) == RED)
					set_color(p, BLACK);
				else
					set_color(p, DOUBLE_B);
				node = p;
				return ;
			}

			void		sibling_rotate(node_pointer &s, node_pointer &p)
			{
				if (s == p->right)
				{
					rotate_right(s);
					set_color(s->left, BLACK);
					set_color(s, RED);
					s = p->right;
				}
				if (s == p->left)
				{
					rotate_left(s);
					set_color(s->right, BLACK);
					set_color(s, RED);
					s = p->left;
				}
				return ;
			}

			void		parent_rotate_black(node_pointer &s, node_pointer &p)
			{
				if (s == p->right)
				{
					rotate_left(p);
					set_color(s, get_color(p));
					set_color(p, BLACK);
					set_color(s->right, BLACK);
				}
				if (s == p->left)
				{
					rotate_right(p);
					set_color(s, get_color(p));
					set_color(p, BLACK);
					set_color(s->left, BLACK);
				}
				return ;
			}

			void		delete_check(node_pointer node)
			{
				if (node == NULL)
					return ;
				if (node == get_root())
				{
					delete_root(node);
					return ;
				}
				if (get_color(node) == RED || get_color(node->left) == RED || get_color(node->right) == RED)
				{
					delete_red(node);
					return ;
				}
				node_pointer s = NULL;
				node_pointer p = NULL;
				node_pointer tmp = node;
				set_color(tmp, DOUBLE_B);
				while (tmp != get_root() && get_color(tmp) == DOUBLE_B)
				{
					p = tmp->parent;
					s = (tmp == p->left) ? p->right : p->left;
					if (get_color(s) == RED)
						parent_rotate_red(s, p);
					else if (get_color(s->left) == BLACK && get_color(s->right) == BLACK)
						sibling_recolor(s, p, tmp);
					else
					{
						if ((tmp == p->left && get_color(s->right) == BLACK)
						|| (tmp == p->right && get_color(s->left) == BLACK))
							sibling_rotate(s, p);
						parent_rotate_black(s, p);
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
				return ;
			}

			node_pointer	find_change_node(node_pointer node, const value_type &val)
			{
				if (node == NULL)
					return (node);
				if (t_comp(node->value, val))
					return (find_change_node(node->right, val));
				if (t_comp(val, node->value))
					return (find_change_node(node->left, val));
				if (node->left == NULL || node->right == NULL)
					return (node);
				node_pointer tmp = min_search(node->right);
				// 지워질 노드(node)에 대체될 노드(tmp)를 찾아 교체 (node <-> tmp)
				if (tmp->parent == node)
				{
					if (node->parent && node->parent->left == node)
						node->parent->left = tmp;
					if (node->parent && node->parent->right == node)
						node->parent->right = tmp;
					tmp->left = node->left;
					node->left->parent = tmp;
					node->left = NULL;
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
					node_pointer tmp2 = tmp->parent;
					node->right->parent = tmp;
					tmp->parent = node->parent;
					node->parent = tmp2;
					tmp->left = node->left;
					node->left->parent = tmp;
					node->left = NULL;
					node_pointer tmp3 = tmp->right;
					tmp->right = node->right;
					node->right = tmp3;
					std::swap(tmp->color, node->color);
				}
				return (find_change_node(tmp->right, val));
			}

			size_type	delete_value(const value_type &val)
			{
				node_pointer target = find_change_node(get_root(), val);
				if (target == NULL)
					return (0);
				delete_check(target);
				t_size--;
				return (1);
			}
    };

}

#endif
