#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <string>

/* Add one string fast to another reference */
static inline void Add_to_left_No_trim_With_offset(std::string& final_sum, const std::string& value, int offset)
{
	unsigned char carry = 0;
	int i = final_sum.size() - offset -1;
	for(int j=value.size()-1; j>=0; j--)
	{
		unsigned char temp = final_sum[i] + value[j] + carry;
		carry = temp/10;
		temp %= 10;
		final_sum[i] = temp;
		i--;
	}
	while (carry)
	{
		unsigned char temp = final_sum[i] + carry;
		carry = temp/10;
		temp %= 10;
		final_sum[i] = temp;
		i--;
	}
}

/* Trim the leading 0s of the string */
static inline void trim(std::string& value)
{
	value.erase(0, value.find_first_not_of((char)0));
	if(!value.size())
		value.insert(value.begin(), 1, 0);
}


class StringHelper {
public:
	enum class CompareResult
	{
		SMALLER,
		BIGGER,
		EQUAL
	};

	static std::string add(const std::string& bigger_s, const std::string& smaller_s)
	{
		std::string result(bigger_s.size()+1, 0);

		int b_i = bigger_s.size()-1;
		int s_i = smaller_s.size()-1;

		unsigned char carry = 0;
		while ( s_i >= 0 )
		{
			unsigned char temp = (unsigned char)(smaller_s[s_i] + bigger_s[b_i] + carry);
			carry = temp/10;
			temp %= 10;
			result[b_i+1] = temp;
			--s_i, --b_i;
		}
		while ( b_i >= 0 )
		{
			unsigned char temp = bigger_s[b_i] + carry;
			carry = temp/10;
			temp %= 10;
			result[b_i+1] = temp;
			--b_i;
		}
		result[0] = carry;
		trim(result);
		return result;
	}

	static std::string mul(const std::string& bigger_s, const std::string& smaller_s)
	{
		std::string result(bigger_s.size()+smaller_s.size(), 0);

		std::string temp_results[10];
		temp_results[1].insert(temp_results[1].begin(), smaller_s.size()+1, 0);
		for(unsigned int i=0; i<smaller_s.size(); i++)
			temp_results[1][i+1] = smaller_s[i];

		for (unsigned char i=2; i<10; i++)					// Create a temp map
		{
			temp_results[i] = std::string(temp_results[1].size(), 0);

			unsigned char carry = 0;
			for (int i_r = temp_results[i].size()-1; i_r>=0; i_r--)
			{
				unsigned char temp = i * temp_results[1][i_r] + carry;
				carry = temp/10;
				temp %= 10;
				temp_results[i][i_r] = temp;
			}
		}
		for (int i_l = bigger_s.size()-1; i_l>=0; i_l--)	// add the calculated sums from the temp map
		{
			unsigned char temp_factor = bigger_s[i_l];
			if (temp_factor == 0)
				continue;
			Add_to_left_No_trim_With_offset(result, temp_results[temp_factor], bigger_s.size()-i_l-1);
		}
		trim(result);
		return result;
	}

	static CompareResult LeftComparedToRight(const std::string& left, const std::string& right)
	{
		if( left.size() < right.size() )
			return CompareResult::SMALLER;
		if( left.size() > right.size() )
			return CompareResult::BIGGER;
		for (unsigned int i=0; i<left.size(); i++)
		{
			if( left[i] < right[i])
				return CompareResult::SMALLER;
			if( left[i] > right[i])
				return CompareResult::BIGGER;
		}
		return CompareResult::EQUAL;
	}

	static std::string sub(const std::string& bigger_s, const std::string& smaller_s)
	{
		std::string result(bigger_s.size(), 0);

		int b_i = bigger_s.size()-1;
		int s_i = smaller_s.size()-1;

		unsigned char carry = 0;
		while ( s_i >= 0 )
		{
			unsigned char temp = (unsigned char)(10 + bigger_s[b_i] - smaller_s[s_i] - carry);
			carry = 1 - temp/10;
			temp %= 10;
			result[b_i] = temp;
			--s_i, --b_i;
		}
		while ( b_i >= 0 )
		{
			unsigned char temp = 10+bigger_s[b_i] - carry;
			carry = 1 - temp/10;
			temp %= 10;
			result[b_i] = temp;
			--b_i;
		}
		result[0] -= carry;

		trim(result);
		return result;
	}
};

#endif /* STRINGHELPER_H_ */
