// 求字符串长度 
int GetLength(char *str)
{
	for (char *p = str;; p++)
		if (*p == '\0')
			return p - str;
}

// 生成next数组 
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

// 返回pattern在target中的位置，不匹配则返回-1 
int StringMatch(char *target, char *pattern)
{
	int i = 0, j = 0;
	int targetLen = GetLength(target);
	int patternLen = GetLength(pattern);
	int *next = new int[patternLen];
	GenerateNextArray(pattern, patternLen, next);
	while (i < targetLen && j < patternLen)
	{
		if (j == -1 || target[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	delete[] next;
	if (j >= patternLen)
		return i - patternLen;
	else
		return -1;
}
