#include <stdio.h>

void prefix(char p[], char s1[], int l1, char s2[], int l2);

int main()
{
	char str1[] = "abcjane";
	char str2[] = "abcdef";
	char str3[] = "ablaosk";
	int len1 = 7;
	int len2 = 6;
	int len3 = 7;
	char p1[] = "";
	char p2[] = "";
	char p3[] = "";
	
	prefix(p1, str1, len1, str2, len2);
	printf("Prefixul comun pentru %s si %s este %s\n", str1, str2, p1);

	prefix(p2, str2, len2, str3, len3);
	printf("Prefixul comun pentru %s si %s este %s\n", str2, str3, p2);

	prefix(p3, str1, len1, str3, len3);
	printf("Prefixul comun pentru %s si %s este %s\n", str1, str3, p3);

	return 0;
}