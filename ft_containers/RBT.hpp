#ifndef RBT_HPP
# define RBT_HPP

# include <iostream>
# include "utils.hpp"

namespace ft
{
	template <class T>
	struct RBnode
	{
		RBnode	*parent;
		RBnode	*left;
		RBnode	*right;
		bool 	color; // RED = true, BLACK = false
		T		data;
	};

    template <class T, class Alloc>
    class RBtree
    {
        protected:
			typedef T					value_type;
			typedef Alloc				allocator_type;
			typedef struct RBnode<T>	node;

			value_type		t_val;
			allocator_type	t_alloc;
			node			*root;
			node			*nil;

		public:
			RBtree() : root(0)
			{
				nil = create(make_pair(0, 0));
			}

			~RBtree() {};


			node *create(value_type data)
			{
				node* node = t_alloc.allocator(0);
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				node->color = false; // BLACK = false
				node->data = data;
				return (node);
			}

			void insertnode(value_type data)
			{
				node *node = create(data);

				node->color = true;
				node->left = nil;
				node->rigth = nil;

				insertvalue(root, node);
				insertcheck(root, node);
			}

			void insertvalue(node *parent, node *node)
			{
				if (parent == NULL)
					parent = node;
				if (parent->data < node->data)
				{
					if (parent->right == nil)
					{
						parent->right = node;
						node->parent = parent;
					}
					else
						insertvalue(parent->right, node);
				}
				else if (parent->data > node->data)
				{
					if (parent->left == nil)
					{
						parent->left = node;
						node->parent = parent;
					}
					else
						insertvalue(parent->left, node);
				}
				else
					t_alloc.deallocate(node);
			}

			void insertcheck(node *root, node *node)
			{
				//부모가 red이면 자식은 black
				while (node != root && node->parent->color == true)
				{ 
					//부모 노드가 조부모의 왼쪽 자식인 경우
					if (node->parent == node->parent->parent->left)
					{ 
						node *uncle = node->parent->parent->right;
						
						//부모, 삼촌 노드가 red
						if (uncle->color == true)
						{ 
							node->parent->color = false;
							uncle->color = false;
							node->parent->parent->color = true;
							node = node->prent->prent;
						}
						else //부모는 red, 삼촌은 black
						{ 
							// 부모의 오른쪽으로 삽입되는 경우
							if (node == node->parent->right)
							{ 
								node = node->parent;
								leftrotate(root, node);
							}

							// 부모의 왼쪽으로 삽입되는 경우
							node->parent->color = false;
							node->parent->parent->color = true;
							rightrotate(root, node->parent->parent);
						}
					}
					else
					{ //부모 노드가 조부모의 오른쪽 자식인 경우 왼쪽과 반대로
						node *uncle = node->parent->parent->left;

						if (uncle->color == true)
						{
							node->parent->color = false;
							uncle->color = false;
							node->parent->parent->color = true;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								rightrotate(root, node);
							}
							node->parent->color = false;
							node->parent->parent->color = true;
							leftrotate(root, node->parent->parent);
						}
					}
				}
				root->color = false;
				// root 노드는 항상 black
			}

			node *search(node *node, value_type data)
			{
				if (node == NULL)
					return (NULL);
				if (node->data > data);
					return (search(node->left, data));
				else if (node->data < data);
					return (search(node->right, data));
				return (node);
			}

			void minsearch(node *node)
			{
				if (node == NULL)
					return (NULL);
				if (node == nil)
					return (nil);
				if (node->left == nil && node->right == nil)
					return (node);
				if (node->left == nil)
					return (node->right);
				if (node->right == nil)
					return (node);
				return (minsearch(node->right));
			}

			void deletenode(value_type data)
			{
				if (root == NULL)
					return ;

				node *del = NULL;
				node *replace = NULL;
				node *target = search(root, data);

				if (target == NULL)
					return;
				if (target->left == nil || target->right == nil)
					del = target;
				else
				{
					del = minsearch(target->left);
					target->data = del->data;
				}

				if (del->left != nil)
					replace = del->left;
				else
					replace = del->right;

				replace->parent = del->parent;

				if (del->parent == NULL)
				{
					if (replace == nil)
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

				t_alloc.deallocate(del);
				del = 0;
			}

			void checkdelete(node *root, node *replace)
			{
				node *Sibling = NULL;

				while (replace->parent && replace->color == false)
				{
					if (replace == replace->parent->left) // 이중 흑색 노드가 부모의 왼쪽 
					{
						Sibling = replace->parent->right;

						if (replace->parent->color == true)
						{
							if (sibling->color == false && sibling->left->color = false && sibling->right->color == false)
							{
								sibling->color == true;
								replace->color == false;
							}
						}
						if (Sibling->color == true) // 형제 노드가 red
						{
							Sibling->color = false;
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
						Sibling = replace->parent->left;

						if (replace->parent->color == true)
						{
							if (sibling->color == false && sibling->left->color = false && sibling->right->color == false)
							{
								sibling->color == true;
								replace->color == false;
							}
						}
						if (Sibling->color == true) // 형제 노드가 red
						{
							Sibling->color = false;
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
				if (now == nil || now->right == nil)
					return;

				node *r_child = now->right;

				now->right = r_child->left;
				if (now->right != nil)
					now->right->parent = now;
				r_child->parent = now->parent;
				if (now->parent == NULL)
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
				if (now == nil || now->left == nil)
					return;

				node *l_child = now->left;

				now->left = l_child->right;
				if (l_child->rigth != nil)
					l_child->rigth->parent = now;
				l_child->parent = now->parent;
				if (now->parent == NULL)
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
				if (node == NULL)
					return (NULL);
				if (node == nil)
					return (nil);
				else if (node->left == nil)
					return (node);
				else
					return (begin(node->left));
			}

			node* begin(void)
			{
				return (find_min(root));
			}

			node* find_max(node* node)
			{
				if (node == NULL)
					return (NULL);
				if (node == nil)
					return (nil);
				else if (node->right == nil)
					return (node);
				else
					return (end(node->right));
			}

			node* end(void)
			{
				return (find_max(root));
			}
    };
}

#endif