#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft
{
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };


    template <class Iterator>
    class iterator_traits
    {
        public:
            typedef typename Iterator::iterator_category    iterator_category;
            typedef typename Iterator::reference            reference;
            typedef typename Iterator::pointer              pointer;
            typedef typename Iterator::value_type           value_type;
            typedef typename Iterator::difference_type      difference_type;
    };

    template <class T>
    class iterator_traits<T*>
    {
        public:
            typedef random_access_iterator_tag  iterator_category;
            typedef T			            	value_type;
            typedef T&			            	reference;
            typedef T*			            	pointer;
            typedef std::ptrdiff_t          	difference_type;
    };

    template <class T>
    class iterator_traits<const T*>
    {
        public:
            typedef random_access_iterator_tag  iterator_category;
            typedef const T			            value_type;
            typedef const T&			      	reference;
            typedef const T*		           	pointer;
            typedef std::ptrdiff_t          	difference_type;
    };
}

#endif