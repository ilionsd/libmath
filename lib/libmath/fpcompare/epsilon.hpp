/*
 * comparator.hpp
 *
 *  Created on: Jul 10, 2017
 *      Author: ilion
 */

#ifndef LIBMATH_FPCOMPARE_EPSILON_HPP_
#define LIBMATH_FPCOMPARE_EPSILON_HPP_

#include <cmath>
#include <bits/stl_function.h>
#include <algorithm>


namespace libmath {
namespace fpcompare {

template<typename T>
struct max {
    inline constexpr T operator()(const T a, const T b) const {
        return std::max(a, b);
    };
};
template<typename T>
struct min {
    inline constexpr T operator()(const T a, const T b) const {
        return std::min(a, b);
    };
};

template<typename T>
struct epsilon_traits {
    typedef T value_type;
    static constexpr value_type default_rel_tolerance = 0;
    static constexpr value_type default_abs_tolerance = 0;
};
template<>
struct epsilon_traits<float> {
    typedef float value_type;
    static constexpr value_type default_rel_tolerance = 1e-3;
    static constexpr value_type default_abs_tolerance = 1e-5;
};
template<>
struct epsilon_traits<double> {
    typedef double value_type;
    static constexpr value_type default_rel_tolerance = 1e-5;
    static constexpr value_type default_abs_tolerance = 1e-8;
};



template<typename T, typename F>
struct limited_relative {
    typedef T value_type;
    typedef epsilon_traits<value_type> traits;

    inline constexpr limited_relative(
            const value_type relTolerance = traits::default_rel_tolerance,
            const value_type absTolerance = traits::default_abs_tolerance) noexcept :
        relTolerance(relTolerance),
        absTolerance(absTolerance)
    {};

    inline constexpr value_type operator() (const value_type a, const value_type b) const {
        return std::max(absTolerance, relTolerance * F {}(std::fabs(a), std::fabs(b)));
    };

    value_type relTolerance, absTolerance;
};


template<typename T>
using limited_relative_max = limited_relative<T, max<T>>;
template<typename T>
using limited_relative_min = limited_relative<T, min<T>>;


template<typename Eps>
struct epsilon_comparator {
    using epsilon_type = Eps;

    template<typename ... Ts>
    inline constexpr epsilon_comparator(const Ts ... args) noexcept :epsilon(args...)
    {};

    inline constexpr bool equal_to(const double a, const double b) const {
        return std::fabs(a - b) < epsilon(a, b);
    };
    inline constexpr bool less_equal(const double a, const double b) const {
        return a - b < epsilon(a, b);
    };
    inline constexpr bool greater_equal(const double a, const double b) const {
        return a - b > epsilon(a, b);
    };

    inline constexpr bool not_equal_to(const double a, const double b) const {
        return !equal_to(a, b);
    };
    inline constexpr bool less(const double a, const double b) const {
        return !greater_equal(a, b);
    };
    inline constexpr bool greater(const double a, const double b) const {
        return !less_equal(a, b);
    };

    epsilon_type epsilon;
};  //-- struct epsilon_comparator --


template<typename T, template<typename > class Eps>
struct base_epsilon_comparator : public std::binary_function <T, T, bool> {
    typedef T value_type;
    typedef Eps<value_type> epsilon_type;

    template<typename... Ts>
    inline constexpr base_epsilon_comparator(const Ts... args) :
        epsilon { args... }
    {};

    epsilon_type epsilon;
};


#define DEFINE_COMPARE_OPERATOR( NAME, EXPR )                                                                \
template<typename T, template<typename > class Eps>                                                          \
struct NAME : public base_epsilon_comparator<T, Eps> {                                                       \
    typedef base_epsilon_comparator<T, Eps> base_type;                                                       \
    using typename base_type::value_type;                                                                    \
    using base_type::base_type;                                                                              \
    using base_type::epsilon;                                                                                \
    inline constexpr bool operator() (const value_type a, const value_type b) const { return EXPR ; };       \
};

/*
 * definition of ==, !=
 */
DEFINE_COMPARE_OPERATOR(     equal_to , std::fabs(a - b) <  epsilon(a, b) )
DEFINE_COMPARE_OPERATOR( not_equal_to , std::fabs(a - b) >= epsilon(a, b) )

/*
 * definition of <, >=
 */
DEFINE_COMPARE_OPERATOR(          less , a - b <= -epsilon(a, b) )
DEFINE_COMPARE_OPERATOR( greater_equal , a - b >  -epsilon(a, b) )

/*
 * definition of >, <=
 */
DEFINE_COMPARE_OPERATOR(    greater , a - b >= epsilon(a, b) )
DEFINE_COMPARE_OPERATOR( less_equal , a - b <  epsilon(a, b) )


};  //-- namespace fpcompare --
};  //-- namespace libmath --

#endif /* LIBMATH_FPCOMPARE_EPSILON_HPP_ */
