#ifndef _LIBMATH_META_GENERATEARRAY_HPP_
#define _LIBMATH_META_GENERATEARRAY_HPP_

#include "meta_array.hpp"

namespace libmath {
	namespace meta {
		namespace utility {
			template<size_t N, template<size_t> class F, unsigned... Args>
			struct generate_array_impl {
				typedef typename generate_array_impl<N - 1, F, F<N>::value, Args...>::type type;
			};

			template<template<size_t> class F, unsigned... Args>
			struct generate_array_impl<0, F, Args...> {
				typedef meta_array<F<0>::value, Args...> type;
			};
		};

		template<size_t N, template<size_t> class F>
		struct generate_array {
			typedef typename utility::generate_array_impl<N, F>::type type;
		};
	};
};

#endif	//-- _LIBMATH_META_GENERATEARRAY_HPP_ --
