/*
	#########################
	### DichotomyLocate.h ###
	###      By Acc.      ###
	###      Ver 1.0      ###
	###    2017-02-22     ###
	#########################

	*** WARING ***
	You should always sort the array (in a particular way) before using this function.

	This function is used to locate a particular position by using dichotomy.
	Those parameters stand for :
		base: point to the array that want to search in.
		num: the number of the elements in the array.
		size: the size of the element in the array (count by bytes).
		
		(*ncomp): normal-comparison function
			parameters in comp function:
				baseLeft: point to the first element in the array.
				baseRight: point to the last element in the array.
				tempLeft: point to the first element in the temporary segment.
				tempRight: point to the last element in the temporary segment.
				middle: point to the middle element in the temporary segment.
			When returning "false", the left border of the temporary segment will be given the value of "middle".
			That is, the right half segment will do the next round of search.
			When returning "true", the right border of the temporary segment will be given the value of "middle".
			That is, the left half segment will do the next round of search.

		What is the "critical" situcation?
		During the cycle, "ncomp" function will be implemented, and the "tempLeft" & "tempRight" pointer will get closer to each other.
		Meanwhile, those two pointers will also get closer to the target position set by the logic of your own "ncomp" function.
		The "critical" situation occurs when the two pointers are located between each other.
		That is: (char*)tempLeft + sizeof(YOUR_ELEMENT) == (char*)tempRight
		When such thing happens, you have to choose one between "tempLeft" and "tempRight" to be your final result.
		The choosing logic should be defined by the function "ccomp".

		(*ccomp): critical-comparison function
			parameters in comp function:
				baseLeft: point to the first element in the array.
				baseRight: point to the last element in the array.
				tempLeft: point to the first element in the temporary segment.
				tempRight: point to the last element in the temporary segment.
			When returning "false", the pointer on the left will be chosen as the final result.
			Otherwise, the pointer on the right will be chosen.
		
	Example:
		Given array:
			int example[9] = { 1,2,3,4,5,6,7,8,9 };
		Assume that we want to locate the position of "3".

		##### Code Start #####
		bool ncomp(const void *baseLeft, const void *baseRight, const void *tempLeft, const void *tempRight, const void *middle)
		{
			if (*(int*)middle >= 3)
				return true;
			else
				return false;
		}
		bool ccomp(const void *baseLeft, const void *baseRight, const void *tempLeft, const void *tempRight)
		{
			if (*(int*)tempLeft == 3)
				return tempLeft;
			else
				return tempRight;
		}
		int main()
		{
			int example[9] = { 1,2,3,4,5,6,7,8,9 };
			int *target = (int*)DichotomyLocate(example, 9, sizeof(int), ncomp, ccomp);
			return 0;
		}
		##### Code End #####

		"target" is the location of "3".
		P.S.
		In this particular situation, not all the pointers in the parameter are used.
		However, they may be necessary in other situations.

*/


void *DichotomyLocate(void *base, int num, int size, \
	bool(*ncomp)(const void *baseLeft, const void *baseRight, \
		const void *tempLeft, const void *tempRight, const void *middle), \
	bool(*ccomp)(const void *baseLeft, const void *baseRight, \
		const void *tempLeft, const void *tempRight))
{
	char *toFirstElement = (char*)base;
	char *toLastElement = (char*)base + size * (num - 1);
	char *leftPointer = toFirstElement, *rightPointer = toLastElement, *middlePointer = 0;
	while ((rightPointer - leftPointer) / size > 1)
	{
		middlePointer = leftPointer + size * (((rightPointer - leftPointer) / size) / 2);
		if ((*ncomp)(toFirstElement, toLastElement, leftPointer, rightPointer, middlePointer))
			rightPointer = middlePointer;
		else
			leftPointer = middlePointer;
	}
	return (*ccomp)(toFirstElement, toLastElement, leftPointer, rightPointer) ? rightPointer : leftPointer;
}