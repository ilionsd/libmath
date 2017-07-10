/*
 * floating_point.hpp
 *
 *  Created on: Jul 10, 2017
 *      Author: ilion
 */

#ifndef LIBMATH_META_FLOATING_POINT_HPP_
#define LIBMATH_META_FLOATING_POINT_HPP_

#include <cmath>


namespace libmath {
	namespace meta {

		template<int M, int E>
		struct floating_point {
			constexpr static int mantissa = M;
			constexpr static int exponent = E;
			inline constexpr static double value() const {
				return static_cast<double>(mantissa) * pow(1.0, exponent);
			}
		};

	};	//-- namespace meta --
};	//-- namespace libmath --



#endif /* LIBMATH_META_FLOATING_POINT_HPP_ */
