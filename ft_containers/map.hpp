#ifndef MAP_HPP
# define MAP_HPP

# include "map_iterator.hpp"

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
			typedef size_t									size_type;
			typedef ft::map_iterator<T>						iterator;
			typedef ft::const_map_iterator<T>				const_iterator;
			typedef ft::reverse_map_iterator<T>				reverse_iterator;
			typedef ft::const_reverse_map_iterator<T>		const_reverse_iterator;
			class value_compare// : public binary_function<value_type,value_type,bool>
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
			typedef RBtree<value_type, allocator_type> tree_type;
			tree_type	tree;

			typedef struct RBnode<value_type> node;
			allocator_type	t_alloc;
			key_compare		comp;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : \
									t_alloc(alloc), comp(comp)  {};
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : \
									t_alloc(alloc), comp(comp) {};
			map (const map& x) {tree(x.tree);};
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
				return ((*((this->insert(ft::make_pair(k,mapped_type()))).data)).value);
			}

		// Iterator
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
			pair<iterator,bool> insert (const value_type& val)
			{
				node *tmp = tree.search(val);
				if (tmp)
					return (make_pair(iterator(*tmp), false));
				tmp = tree.insertnode(val);
				return (make_pair(iterator(*tmp), true));
			}

			iterator insert (iterator position, const value_type& val)
			{
				node *tmp = tree.serarch(val);
				if (tmp)
					return (iterator(*tmp));
				tmp = tree.insertnode(val);
				return (iterator(*tmp));
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
    };
}

#endif