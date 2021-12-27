#ifndef UTILS_HPP
# define UTILS_HPP


namespace ft
{
    template <bool Cond, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <typename T>
    struct is_integral
    {
        //typedef T type;
        static const bool value = false;
    };


    template <>
    struct is_integral<bool> {static const bool value = true;};

    template <>
    struct is_integral<char> {static const bool value = true;};

    template <>
    struct is_integral<signed char> {static const bool value = true;};

    template <>
    struct is_integral<short int> {static const bool value = true;};

    template <>
    struct is_integral<int> {static const bool value = true;};

    template <>
    struct is_integral<long int> {static const bool value = true;};

    template <>
    struct is_integral<long long int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned char> {static const bool value = true;};

    template <>
    struct is_integral<unsigned short int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned long int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned long long int> {static const bool value = true;};

};

#endif