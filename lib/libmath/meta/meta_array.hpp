#ifndef _LIBMATH_META_METAARRAY_HPP_
#define _LIBMATH_META_METAARRAY_HPP_

namespace libmath {
	namespace meta {

		template<unsigned... Args>
		struct meta_array {
			static const size_t size = sizeof...(Args);
			static const unsigned data[size];
		};

		template<unsigned... Args>
		const unsigned meta_array<Args...>::data[meta_array<Args...>::size] = { Args... };

	};
};

#endif	//-- _LIBMATH_META_METAARRAY_HPP_ --
