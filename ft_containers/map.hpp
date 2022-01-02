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
			}
		private:
			key_type	key;
			mapped_type	;
			value_type	val;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			map (const map& x);
			~map();
    };
}

#endif