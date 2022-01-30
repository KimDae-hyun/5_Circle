#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

# include "iterator_traits.hpp"
# include "RBT.hpp"

namespace ft
{
    template<class T>
    struct RBnode;

    template <typename T>
	class const_tree_iterator;

	template <class T>
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		private:
			typedef ft::RBnode<T>				node;
			typedef ft::RBnode<T>*				node_pointer;

		public:
			typedef bidirectional_iterator_tag  iterator_category;
			typedef T                           value_type;
			typedef value_type&                 reference;
			typedef std::ptrdiff_t              difference_type;
			typedef T*                          pointer;

		private:
			node_pointer n_ptr;

			node_pointer	min_search(node_pointer node)
			{
				while (node->left != NULL)
					node = node->left;
				return (node);
			}

			node_pointer	max_search(node_pointer node)
			{
				while (node->right != NULL)
					node = node->right;
				return (node);
			}

		public:
			tree_iterator(): n_ptr(NULL) {}
			tree_iterator(node_pointer node) : n_ptr(node) {}
			tree_iterator(const tree_iterator &ref) : n_ptr(ref.n_ptr) {}
			~tree_iterator() {}

			tree_iterator& operator=(const tree_iterator& ref)
			{
				if (this != &ref)
					this->n_ptr = ref.n_ptr;
				return (*this);
			}

	        node_pointer getptr() const
			{
				return (this->n_ptr);
			}

			tree_iterator& operator++()
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
			}

			tree_iterator& operator--()
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
				return(*this);
			}

			tree_iterator operator++(int)
			{
				tree_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp);
			}

			tree_iterator operator--(int)
			{
				tree_iterator tmp;

				tmp = *this;
				--(*this);
				return (tmp);
			}

			reference operator*() const
			{
				return (n_ptr->value);
			}

			pointer operator->() const
			{
				return (&(n_ptr->value));
			}

			bool operator== (const tree_iterator& lhs)
			{
				return (this->n_ptr == lhs.getptr());
			}

			bool operator!= (const tree_iterator& lhs)
			{
				return (this->n_ptr != lhs.getptr());
			}

			bool operator== (const const_tree_iterator<T>& lhs)
			{
				return (this->n_ptr == lhs.getptr());
			}

			bool operator!= (const const_tree_iterator<T>& lhs)
			{
				return (this->n_ptr != lhs.getptr());
			}
	};

	template <class T>
	class const_tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, const T>
	{
		private:
			typedef ft::RBnode<T>               node;
			typedef ft::RBnode<T>*              node_pointer;

		public:
			typedef bidirectional_iterator_tag  iterator_category;
			typedef T                           value_type;
			typedef const value_type&           reference;
			typedef std::ptrdiff_t              difference_type;
			typedef const T*                    pointer;

		private:
			node_pointer 	n_ptr;

			node_pointer	min_search(node_pointer node)
			{
				while (node->left != NULL)
					node = node->left;
				return (node);
			}

			node_pointer	max_search(node_pointer node)
			{
				while (node->right != NULL)
					node = node->right;
				return (node);
			}

		public:
			const_tree_iterator(): n_ptr(NULL) {}
			const_tree_iterator(node_pointer node) : n_ptr(node) {}
			const_tree_iterator(const const_tree_iterator &ref) : n_ptr(ref.n_ptr) {}
			const_tree_iterator(const tree_iterator<T>& other) : n_ptr(other.getptr()) {}
			~const_tree_iterator() {}

			const_tree_iterator& operator=(const const_tree_iterator& ref)
			{
				if (this != &ref)
					this->n_ptr = ref.n_ptr;
				return (*this);
			}

	        node_pointer getptr() const
			{
				return (this->n_ptr);
			}

			const_tree_iterator& operator++()
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
			}

			const_tree_iterator& operator--()
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
			}

			const_tree_iterator operator++(int)
			{
				 const_tree_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp);
			}

			 const_tree_iterator operator--(int)
			{
				 const_tree_iterator tmp;

				tmp = *this;
				--(*this);
				return (tmp);
			}

			reference operator*() const
			{
				return (n_ptr->value);
			}

			pointer operator->() const //return 시, const 형을 반환
			{
				return (&(n_ptr->value));
			}

			bool operator== (const  const_tree_iterator& lhs)
			{
				return (this->n_ptr == lhs.getptr());
			}

			bool operator!= (const  const_tree_iterator& lhs)
			{
				return (this->n_ptr !=lhs.getptr());
			}

			bool operator== (const tree_iterator<T>& lhs)
			{
				return (this->n_ptr == lhs.getptr());
			}

			bool operator!= (const tree_iterator<T>& lhs)
			{
				return (this->n_ptr != lhs.getptr());
			}
	};
}
#endif
