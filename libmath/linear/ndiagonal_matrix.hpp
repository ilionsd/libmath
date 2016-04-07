#ifndef _LIBMATH_LINEAR_NDIAGONALMATRIX_HPP_
#define _LIBMATH_LINEAR_NDIAGONALMATRIX_HPP_

#include <memory>
#include <array>
#include <utility>
#include <cstdlib>
#include <algorithm>

#include "matrix.hpp"

namespace linear {

	using diagonal_number_t = unsigned;

	template<diagonal_number_t DiagonalNumber>
	struct middle_index {
		static const diagonal_number_t value = DiagonalNumber / 2 + 1;
	};

	template<typename SpecifiedContainer, diagonal_number_t DiagonalNumber>
	void AllocDiagonals(std::array <SpecifiedContainer, DiagonalNumber> &diags, const index_t size);

	template<diagonal_number_t DiagonalNumber>
	inline diagonal_number_t DiagIndex(const index_t row, const index_t col);

	inline diagonal_number_t ItemIndex(const index_t row, const index_t col);


	template<typename T, diagonal_number_t DiagonalNumber, template<typename...> typename _Tcontainer>
	class ndiagonal_matrix_t;


	template<typename T, diagonal_number_t DiagonalNumber>
	using ndiagonal_matrix = ndiagonal_matrix_t<T, DiagonalNumber, std::vector>;


	template<typename T, diagonal_number_t DiagonalNumber, template<typename...> typename _Tcontainer>
	class ndiagonal_matrix_t : public matrix<T> {
	public:
		
		static_assert(DiagonalNumber % 2 == 1, "Number of diagonals can be only odd!");

		using container_t = _Tcontainer<T>;

		using const_reference = matrix<T>::const_reference;
		using reference = matrix<T>::reference;

		ndiagonal_matrix_t(const index_t size) :
			matrix(),
			size_(size),
			diagonals_ptr_(std::make_unique<std::array<container_t, DiagonalNumber>>())
		{
			AllocDiagonals(*diagonals_ptr_, size);
		};

		inline index_t size() const {
			return size_;
		};

		inline virtual index_t rows_number() const override {
			return size();
		};

		inline virtual index_t cols_number() const override {
			return size();
		};

		diagonal_number_t diagonal_number() const {
			return DiagonalNumber;
		};

		void resize(const index_t size) {
			auto newDiagonalsPtr = std::make_unique<std::array<container_t, DiagonalNumber>>();
			index_t minSize = std::min(this->size(), size);
			AllocDiagonals(*newDiagonalsPtr, size);
			diagonal_number_t mid = middle_index<DiagonalNumber>::value;
			DiagonalCopy(diagonals()[mid], (*newDiagonalsPtr)[mid], minSize);
			for (diagonal_number_t diagDiff = 1; diagDiff < DiagonalNumber / 2; diagDiff++) {
				DiagonalCopy(diagonals()[mid - diagDiff], (*newDiagonalsPtr)[mid - diagDiff], minSize - diagDiff);
				DiagonalCopy(diagonals()[mid + diagDiff], (*newDiagonalsPtr)[mid + diagDiff], minSize - diagDiff);
			};
		};

	protected:
		inline virtual const T& get(const index_t row, const index_t col) const {
			return diagonals()[DiagIndex<DiagonalNumber>(row, col)][ItemIndex(row, col)];
		};

		inline virtual void set(const index_t row, const index_t col, const T& value) {
			diagonals()[DiagIndex<DiagonalNumber>(row, col)][ItemIndex(row, col)] = value;
		};

	private:
		inline const std::array <container_t, DiagonalNumber>& diagonals() const {
			return *diagonals_ptr_;
		};

		inline std::array <container_t, DiagonalNumber>& diagonals() {
			return *diagonals_ptr_;
		};

		index_t size_;
		std::unique_ptr<std::array <container_t, DiagonalNumber>> diagonals_ptr_;

	};	//-- class matrix<T> --

	template<typename SpecifiedContainer, diagonal_number_t DiagonalNumber>
	inline void AllocDiagonals(std::array <SpecifiedContainer, DiagonalNumber> &diags, const index_t size) {
		diagonal_number_t mid = middle_index<DiagonalNumber>::value;
		diags[mid].resize(size);
		for (diagonal_number_t diagDiffIndex = 1; diagDiffIndex < mid; diagDiffIndex++) {
			diags[mid - diagDiffIndex].resize(size - diagDiffIndex);
			diags[mid + diagDiffIndex].resize(size - diagDiffIndex);
		}
	};

	template<diagonal_number_t DiagonalNumber>
	inline diagonal_number_t DiagIndex(const index_t row, const index_t col) {
		diagonal_number_t index = row - col + middle_index<DiagonalNumber>::value;
		return index;
	};

	inline diagonal_number_t ItemIndex(const index_t row, const index_t col) {
		diagonal_number_t index = std::max(row, col) - abs(static_cast<signed long long>(row) - col);
		return index;
	};

	template<typename C>
	inline void DiagonalCopy(const C& src, C& dst, const index_t copySize) {
		std::copy(src.begin(), src.begin() + copySize, dst.begin());
	};

};	//-- namespace linear --

#endif	//-- _LIBMATH_LINEAR_NDIAGONALMATRIX_HPP_ --
