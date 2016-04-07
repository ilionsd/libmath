#include <iostream>
#include <vector>

//#include "../../../libmath/linear/normal_matrix.hpp"
//#include "../../../libmath/linear/ndiagonal_matrix.hpp"

#include "../../../libmath/linear/mapper.hpp"

int main() {
	//linear::normal_matrix<double> m(2, 3);
	//linear::ndiagonal_matrix<double, 3> n(5);

	libmath::linear::mapper<double, std::vector> m(1, 2, 3);
	return 0;
}