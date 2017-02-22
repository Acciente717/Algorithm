/*
#########################
###       KMP.h       ###
###      By Acc.      ###
###      Ver 1.1      ###
###    2017-01-27     ###
#########################

It works just like the "strstr" function in <cstring>.

*/

// Get the length of the string.
int GetLength(char *str)
{
	for (char *p = str;; p++)
		if (*p == '\0')
			return p - str;
}

// Generate the "next" array to speed up the matching process.
void GenerateNextArray(char *str, int length, int* next)
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

// Return the pointer pointing to the matched piece, otherwise return 0 (NULL).
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