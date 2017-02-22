# Algorithm

###This is a depository used to store the self-written functions.<br><br>
###KMP.h<br>
Works like "strstr" in \<cstring> but using KMP algorithm.<br>
```c++
char *strstr_KMP(char *target, char *pattern);
```
<br>
###DichotomyLocate.h<br>
This function is used to locate a particular position by using dichotomy.
```c++
void *DichotomyLocate(void *base, int num, int size, \
　bool(*ncomp)(const void *baseLeft, const void *baseRight, \
　　const void *tempLeft, const void *tempRight, const void *middle), \
　bool(*ccomp)(const void *baseLeft, const void *baseRight, \
　　const void *tempLeft, const void *tempRight));
```
