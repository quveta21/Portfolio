#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void fractie(int k, int m, int n) {
	/*
	Functia afiseaza pe ecran primele n zecimale ale unei fractii
	preconditii: k - numarator intreg, m - numitor intreg, k < m, m != 0, n - numarul de zecimale afisat
	postconditii: se tipareste pe ecran cele n zecimale
	*/
	k *= 10;
	while (k && n) {
		if (k % m == 0) {
			printf("%d", k / m);
		}
		else {
			printf("%d", k / m);
			k = (k - m * (k / m)) * 10;
		}
		n -= 1;
	}
}

int main() {
	int k, m, n;
	printf("k: ");
	scanf("%d", &k);
	do {
		printf("m: ");
		scanf("%d", &m);
		if (m == 0)
			printf("Can't divide by zero!!\n");
	} while (m == 0);
	printf("n: ");
	scanf("%d", &n);
	printf("k/m = 0.");
	fractie(k, m, n);
	return 0;
}