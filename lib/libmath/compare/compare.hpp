/*
 * compare.hpp
 *
 *  Created on: Jul 9, 2017
 *      Author: ilion
 */

#ifndef LIBMATH_COMPARE_COMPARE_HPP_
#define LIBMATH_COMPARE_COMPARE_HPP_

#include <cmath>
#include <bits/stl_function.h>

namespace libmath {
	namespace compare {

		template<unsigned M, int E>
		struct epsilon_compare :
				public std::binary_function<double, double, bool>
		{
			constexpr static double mantissa = M;
			constexpr static double exponent = E;
			constexpr static double epsilon = mantissa * pow(1.0, exponent);
		};

		template<unsigned M, int E>
		struct equal_to :
				public epsilon_compare<M, E>
		{
			using epsilon_compare<M, E>::epsilon;
			inline constexpr bool operator() (double a, double b) const {
				return fabs(a - b) < epsilon;
			};
		};

		template<unsigned M, int E>
		struct not_equal_to :
				public epsilon_compare<M, E>
		{
			using epsilon_compare<M, E>::epsilon;
			inline constexpr bool operator() (double a, double b) const {
				return fabs(a - b) >= epsilon;
			};
		};

		template<unsigned M, int E>
		struct less :
				public epsilon_compare<M, E>
		{
			using epsilon_compare<M, E>::epsilon;
			inline constexpr bool operator() (double a, double b) const {
				return (a - b) <= -epsilon;
			};
		};

		template<unsigned M, int E>
		struct less_equal :
				public epsilon_compare<M, E>
		{
			using epsilon_compare<M, E>::epsilon;
			inline constexpr bool operator() (double a, double b) const {
				return (a - b) < epsilon;
			};
		};

		template<unsigned M, int E>
		struct greater_equal :
				public epsilon_compare<M, E>
		{
			using epsilon_compare<M, E>::epsilon;
			inline constexpr bool operator() (double a, double b) const {
				return (b - a) < epsilon;
			}
		};

	};	//-- namespace compare --
};	//-- namespace libmath --



#endif /* LIBMATH_COMPARE_COMPARE_HPP_ */
