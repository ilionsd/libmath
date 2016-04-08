#include <iostream>
#include <vector>


#include "../../../libmath/meta/meta_function.hpp"
#include "../../../libmath/meta/generate_array.hpp"

using std::cout;
using std::endl;

int main() {
	//linear::normal_matrix<double> m(2, 3);
	//linear::ndiagonal_matrix<double, 3> n(5);

	cout << libmath::meta::factorial<5>::value << endl;

	typedef libmath::meta::generate_array<5, libmath::meta::sum>::type factor5;

	for (size_t k = 0; k < factor5::size; k++)
		cout << factor5::data[k] << endl;

	std::system("pause");
	return 0;
}