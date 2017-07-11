/*
 * comparator.hpp
 *
 *  Created on: Jul 10, 2017
 *      Author: ilion
 */

#ifndef LIBMATH_COMPARE_EPSILON_COMPARATOR_HPP_
#define LIBMATH_COMPARE_EPSILON_COMPARATOR_HPP_

#include <cmath>
#include <algorithm>

namespace libmath {
	namespace compare {

		struct max {
			template<typename T>
			inline constexpr T operator() (const T a, const T b) const {
				return std::max(a, b);
			};
		};
		struct min {
			template<typename T>
			inline constexpr T operator() (const T a, const T b) const {
				return std::min(a, b);
			};
		};

		template<typename F>
		struct limited_relative_epsilon {
			double relTolerance, absTolerance;

			inline limited_relative_epsilon(const double relTolerance = 1e-5, const double absTolerance = 1e-8) noexcept :
					relTolerance(relTolerance),
					absTolerance(absTolerance)
			{};

			inline constexpr double operator() (const double a, const double b) const {
				return std::max(absTolerance, relTolerance * F{}(std::fabs(a), std::fabs(b)));
			};
		};

		using limited_max_relative_epsilon = limited_relative_epsilon<max>;
		using limited_min_relative_epsilon = limited_relative_epsilon<min>;

		template<typename EpsilonT>
		struct epsilon_comparator {
			using epsilon_type = EpsilonT;

			template<typename... Ts>
			inline constexpr epsilon_comparator(const Ts... args) noexcept :
				epsilon(args...)
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
		};

	};
};



#endif /* LIBMATH_COMPARE_EPSILON_COMPARATOR_HPP_ */
