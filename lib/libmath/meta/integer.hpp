/*
 * integer.hpp
 *
 *  Created on: Jul 11, 2017
 *      Author: ilion
 */

#ifndef LIB_LIBMATH_META_INTEGER_HPP_
#define LIB_LIBMATH_META_INTEGER_HPP_

#include <cstddef>
#include <cstdint>

namespace libmath {
	namespace meta {

		template<std::size_t Size>
		struct integer {
			using type = void;
			using utype = void;
		};

		template<>
		struct integer<1> {
			using type = std::int8_t;
			using utype = std::uint8_t;
		};

		template<>
		struct integer<2> {
			using type = std::int16_t;
			using utype = std::uint16_t;
		};

		template<>
		struct integer<4> {
			using type = std::int32_t;
			using utype = std::uint32_t;
		};

		template<>
		struct integer<8> {
			using type = std::int64_t;
			using utype = std::uint64_t;
		};

	};
};


#endif /* LIB_LIBMATH_META_INTEGER_HPP_ */
