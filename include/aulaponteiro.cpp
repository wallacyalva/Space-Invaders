#include <windows.h>
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
    system("cls");
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int *pont1, v = 5;
    pont1 = &v;
    cout << endl
         << *pont1 << endl;
    cout << endl
         << pont1 << endl;
    return 0;
}