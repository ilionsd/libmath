#ifndef _LIBMATH_LINEAR_TRIANGULARMATRIX_HPP_
#define _LIBMATH_LINEAR_TRIANGULARMATRIX_HPP_

#include <memory>

#include "matrix.hpp"

namespace linear {



	template<typename T, template<typename...> typename C>
	class triangular_matrix : public matrix<T> {
	public:
		using container_t = C<T>;

	private:


		std::unique_ptr<container_t> elements_ptr_;
	};
};	//-- namespace linear --

#endif	//-- _LIBMATH_LINEAR_TRIANGULARMATRIX_HPP_ --
