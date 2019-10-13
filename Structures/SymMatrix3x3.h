#ifndef SYMMATRIX3X3_H_
#define SYMMATRIX3X3_H_

#include "MatrixItem.h"

#include <string>

class SymMatrix3x3 {
	MatrixItem a11, a12, a13;
	MatrixItem 		a22, a23;
	MatrixItem			 a33;
public:
	SymMatrix3x3(const char * _a11, const char * _a12, const char * _a13, const char * _a22, const char * _a23, const char * _a33)
					: a11(_a11), a12(_a12), a13(_a13), a22(_a22), a23(_a23), a33(_a33) { }
	SymMatrix3x3(const SymMatrix3x3& r)
					: a11(r.a11), a12(r.a12), a13(r.a13), a22(r.a22), a23(r.a23), a33(r.a33) { }
	SymMatrix3x3(const MatrixItem& _a11, const MatrixItem& _a12, const MatrixItem& _a13, const MatrixItem& _a22, const MatrixItem& _a23, const MatrixItem& _a33)
					: a11(_a11), a12(_a12), a13(_a13), a22(_a22), a23(_a23), a33(_a33) { }

	const SymMatrix3x3 operator+(const SymMatrix3x3& r) const
	{
		return SymMatrix3x3(a11+r.a11, a12+r.a12, a13+r.a13,
									   a22+r.a22, a23+r.a23,
									   	   	   	  a33+r.a33);
	}

	const SymMatrix3x3 operator*(const SymMatrix3x3& r) const
	{
		return SymMatrix3x3(a11*r.a11 + a12*r.a12 + a13*r.a13, a11*r.a12 + a12*r.a22 + a13*r.a23, a11*r.a13 + a12*r.a23 + a13*r.a33,
															   a12*r.a12 + a22*r.a22 + a23*r.a23, a12*r.a13 + a22*r.a23 + a23*r.a33,
																								  a13*r.a13 + a23*r.a23 + a33*r.a33);
	}

	SymMatrix3x3& operator+=(const SymMatrix3x3& r)
	{
		a11 += r.a11;
		a12 += r.a12;
		a13 += r.a13;
		a22 += r.a22;
		a23 += r.a23;
		a33 += r.a33;
		return *this;
	}

	SymMatrix3x3& operator*=(const SymMatrix3x3& r)
	{
		const MatrixItem _a11 = a11*r.a11 + a12*r.a12 + a13*r.a13;
		const MatrixItem _a12 = a11*r.a12 + a12*r.a22 + a13*r.a23;
		const MatrixItem _a13 = a11*r.a13 + a12*r.a23 + a13*r.a33;
		const MatrixItem _a22 = a12*r.a12 + a22*r.a22 + a23*r.a23;
		const MatrixItem _a23 = a12*r.a13 + a22*r.a23 + a23*r.a33;
		const MatrixItem _a33 = a13*r.a13 + a23*r.a23 + a33*r.a33;
		a11 = _a11;
		a12 = _a12;
		a13 = _a13;
		a22 = _a22;
		a23 = _a23;
		a33 = _a33;
		return *this;
	}

	SymMatrix3x3& operator=(const SymMatrix3x3& r)
	{
		a11 = r.a11;
		a12 = r.a12;
		a13 = r.a13;
		a22 = r.a22;
		a23 = r.a23;
		a33 = r.a33;
		return *this;
	}

	const SymMatrix3x3 Squared() const
	{
		return SymMatrix3x3(a11*a11 + a12*a12 + a13*a13, a11*a12 + a12*a22 + a13*a23, a11*a13 + a12*a23 + a13*a33,
														 a12*a12 + a22*a22 + a23*a23, a12*a13 + a22*a23 + a23*a33,
														 	 	 	 	 	 	 	  a13*a13 + a23*a23 + a33*a33);
	}

	SymMatrix3x3 RaiseToPower(unsigned int n)
	{
		SymMatrix3x3 temp_factor(*this);
		SymMatrix3x3 temp_result("1", "0", "0",
									  "1", "0",
									  	   "1");
		while(n)
		{
			if( n%2 )
				temp_result *= temp_factor;
			n >>= 1;
			temp_factor = temp_factor.Squared();
		}
		return temp_result;
	}

	void swap(SymMatrix3x3& r)
	{
		a11.swap(r.a11);
		a12.swap(r.a12);
		a13.swap(r.a13);
		a22.swap(r.a22);
		a23.swap(r.a23);
		a33.swap(r.a33);
	}

	const std::string getA11() const
	{
		return a11.getAsString();
	}

	const std::string getA12() const
	{
		return a12.getAsString();
	}

	const std::string getA13() const
	{
		return a13.getAsString();
	}

	const std::string getA21() const
	{
		return a12.getAsString();
	}

	const std::string getA22() const
	{
		return a22.getAsString();
	}

	const std::string getA23() const
	{
		return a23.getAsString();
	}

	const std::string getA31() const
	{
		return a13.getAsString();
	}

	const std::string getA32() const
	{
		return a23.getAsString();
	}

	const std::string getA33() const
	{
		return a33.getAsString();
	}


};


#endif /* SYMMATRIX3X3_H_ */
