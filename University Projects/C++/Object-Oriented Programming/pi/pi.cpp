#include <iostream>
#include <iomanip>

using namespace std;

double pi_aprox(int start, int stop)
{
    if (start == stop)
        return 1;
    return 6 + (2 * start + 1) * (2 * start + 1) / pi_aprox(start + 1, stop);
}

int main()
{
    int start=1, stop;
    cout << "Introduceti numarul de iteratii: ";
    cin >> stop;
    double pi = 3 + 1 / pi_aprox(1, stop);
    cout << setprecision(50)<<pi;
}
