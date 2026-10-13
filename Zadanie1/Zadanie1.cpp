#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    string szcierzka("../Dane/zad1/example_input.txt");
    ifstream plik(szcierzka);
    string linia;

    if (!plik.is_open()) {
       printf( ("Nie mozna otworzyc pliku! " +szcierzka).c_str());
        return 1;
    }
    int n = 0; //liczba punktów w zbiorze
    int m = 0; // minimalna dopuszczana odległość między dwoma pachołkami
    //n = plik.getline();

    while (getline(plik, linia)) {
        printf("%s\n", linia.c_str());
    }

    plik.close();
    return 0;
}
