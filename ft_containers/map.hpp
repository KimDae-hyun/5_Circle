#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "RBT.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair< const Key, T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			poiner;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::tree_iterator<value_type>				iterator;
			typedef ft::const_tree_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::size_t									size_type;
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare	comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			typedef RBtree<value_type, value_compare, allocator_type> tree_type;
			tree_type	tree;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: tree(value_compare(comp), alloc) {};

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
				: tree(value_compare(comp), alloc)
			{
				this->insert(first, last);
			}

			map (const map& x) : tree(x.tree) {};

			~map () {};

			map& operator= (const map& other)
			{
				if (this == &other)
					return (*this);
				this->tree = other.tree;
				return (*this);
			}

		//Iterator
			iterator 				begin(){ return (tree.begin()); }
			const_iterator 			begin() const { return (tree.begin()); }
			iterator 				end() {  return (tree.end()); }
			const_iterator	 		end() const {  return (tree.end()); }
			reverse_iterator		rbegin() { return (tree.rbegin()); }
			const_reverse_iterator 	rbegin() const { return (tree.rbegin()); }
			reverse_iterator 		rend() {  return (tree.rend()); }
			const_reverse_iterator 	rend() const {  return (tree.rend()); }

		// Capacity
			bool 					empty() const { return (this->tree.empty()); }
			size_type 				size() const { return (this->tree.size()); }
			size_type 				max_size() const { return (tree.max_size()); }

		//Element access
			mapped_type& operator[] (const key_type& key) { return (insert(ft::make_pair(key, mapped_type())).first->second); }

		// Modifiers
			pair<iterator,bool> 	insert (const value_type& val) { return (tree.insert(val)); }
			iterator 				insert (iterator position, const value_type& val) { return (tree.insert(position, val)); }
			template <class InputIterator>
			void 					insert (InputIterator first, InputIterator last) {	return (tree.insert(first, last));	}
			void 					erase (iterator position) { return (tree.erase(position)); }
			size_type 				erase (const key_type& key)	{ return (tree.erase(ft::make_pair(key, mapped_type()))); }
			void 					erase (iterator first, iterator last)	{ return (tree.erase(first, last)); }
			void            		swap (map& x) { return (tree.swap(x.tree)); }
			void           			clear() { return (tree.clear()); }

		//Observers
			key_compare				key_comp() const { return (key_compare()); }
			value_compare			value_comp() const { return (value_compare(key_compare())); }

		//Operations
			iterator				find (const key_type& key) { return (iterator(tree.find(ft::make_pair(key, mapped_type())))); }
			const_iterator			find (const key_type& key) const { return (const_iterator(tree.find(ft::make_pair(key, mapped_type())))); }
			size_type				count (const key_type& key) const { return (tree.count(ft::make_pair(key, mapped_type()))); }
			iterator        		lower_bound (const key_type& key) {	return (iterator(tree.lower_bound(ft::make_pair(key, mapped_type())))); }
			iterator        		upper_bound (const key_type& key) {	return (iterator(tree.upper_bound(ft::make_pair(key, mapped_type())))); }
			const_iterator			lower_bound (const key_type& key) const {	return (const_iterator(tree.lower_bound(ft::make_pair(key, mapped_type())))); }
			const_iterator			upper_bound (const key_type& key) const {	return (const_iterator(tree.upper_bound(ft::make_pair(key, mapped_type())))); }
			pair<const_iterator, const_iterator> equal_range (const key_type& key) const
			{ return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }
			pair<iterator, iterator> equal_range (const key_type& key)
			{ return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }

		//Allocator
			allocator_type get_allocator() const { return (allocator_type()); }
	};

	//Non_member
	template<class Key, class T, class Compare, class Alloc>
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return(!(rhs < lhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
