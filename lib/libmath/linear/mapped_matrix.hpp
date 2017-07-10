#ifndef _LIBMATH_LINEAR_MAPPER_HPP_
#define _LIBMATH_LINEAR_MAPPER_HPP_

#include <cstddef>
#include <unordered_map>
#include <algorithm>

#include "../meta/meta_function.hpp"
#include "../meta/generate_array.hpp"

#include "matrix.hpp"

namespace libmath {
	namespace linear {
		namespace mapping {
		
			class mapper {
			public:
				using index_type = index_t;
				using size_type = std::size_t;

				mapper(const index_type rowsNumber, const index_type colsNumber) noexcept :
					rows_number_(rowsNumber),
					cols_number_(colsNumber)
				{};

				inline index_type rows_number() const {
					return rows_number_;
				};

				inline index_type cols_number() const {
					return cols_number_;
				};

				virtual size_type size() const = 0;

				virtual size_type map(const index_type row, const index_type col) const = 0;
				
			private:
				index_type rows_number_;
				index_type cols_number_;

			};


			class normal_mapper : public mapper {
			public:
				using size_type  = mapper::size_type;
				using index_type = mapper::index_type;

				using mapper::mapper;

				inline virtual size_type size() const override {
					return rows_number() * cols_number();
				};

				inline virtual size_type map(const index_type row, const index_type col) const override {
					return row * cols_number() + col;
				};
			};

			template<size_t LowNumber, size_t HighNumber>
			class diagonal_mapper : public mapper {
			public:
				using size_type  = mapper::size_type;
				using index_type = mapper::index_type;

				using mapper::mapper;

				constexpr int low_number() const {
					return LowNumber;
				};

				constexpr int high_number() const {
					return HighNumber;
				}

				constexpr unsigned diagonal_number() const {
					return highest_index() + lowest_index() + 1;
				};

				struct place {
					size_type begin_index;
					size_type end_index;
				};

				

			private:
				using sum_cache = meta::generate_array<std::max(low_number(), high_number()), meta::sum>::type;

				place begin_index(const index_type row) const {
					if (row < low_number()) {
						//-- reduced rows, special mapping --

					}
					else if (row - low_number() + diagonal_number() < cols_number()) {
						//-- diagonal_number elements in row --
					}
					else {
						//-- reduced rows again --
					}
				}

			};



		};	//-- namespace mapping --
	};	//-- namespace linear --
};	//-- namespace libmath --

#endif	//-- _LIBMATH_LINEAR_MAPPER_HPP_ --
