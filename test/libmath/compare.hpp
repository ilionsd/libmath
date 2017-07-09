/*
 * compare.hpp
 *
 *  Created on: Jul 9, 2017
 *      Author: ilion
 */

#ifndef TEST_COMPARE_HPP_
#define TEST_COMPARE_HPP_

#include <iostream>
#include <cassert>
#include <bits/stl_function.h>

#include "../../include/libmath/compare.hpp"


namespace test {
	namespace libmath {

		template<typename C1, typename C2>
		struct compare_difference {
			template<typename T>
			constexpr bool operator() (const T a, const T b) const {
				return C1{}(a, b) == C2{}(a, b);
			}
		};

		void test_compare() {
			using std::cout;
			using std::endl;
			cout << "libmath::compare test... ";
			namespace ecmp = ::libmath::compare;
			ecmp::less_equal<1, -9> ele;
			assert(ele(1.0 / 3.0, 0.333333333) == true);
			cout << "ok" << endl;
		};

	};
};

#endif /* TEST_COMPARE_HPP_ */
