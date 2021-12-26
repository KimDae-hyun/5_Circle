#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

namespace ft
{
    template <class T, class Alloc = allocator<T>> 
    class vector
    {
        private:
            pointer                                                 v_data;
            size_type                                               v_size;
            size_type                                               v_capacity;
            allocator_type                                          v_alloc;

            size_type _recommend_size(size_type new_size) const;

        public:
            typedef T                                               value_type;
            typedef Allocator                                       allocator_type;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::size_type              size_type;
            typedef typename allocator_type::difference_type        difference_type;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef ft::vector_iterator<pointer>                    iterator;
            typedef ft::vector_iterator<const_pointer>              const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

            explicit    vector (const allocator_type& alloc = allocator_type());
            explicit    vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            vector (const vector& x);

            void    push_back(const value_type& x);
            void    reserve(size_type n);

            
    };
}

namespace ft
{
    templete <class T, class Alloc>
    vector<T, Alloc>::explicit vector(const allocator_type& alloc = allocator_type()) = v_data(NULL), v_size(0), v_capacity(0), v_alloc(alloc) {}

    templete <class T, class Alloc>
    vector<T, Alloc>::explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())\
    = v_data(NULL), v_size(n), v_capacity(n), v_alloc(alloc)
    {
        if (n > 0)
        {
            v_data = v_alloc.allocate(size);
            for (size_type i = 0; i < n; i++)
            {
                v_data[i] = val;
            }
        }
    }

    templete <class T, class Alloc>
    template <class InputIterator>
    vector<T, Alloc>::vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) = v_alloc(alloc)
    {
        v_size = 0;
        v_capacity = 0;
        v_data = NULL;
        for (; first != last; first++)
            push_back(*first);
        pointer v_new = v_alloc.allocate(v_size); // capacity등을 최대값과 맞춰주기 위한 과정이 필요
        for (size_type i = 0; i < v_size; i++)
            v_new[i] = v_data[i];
        v_alloc.deallocate(v_data, v_capacity);
        v_data = v_new_data;
        v_capacity = v_size;
    }

    templete <class T, class Alloc>
    vector<T, Alloc>::vector (const vector& x)
    {
        if (this != &x)
        {
            *this = x;
        }
    }
}

#endif