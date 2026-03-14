#include <stdio.h>

int gcd(int a, int b) {
	/*
	Afla cel mai mare divizor comun a doua numere intregi
	preconditii: a si b sunt doua numere intregi
	postconditii: se returneaza cmmdc
	*/
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int prim(int n) {
	/*
	Verifica primalitatea unui numar intreg
	preconditii: n - numar intreg
	postconditii: 1 - n prim, 0 - altfel
	*/
	if (n < 2) return 0;
	for (int d = 2; d * d <= n; d++)
		if (n % d == 0) return 0;
	return 1;
}

int verifica(int n) {
	/*
	Verifica daca un numar are proprietatea ceruta (mai exact toate numerele mai mici decat numarul dat care sunt prime cu acesta
	sunt la randul lor prime)
	preconditii: n - numar intreg
	postconditii: 1 - proprietatea este verificata, 0 - altfel
	*/
	for (int i = 2; i < n; i++) 
		if (gcd(n, i) == 1 && prim(i) == 0)
			return 0;
	return 1;
}

int main(){
	int n = 3, count = 0;
	while (count < 8) {
		if (verifica(n)) {
			printf("%d ", n);
			count++;
		}
		if (n == 3)
			n++;
		else
			n += 2;
	}
	return 0;
}