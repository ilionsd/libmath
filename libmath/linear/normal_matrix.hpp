#ifndef _LIBMATH_LINEAR_NORMALMATRIX_HPP_
#define _LIBMATH_LINEAR_NORMALMATRIX_HPP_

#include <memory>
#include <functional>

#include "matrix.hpp"

namespace linear {
	template<typename T, template<typename...> typename _Tcontainer>
	class normal_matrix_t;

	template<typename T>
	using normal_matrix = normal_matrix_t<T, std::vector>;


	template<typename T, template<typename...> typename _Tcontainer>
	class normal_matrix_t : public rectangular_matrix<T> {
	public:
		using container_type = _Tcontainer<T>;
		using container_size_type = container_type::size_type;


		using const_reference = matrix<T>::const_reference;
		using reference = matrix<T>::reference;

		inline normal_matrix_t(const index_t rowsNumber, const index_t colsNumber) :
			rectangular_matrix(rowsNumber, colsNumber),
			elements_ptr_(std::make_unique<container_t>(rowsNumber * colsNumber))
		{};

		inline normal_matrix_t(const matrix<T> &other) :
			rectangular_matrix(other.rows_number(), other.cols_number()),
			elements_(other.rows_number() * other.cols_number())
		{
			MatrixCopy(other, (*this));
		};

		virtual void resize(const index_t rowsNumber, const index_t colsNumber) override {
			container_t newElements(rowsNumber * colsNumber);
			index_t minRowsNumber = std::min(rowsNumber, rows_number());
			index_t minColsNumber = std::min(colsNumber, cols_number());
			for (index_t row = 0; row < minRowsNumber; row++)
				for (index_t col = 0; col < minColsNumber; col++)
					newElements[row * colsNumber + col] = elements[index(row, col)];
			//-- as single --
			rows_number_ = rowsNumber;
			cols_number_ = colsNumber;
			elements_.swap(newElements);
		};

	protected:
		inline virtual const T& get(const index_t row, const index_t col) const override {
			return elements_[index(row, col)];
		};

		inline virtual void set(const index_t row, const index_t col, const T& value) override {
			elements_[index(row, col)] = value;
		};

	private:
		inline container_index_t index(const index_t row, const index_t col) const {
			return static_cast<container_index_t>(row) * cols_number() + col;
		};

		container_t elements_;
	};	//-- class normal_matrix<T, C> --






};	//-- namespace linear --

#endif	//-- _LIBMATH_LINEAR_NORMALMATRIX_HPP_ --
