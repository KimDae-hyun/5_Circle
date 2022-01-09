#ifndef RBT_HPP
# define RBT_HPP

# include "utils.hpp"

namespace ft
{
	template <class T>
	struct RBnode
	{
		typedef T		value_type;

		RBnode			*parent;
		RBnode			*left;
		RBnode			*right;
		bool 			color; // RED = true, BLACK = false
		value_type		data;

		//RBnode() : left(nullptr), right(nullptr), parent(nullptr), data() {}

		RBnode(value_type& other) : left(nullptr), right(nullptr), parent(nullptr), data(other) {}

		RBnode(const RBnode& node) : left(node.left), right(node.right), parent(node.parent), color(node.color), data(node.value) {}

		~RBnode() {} 

		RBnode& operator =(const RBnode& node)
		{
			if (*this != node)
			{
				this->left = node.left;
				this->right = node.right;
				this->parent = node.parent;
				this->value = node.value;
				this->data = node.data;
			}
			return (*this);
		}

		bool operator ==(const RBnode &node)
		{
			if (this->value == node->value)
				return (true);
			return (false);
		}

		bool operator !=(const RBnode &node)
		{
			return (!(*this == node));
		}

	};

    template <class V, class C, class A>
    class RBtree
    {
        public:
			typedef V					value_type;
			typedef C					value_compare;
			typedef A					allocator_type;
			typedef size_t				size_type;
			typedef RBtree				tree;
			typedef RBnode<V>			node;
			typedef typename std::allocator<node> node_alloc;


			//value_type		t_val;
			value_compare	t_comp;
			allocator_type	t_alloc;
			node_alloc		n_alloc;
			size_type		size;
			node			*root;
			node			*nil;

		public:
			RBtree(value_compare const& comp = value_compare(), allocator_type const& alloc = allocator_type(), node_alloc const& node_a = node_alloc())
			: t_comp(comp), t_alloc(alloc), n_alloc(node_a), size(0)
			{
				root = n_alloc.allocate(1);
				root->left = nullptr;
				root->right = nullptr;
				root->parent = nullptr;
				size = 0;
				nil = n_alloc.allocate(1);
				root->left = nullptr;
				root->right = nullptr;
				root->parent = nullptr;
				size = 0;
			}
			
			RBtree(const RBtree& tree)
			{
				root = tree.root;
				t_comp = tree.t_comp;
				t_alloc = tree.t_alloc;
				size = tree.size;
			}
			~RBtree() {};


			node *create(value_type data)
			{
				node* node = n_alloc.allocate(1);
				node->parent = nullptr;
				node->left = nullptr;
				node->right = nullptr;
				node->color = false; // BLACK = false
				node->data = data;
				return (node);
			}

			void insertnode(value_type data)
			{
				node *node = create(data);

				node->color = true;
				node->left = nil;
				node->right = nil;

				insertvalue(root, node);
				insertcheck(root, node);
			}

			void insertvalue(node *parent, node *node)
			{
				if (parent == nullptr)
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

			void minsearch(node *node)
			{
				if (node == nullptr)
					return ;
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
				if (root == nullptr)
					return ;

				node *del = nullptr;
				node *replace = nullptr;
				node *target = search(root, data);

				if (target == nullptr)
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

				if (del->parent == nullptr)
				{
					if (replace == nil)
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
				if (now == nil || now->right == nil)
					return;

				node *r_child = now->right;

				now->right = r_child->left;
				if (now->right != nil)
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
				if (now == nil || now->left == nil)
					return;

				node *l_child = now->left;

				now->left = l_child->right;
				if (l_child->right != nil)
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
				if (node == nil)
					return (nil);
				else if (node->left == nil)
					return (node);
				else
					return (find_min(node->left));
			}

			node* begin(void)
			{
				return (find_min(root));
			}

			node* find_max(node* node)
			{
				if (node == nullptr)
					return (nullptr);
				if (node == nil)
					return (nil);
				else if (node->right == nil)
					return (node);
				else
					return (find_max(node->right));
			}

			node* end(void)
			{
				return (find_max(root));
			}
     };
}

#endif