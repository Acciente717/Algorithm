/*
#########################
###     cantor.h      ###
###      By Acc.      ###
###      Ver 1.1      ###
###    2017-07-04     ###
#########################
*/


const long long factRow[] = { 0,0,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,
6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000 };

// Calculate the Cantor Expansion number. Range from 0 to n!-1.
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

// Given the Cantor Expansion number, modify the sequence to that given arrangement.
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