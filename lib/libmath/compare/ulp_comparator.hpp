/*
 * ulp_comparator.hpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ilion
 */

#ifndef LIB_LIBMATH_COMPARE_ULP_COMPARATOR_HPP_
#define LIB_LIBMATH_COMPARE_ULP_COMPARATOR_HPP_

#include <cstdint>
#include <cmath>

#include "../meta/integer.hpp"

namespace libmath {
	namespace compare {

		template<typename T>
		union ulp_t {
			using floating_point_type = T;
			using integer_type = typename meta::integer<sizeof(T)>::type;

			inline constexpr ulp_t(const T fp) noexcept :
					floating_point(fp)
			{};

			floating_point_type floating_point;
			integer_type integer;
		};

		struct ulp_comparator {
			inline constexpr ulp_comparator(const unsigned ulpDiff = 10) noexcept :
					ulp_diff(ulpDiff)
			{};

			inline constexpr bool equal_to(const double a, const double b) const {
				ulp_t<double> ulpA { a }, ulpB { b };
				if ((ulpA.integer < 0) != (ulpB.integer < 0))
					return a == b;
				else {
					auto ulpDiff = std::abs(ulpA.integer - ulpB.integer);
					return ulpDiff < ulp_diff;
				}
			};

			unsigned ulp_diff;
		};

	};
};



#endif /* LIB_LIBMATH_COMPARE_ULP_COMPARATOR_HPP_ */
