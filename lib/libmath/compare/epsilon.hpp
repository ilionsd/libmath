/*
 * comparator.hpp
 *
 *  Created on: Jul 10, 2017
 *      Author: ilion
 */

#ifndef LIBMATH_COMPARE_EPSILON_COMPARATOR_HPP_
#define LIBMATH_COMPARE_EPSILON_COMPARATOR_HPP_

#include <cmath>
#include <bits/stl_function.h>
#include <algorithm>


namespace libmath {
namespace compare {

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

template<typename F>
struct limited_relative {
    static constexpr double default_rel_tolerance = 1e-5;
    static constexpr double default_abs_tolerance = 1e-8;

    double relTolerance, absTolerance;

    inline limited_relative(
            const double relTolerance = default_rel_tolerance,
            const double absTolerance = default_abs_tolerance) noexcept :
        relTolerance(relTolerance),
        absTolerance(absTolerance)
    {};

    inline constexpr double operator() (const double a, const double b) const {
        return std::max(absTolerance, relTolerance * F {}(std::fabs(a), std::fabs(b)));
    };
};

using limited_max_relative = limited_relative<max<double>>;
using limited_min_relative = limited_relative<min<double>>;

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


template<typename Eps>
struct base_epsilon_comparator : public std::binary_function <double, double, bool> {
    typedef Eps epsilon_type;

    template<typename... Ts>
    inline constexpr base_epsilon_comparator(const Ts... args) :
        epsilon { args... }
    {};

    epsilon_type epsilon;
};


#define DEFINE_COMPARE_OPERATOR( NAME, EXPR ) \
template<typename Eps> \
struct NAME : public base_epsilon_comparator<Eps> { \
    using base_epsilon_comparator<Eps>::epsilon; \
    inline constexpr bool operator() (const double a, const double b) const { return EXPR ; }; \
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


};  //-- namespace compare --
};  //-- namespace libmath --

#endif /* LIBMATH_COMPARE_EPSILON_COMPARATOR_HPP_ */
