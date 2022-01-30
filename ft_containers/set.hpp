#ifndef SET_HPP
# define SET_HPP

# include "RBT.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T											key_type;
			typedef T											value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			poiner;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::const_tree_iterator<value_type>			iterator;
			typedef ft::const_tree_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

		private:
			typedef RBtree<value_type, value_compare, allocator_type> tree_type;

			tree_type           tree;

		public:
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: tree(value_compare(comp), alloc) {};

			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
				: tree(value_compare(comp), alloc)
			{
				this->insert(first, last);
			}

			set (const set& other) : tree(other.tree) {};

			~set () {}

			set& operator= (const set& other)
			{
				if (this == &other)
					return (*this);
				this->tree = other.tree;
				return (*this);
			}

		//Iterator
			iterator 				begin() { return (tree.begin()); }
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

		// Modifiers
			pair<iterator,bool> 	insert (const value_type& val) { return (tree.insert(val)); }
			iterator 				insert (iterator position, const value_type& val) {	(void)position; return (tree.insert(val).first); }
			template <class InputIterator>
			void 					insert (InputIterator first, InputIterator last) {	return (tree.insert(first, last));	}
			void 					erase (iterator position) { return (tree.erase(position)); }
			size_type 				erase (const value_type& val)	{ return (tree.erase(val)); }
			void 					erase (iterator first, iterator last)	{ return (tree.erase(first, last)); }
			void            		swap (set& x) { return (tree.swap(x.tree)); }
			void           			clear() { return (tree.clear()); }
		
		//Observers
			key_compare				key_comp() const { return (key_compare()); }
			value_compare			value_comp() const { return (value_compare()); }

		//Operations
			iterator				find (const value_type& val) { return (iterator(tree.find(val))); }
			const_iterator			find (const value_type& val) const { return (const_iterator(tree.find(val))); }
			size_type				count (const value_type& val) const { return (tree.count(val)); }
			iterator				lower_bound (const value_type& val) { return (iterator(tree.lower_bound(val))); }
			iterator				upper_bound (const value_type& val) { return (iterator(tree.upper_bound(val))); }
			const_iterator			lower_bound (const value_type& val) const {	return (const_iterator(tree.lower_bound(val))); }
			const_iterator			upper_bound (const value_type& val) const {	return (const_iterator(tree.upper_bound(val))); }
			pair<iterator, iterator> equal_range (const value_type& val)
			{ return (ft::make_pair(this->lower_bound(val), this->upper_bound(val))); }
			pair<const_iterator,const_iterator> equal_range( const value_type& val) const
			{ return (ft::make_pair(this->lower_bound(val), this->upper_bound(val))); }

		//Allocator
			allocator_type get_allocator() const
			{ return (allocator_type()); }
	};

//Non_member
	template<class T, class Compare, class Alloc>
	bool operator==( const ft::set<T,Compare,Alloc>& lhs,
		const ft::set<T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class T, class Compare, class Alloc>
	bool operator!=( const ft::set<T,Compare,Alloc>& lhs,
		const ft::set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template<class T, class Compare, class Alloc>
	bool operator<( const ft::set<T,Compare,Alloc>& lhs,
					const ft::set<T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Compare, class Alloc>
	bool operator<=( const ft::set<T,Compare,Alloc>& lhs,
					const ft::set<T,Compare,Alloc>& rhs )
	{
		return(!(rhs < lhs));
	}

	template<class T, class Compare, class Alloc>
	bool operator>( const ft::set<T,Compare,Alloc>& lhs,
					const ft::set<T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template<class T, class Compare, class Alloc>
	bool operator>=( const ft::set<T,Compare,Alloc>& lhs,
					const ft::set<T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template<class T, class Compare, class Alloc>
	void swap (ft::set<T,Compare,Alloc>& x, ft::set<T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
