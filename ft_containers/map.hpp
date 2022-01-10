#ifndef MAP_HPP
# define MAP_HPP

# include "RBT.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        public:
            typedef Key										key_type;
            typedef T										mapped_type;
            typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef Compare									key_compare;
			typedef Alloc									allocator_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef T*										pointer;
			typedef const T *								const_pointer;
			typedef std::ptrdiff_t							size_type;
			typedef map_iterator<value_type>				iterator;
			typedef map_iterator<const value_type>			const_iterator;
			typedef ft::reverse_map_iterator<value_type>		reverse_iterator;
			typedef ft::reverse_map_iterator<const value_type>	const_reverse_iterator;
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
		private:
			typedef RBtree<value_type, value_compare, allocator_type> tree_type;
			tree_type	tree;

			//typedef struct RBnode<value_type> node;
			//value_type	val;
			//allocator_type	t_alloc;
			// key_compare		comp;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : \
									tree(value_compare(comp), alloc) {};
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : \
									tree(value_compare(comp), alloc)
			{
				tree.insert(first, last);
			};
			map (const map& x) : tree(x.tree)
            {
               insert(x.begin(), x.end());
            };
			~map() {};

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					tree = x.tree;
				}
				return (*this);
			}

			mapped_type& operator[] (const key_type& k)
			{
 				return ((*((tree.insert(ft::make_pair(k, mapped_type()))).first)).second); 
			}

		//Iterator
			iterator begin()
			{
				return (iterator(tree.begin()));
			}

			const_iterator begin() const
			{
				return (const_iterator(tree.begin()));
			}

			iterator end()
			{
				return (iterator(tree.end()));
			}

			const_iterator end() const
			{
				return (const_iterator(tree.end()));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(tree.end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(tree.end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(tree.begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(tree.begin()));
			}

		// Modifiers
			ft::pair<iterator, bool> insert (const value_type& val)
			{
				pair<iterator, bool>	temp = tree.insert(val);
				return (ft::make_pair(iterator(temp.first), temp.second));
			}

			iterator insert (iterator position, const value_type& val)
			{
				return (tree.insert(position, val)); 
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last)
			{
				tree.insert(first, last);
			}
    };
}

#endif