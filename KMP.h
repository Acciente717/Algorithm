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
int strstr_KMP(char *target, char *pattern)
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
		return p - target - patternLen;
	else
		return -1;
}
