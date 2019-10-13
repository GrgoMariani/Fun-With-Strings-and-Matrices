#include <iostream>
#include <string>

#include "Structures/Matrix3x3.h"
#include "Structures/SymMatrix3x3.h"
#include "Structures/SymMatrix2x2.h"

int _main_(int argc, char ** argv)
{

	std::cout << std::endl << "Fibonacci:" << std::endl;

	SymMatrix2x2 fibonacci("1", "1",
								"0");

	for(int i=0; i<30; i++)
		std::cout << fibonacci.RaiseToPower(i).getA11() << std::endl;

	std::cout << std::endl << "Squares:" << std::endl;

	Matrix3x3 m3x3(	"2", "1", "0",
					"-1", "0", "0",
					"2", "0", "1");

	Matrix3x3 m3x3_1(	"1", "0", "1",
						"0", "0", "0",
						"0", "0", "0");

	for(int i=0; i<30; i++)
		std::cout << (m3x3_1*m3x3.RaiseToPower(i)).getA11() << std::endl;
    return 0;
}
