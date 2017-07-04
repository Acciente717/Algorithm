/*
#########################
###     accalgo.h     ###
###      By Acc.      ###
###      Ver 1.0      ###
###    2017-07-04     ###
#########################

Algorithms included:

Cantor Expansion:
	long long cantor(RanIt _start, RanIt _end);

Reverse Cantor Expansion:
	void cantor_reverse(RanIt _start, RanIt _end, long long arrangeNum);

KMP:
	char *strstr_KMP(char *target, char *pattern);

*/

namespace acc
{

	/*
	#########################
	Cantor Expansion
	Last modified: 2017-07-04
	Version: 1.1
	#########################
	*/
	const long long factRow[] = { 0,0,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,
		6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000 };

	template <class RanIt>
	long long cantor(RanIt _start, RanIt _end)
	{
		int len = _end - _start;
		if (len > 19) throw "Cantor Expansion overflow! Input length limit exceeded!";
		long long result = 0;
		int reverseNum;
		for (; _start != _end; ++_start)
		{
			reverseNum = 0;
			for (RanIt it = _start + 1; it != _end; ++it)
				if (*it < *_start) ++reverseNum;
			result += reverseNum * factRow[_end - _start];
		}
		return result;
	}

	template <class RanIt>
	void cantor_reverse(RanIt _start, RanIt _end, long long arrangeNum)
	{
		int len = _end - _start;
		if (len > 19) throw "Reverse Cantor Expansion overflow! Input length limit exceeded!";
		if (arrangeNum < 0 || arrangeNum >= factRow[len + 1]) throw "Reverse Cantor Expansion: Invalid arrangement number!";
		for (; _start != _end - 1; ++_start)
		{
			sort(_start, _end);
			swap(*_start, *(_start + arrangeNum / factRow[_end - _start]));
			arrangeNum %= factRow[_end - _start];
		}
	}
	// Cantor Expansion End.


	/*
	#########################
	KMP
	Last modified: 2017-07-04
	Version: 1.2
	#########################
	*/

	static int GetLength(char *str)
	{
		for (char *p = str;; p++)
			if (*p == '\0')
				return p - str;
	}

	static void GenerateNextArray(char *str, int length, int* next)
	{
		next[0] = -1;
		int i = 0, k = -1;
		while (i < length - 1)
		{
			while (k >= 0 && str[i] != str[k])
				k = next[k];
			k++;
			i++;
			if (str[i] == str[k])
				next[i] = next[k];
			else
				next[i] = k;
		}
	}

	char *strstr_KMP(char *target, char *pattern)
	{
		int j = 0;
		int patternLen = GetLength(pattern);
		int *next = new int[patternLen];
		char *p = target;
		GenerateNextArray(pattern, patternLen, next);
		while (*p != '\0' && j < patternLen)
		{
			if (j == -1 || *p == pattern[j])
			{
				p++;
				j++;
			}
			else
				j = next[j];
		}
		delete[] next;
		if (j >= patternLen)
			return target + (p - target - patternLen);
		else
			return 0;
	}
	// KMP End.
}