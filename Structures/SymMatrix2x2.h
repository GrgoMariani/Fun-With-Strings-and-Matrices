#ifndef SYMMATRIX2X2_H_
#define SYMMATRIX2X2_H_

#include "MatrixItem.h"

#include <string>

class SymMatrix2x2 {
	MatrixItem a11, a12;
	MatrixItem      a22;
public:
	SymMatrix2x2(const char * _a11, const char * _a12, const char * _a22)
					: a11(_a11), a12(_a12), a22(_a22){ }
	SymMatrix2x2(const SymMatrix2x2& r)
					: a11(r.a11), a12(r.a12), a22(r.a22) { }
	SymMatrix2x2(const MatrixItem& _a11, const MatrixItem& _a12, const MatrixItem& _a22)
					: a11(_a11), a12(_a12), a22(_a22) { }

	const SymMatrix2x2 operator+(const SymMatrix2x2& r) const
	{
		return SymMatrix2x2(a11+r.a11,  a12+r.a12,
										a22+r.a22);
	}

	const SymMatrix2x2 operator*(const SymMatrix2x2& r) const
	{
		return SymMatrix2x2(a11*r.a11 + a12*r.a11,  a11*r.a12 + a12*r.a22,
													a12*r.a12 + a22*r.a22);
	}

	SymMatrix2x2& operator+=(const SymMatrix2x2& r)
	{
		a11 += r.a11;
		a12 += r.a12;
		a22 += r.a22;
		return *this;
	}

	SymMatrix2x2& operator*=(const SymMatrix2x2& r)
	{
		MatrixItem temp = a12*r.a12;
		MatrixItem _a11(a11*r.a11 + temp);
		MatrixItem _a12(a11*r.a12 + a12*r.a22);
		temp += a22*r.a22;
		a11.swap(_a11);
		a12.swap(_a12);
		a22.swap(temp);
		return *this;
	}

	SymMatrix2x2 Squared() const
	{
		return SymMatrix2x2(a11*a11 + a12*a12,  a11*a12 + a12*a22,
												a12*a12 + a22*a22);
	}

	SymMatrix2x2 RaiseToPower(unsigned int n)
	{
		SymMatrix2x2 temp_factor(*this);
		SymMatrix2x2 temp_result("1", "0",
									  "1");
		while(n)
		{
			if( n%2 )
				temp_result *= temp_factor;
			n >>= 1;
			temp_factor.Squared().swap(temp_factor);	// temp_factor = temp_factor.Squared();
		}
		return temp_result;
	}

	void swap(SymMatrix2x2& r)
	{
		a11.swap(r.a11);
		a12.swap(r.a12);
		a22.swap(r.a22);
	}

	const std::string getA11() const
	{
		return a11.getAsString();
	}

	const std::string getA12() const
	{
		return a12.getAsString();
	}

	const std::string getA21() const
	{
		return a12.getAsString();
	}

	const std::string getA22() const
	{
		return a22.getAsString();
	}

};


#endif /* SYMMATRIX2X2_H_ */
