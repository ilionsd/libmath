#ifndef _LIBMATH_LINEAR_MATRIX_HPP_
#define _LIBMATH_LINEAR_MATRIX_HPP_

#include <vector>
#include <algorithm>
#include <functional>

namespace libmath {
	namespace linear {

		using index_t = std::size_t;

		template<typename T>
		class matrix;

		template<typename T>
		class square_matrix : public matrix<T>;

		template<typename T>
		class rectangular_matrix : public matrix<T>;


		template<typename T>
		void MatrixCopy(const matrix<T> &src, matrix<T> &dst);


		template<typename T>
		class matrix {
		public:
			using index_type = index_t;

			class reference_t {
			public:
				reference_t(matrix<T> *matrixPtr, const index_type row, const index_type col) :
					row_(row),
					col_(col),
					matrix_ptr_(matrixPtr)
				{};

				inline operator const T&() const {
					return matrix_ptr_->get(row_, col_);
				};

				reference_t& operator=(const T &value) {
					matrix_ptr_->set(row_, col_, value);
					return (*this);
				};

			private:
				matrix<T> *matrix_ptr_;

				index_type row_;
				index_type col_;

			};	//-- class reference --

			friend reference_t;

			using const_reference = const T&;
			using reference = reference_t;

			inline matrix() noexcept
			{};

			virtual ~matrix() {};

			virtual index_type rows_number() const = 0;

			virtual index_type cols_number() const = 0;

			inline const_reference operator() (const index_type row, const index_type col) const {
				return get(row, col);
			};

			inline reference operator() (const index_type row, const index_type col) {
				return reference(this, row, col);
			};

			inline const_reference at(const index_type row, const index_type col) const {
				if (row >= rows_number())
					throw std::out_of_range("Rows out of range");
				else if (col >= cols_number())
					throw std::out_of_range("Cols out of range");
				else get(row, col);
			};

			virtual reference at(const index_type row, const index_type col) {
				if (row >= rows_number())
					throw std::out_of_range("Rows out of range");
				else if (col >= cols_number())
					throw std::out_of_range("Cols out of range");
				else reference(this, row, col);
			};



		protected:
			virtual const T& get(const index_type row, const index_type col) const = 0;
			virtual void set(const index_type row, const index_type col, const T& value) = 0;

		};	//-- class matrix<T> --


		template<typename T>
		class square_matrix : public matrix<T> {
		public:
			inline square_matrix(const index_t size) :
				matrix(),
				size_(size)
			{};

			inline index_t size() const {
				return size_;
			};

			inline virtual index_t rows_number() const override {
				return size();
			};

			inline virtual index_t cols_number() const override {
				return size();
			};

			virtual void resize(const index_t size) = 0;

		protected:
			index_t size_;
		};


		template<typename T>
		class rectangular_matrix : public matrix<T> {
		public:
			inline rectangular_matrix(const index_t rowsNumber, const index_t colsNumber) noexcept :
				matrix(),
				rows_number_(rowsNumber),
				cols_number_(colsNumber)
			{};

			inline virtual index_t rows_number() const override {
				return rows_number_;
			};

			inline virtual index_t cols_number() const override {
				return cols_number_;
			};

			virtual void resize(const index_t rowsNumber, const index_t colsNumber) = 0;

		protected:
			index_t rows_number_;
			index_t cols_number_;
		};







		template<typename T>
		void MatrixCopy(const matrix<T> &src, matrix<T> &dst) {
			typename matrix<T>::index_t minRowsNumber = std::min(src.rows_number(), dst.rows_number());
			typename matrix<T>::index_t minColsNumber = std::min(src.cols_number(), dst.cols_number());
			for (typename matrix<T>::index_t row = 0; row < minRowsNumber; row++)
				for (typename matrix<T>::index_t col = 0; col < minColsNumber; col++)
					dst(row, col) = src(row, col);
		};


	};	//-- namespace linear --
};	//-- namespace libmath --

#endif	//-- _LIBMATH_LINEAR_MATRIX_HPP_ --
