#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    string path("../Dane/zad1/example_input.txt");
    ifstream file(path);
    string line;
    struct cone {
        int id;
        float x;
        float y;
    };
    vector<string> Dane;

    if (!file.is_open()) {
        printf( ("Nie mozna otworzyc pliku! " +path).c_str());
        return 1;
    }

    int n = 0; //liczba punktów w zbiorze
    float m = 0; // minimalna dopuszczana odległość między dwoma pachołkami
    //<id> <x> <y> - w kolejnych n liniach znajdować się będzie unikalne ID pachołka, oraz współrzędne x i y oddzielone spacją

    if (getline(file, line)) {
       //printf(line.c_str());
        n = atoi(line.c_str());
        //cout << n << endl;
        getline(file, line);
        m = stof(line.c_str());
        cout << n << " " << m << endl;
    }



    while (getline(file, line)) {
        //printf("%s\n", line.c_str());
        Dane.push_back(line);
    }

    file.close();
    //wypisanie wektora z danymi
    for (string dana : Dane) {
        printf("%s\n", dana.c_str());
    }


    n = stoi(Dane.at(0));

    printf("%d n"+n);
    // zwrócić tablice z sl
    return 0;
}
