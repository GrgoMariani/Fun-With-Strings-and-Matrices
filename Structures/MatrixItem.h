#ifndef MATRIXITEM_H_
#define MATRIXITEM_H_

#include "StringHelper.h"

#include <string>

class MatrixItem {
	std::string value;
	bool isPositive;
private:
	MatrixItem()							: value(), isPositive(true)					{ }	// only used as temp variable
public:
	MatrixItem(const char * _value) 		: value(_value), isPositive(true)
	{
		if(value[0] == '-')
		{
			value.erase(0, 1);
			isPositive = false;
		}
		for(auto& c: value)
			c -= '0';
	}

	MatrixItem(const MatrixItem& r) 		: value(r.value), isPositive(r.isPositive)	{ }

	std::string getAsString() const
	{
		std::string result;
		if (!isPositive)
			result += "-";
		for(auto& c: value)
			result += c + '0';
		return result;
	}

	std::string::size_type size() const
	{
		return value.size();
	}

	MatrixItem operator+(const MatrixItem& r) const
	{
		MatrixItem result;
		if( isPositive == r.isPositive)
		{
			if ( size() > r.size() )
				StringHelper::add(value, r.value).swap(result.value);
			else
				StringHelper::add(r.value, value).swap(result.value);
			result.isPositive = isPositive;
		}
		else
		{
			switch (StringHelper::LeftComparedToRight(r.value, value))
			{
			case StringHelper::CompareResult::SMALLER:
				StringHelper::sub(value, r.value).swap(result.value);
				result.isPositive = isPositive;
				break;
			case StringHelper::CompareResult::BIGGER:
				StringHelper::sub(r.value, value).swap(result.value);
								result.isPositive = r.isPositive;
				break;
			case StringHelper::CompareResult::EQUAL:
				result.value.insert(result.value.begin(), 1, 0);
				result.isPositive = true;
				break;
			}
		}
		return result;
	}

	MatrixItem operator*(const MatrixItem& r) const
	{
		MatrixItem result;
		if ( size() > r.size() )
			StringHelper::mul(value, r.value).swap(result.value);
		else
			StringHelper::mul(r.value, value).swap(result.value);
		if ( isPositive != r.isPositive)
			result.isPositive = false;
		return result;
	}

	MatrixItem& operator+=(const MatrixItem& r)
	{
		if ( isPositive == r.isPositive )
		{
			if ( size() > r.size() )
				StringHelper::add(value, r.value).swap(value);
			else
				StringHelper::add(r.value, value).swap(value);
		}
		else
		{
			switch (StringHelper::LeftComparedToRight(r.value, value))
			{
			case StringHelper::CompareResult::SMALLER:
				StringHelper::sub(value, r.value).swap(value);
				break;
			case StringHelper::CompareResult::BIGGER:
				StringHelper::sub(r.value, value).swap(value);
				isPositive = r.isPositive;
				break;
			case StringHelper::CompareResult::EQUAL:
				value.clear();
				value.insert(value.begin(), 1, 0);
				isPositive = true;
				break;
			}
		}
		return *this;
	}

	MatrixItem operator*=(const MatrixItem& r)
	{
		if ( size() > r.size() )
			StringHelper::mul(value, r.value).swap(value);
		else
			StringHelper::mul(r.value, value).swap(value);
		if( (!r.isPositive && isPositive) || (r.isPositive && !isPositive))
			isPositive = false;
		else
			isPositive = true;
		return *this;
	}

	void swap(MatrixItem& r)
	{
		value.swap(r.value);
		std::swap(isPositive, r.isPositive);
	}

};



#endif /* MATRIXITEM_H_ */
