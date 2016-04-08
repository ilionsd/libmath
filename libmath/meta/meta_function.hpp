#ifndef _LIBMATH_META_METAFUNCTION_HPP_
#define _LIBMATH_META_METAFUNCTION_HPP_

namespace libmath {
	namespace meta {

		template<unsigned N>
		struct factorial {
			static constexpr unsigned value = N * factorial<N - 1>::value;
		};

		template<>
		struct factorial<1>	{
			static constexpr unsigned value = 1;
		};

		template<>
		struct factorial<0> {
			static constexpr unsigned value = 1;
		};


		template<unsigned N>
		struct sum {
			static constexpr unsigned value = N + sum<N - 1>::value;
		};

		template<>
		struct sum<0> {
			static constexpr unsigned value = 0;
		};
	};
};


#endif	//-- _LIBMATH_META_METAFUNCTION_HPP_ --
