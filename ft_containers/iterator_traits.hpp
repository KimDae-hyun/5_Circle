#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <iostream>

namespace ft
{
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };


    template <typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
    };

    template <typename T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T			            	value_type;
        typedef T&			            	reference;
        typedef T*			            	pointer;
        typedef std::ptrdiff_t          	difference_type;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T			            value_type;
        typedef const T&			      	reference;
        typedef const T*		           	pointer;
        typedef std::ptrdiff_t          	difference_type;
    };

	template <	typename Category, typename T, typename Distance = ptrdiff_t,
                typename Pointer = T*, typename Reference = T& >
	struct	iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};
}

#endif