#ifndef MAP_HPP
# define MAP_HPP

# include "RBT.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        public:
            typedef Key											key_type;
            typedef T											mapped_type;
            typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef T&											reference;
			typedef const T&									const_reference;
			typedef T*											pointer;
			typedef const T *									const_pointer;
			typedef size_t										size_type;
			typedef ft::map_iterator<value_type>			    iterator;
			typedef ft::const_map_iterator<value_type>	const_iterator;
			typedef ft::reverse_map_iterator<value_type>	    reverse_iterator;
			typedef ft::reverse_map_iterator<value_type>	const_reverse_iterator;
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
				return (reverse_iterator(tree.rbegin()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(tree.rbegin()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(tree.rend()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(tree.rend()));
			}

		// Capacity
			bool empty() const
			{
				return (tree.size() == 0);
			}

			size_type size() const
			{
				return (tree.size());
			}

			size_type max_size() const
			{
				return (tree.max_size());
			}


		//Element access
			mapped_type& operator[] (const key_type& k)
			{
 				return ((*((tree.insert(ft::make_pair(k, mapped_type()))).first)).second); 
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

			void erase (iterator position)
			{
				tree.deletenode(*position);
			}

			size_type erase (const key_type& k)
			{
				tree.deletenode(ft::make_pair(k, mapped_type()));
				return (tree.size());
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					tree.deletenode(*first);
					first++;
				}
			}

			void swap (map& x)
			{
				tree.swap(x.tree);
			}

			void clear ()
			{
				tree.clear();
			}

		//Observers
			key_compare key_comp() const
			{
				return (key_compare());
			}

			value_compare value_comp() const
			{
				return (value_compare(tree.value_comp()));
			}

		//Operations
			iterator find (const key_type& k)
			{
				return (iterator(tree.find(ft::make_pair(k, mapped_type()))));
			}

			const_iterator find (const key_type& k) const
			{
				return (const_iterator(tree.find(ft::make_pair(k, mapped_type()))));
			}

			size_type count (const key_type& k) const
			{
				return (tree.count(ft::make_pair(k, mapped_type())));
			}

			iterator lower_bound (const key_type& k)
			{
				return (iterator(tree.lower_bound(ft::make_pair(k, mapped_type()))));
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return (const_iterator(tree.lower_bound(ft::make_pair(k, mapped_type()))));
			}

			iterator upper_bound (const key_type& k)
			{
				return (iterator(tree.upper_bound(ft::make_pair(k, mapped_type()))));
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return (const_iterator(tree.upper_bound(ft::make_pair(k, mapped_type()))));
			}

			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}
			
			ft::pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}

		//Allocator
			allocator_type get_allocator() const
			{
				return (allocator_type());
			}
    };
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		ft::map_iterator<ft::pair<const Key, T> > it1 = lhs.begin();
		ft::map_iterator<ft::pair<const Key, T> >it2 = rhs.begin();
		while (it1 != lhs.end() && it2 != rhs.end())
		{
			if (it1->first != it2->first)
				return (false);
			else if (it1->second != it2->second)
				return (false);
			it1++;
			it2++;
		}
		if (it1 != lhs.end() || it2 != rhs.end())
			return (false);
		return (true);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		size_t	size;
		size_t	i;

		if (lhs.size() > rhs.size())
			size = rhs.size();
		else
			size = lhs.size();
		
		ft::map_iterator<ft::pair<const Key, T> > it1 = lhs.begin();
		ft::map_iterator<ft::pair<const Key, T> > it2 = rhs.begin();
		
		i = -1;
		while (++i < size)
		{
			if (it1->first != it2->first)
				return (it1->first < it2->first);
			else if (it1->second != it2->second)
				return (it1->second < it2->second);
			it1++;
			it2++;
		}
		return (lhs.size() < rhs.size());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		size_t	size;
		size_t	i;

		if (lhs.size() > rhs.size())
			size = rhs.size();
		else
			size = lhs.size();
		
		ft::map_iterator<ft::pair<const Key, T> > it1 = lhs.begin();
		ft::map_iterator<ft::pair<const Key, T> > it2 = rhs.begin();
		
		i = -1;
		while (++i < size)
		{
			if (it1->first != it2->first)
				return (it1->first > it2->first);
			else if (it1->second != it2->second)
				return (it1->second > it2->second);
			it1++;
			it2++;
		}
		return (lhs.size() > rhs.size());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif