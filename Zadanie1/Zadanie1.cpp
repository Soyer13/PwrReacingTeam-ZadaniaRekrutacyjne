#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
    vector<cone> Data;
    //kontrola błedu otwierania pliku
    if (!file.is_open()) {
        printf( ("Nie mozna otworzyc pliku! " +path).c_str());
        return 1;
    }

    int n = 0; //liczba punktów w zbiorze
    float m = 0; // minimalna dopuszczana odległość między dwoma pachołkami
    //<id> <x> <y> - w kolejnych n liniach znajdować się będzie unikalne ID pachołka, oraz współrzędne x i y oddzielone spacją

    //wycągniecie n i m
    if (getline(file, line)) {
       //printf(line.c_str());
        n = atoi(line.c_str());
        //cout << n << endl;
        getline(file, line);
        m = stof(line.c_str());
        //cout << n << " " << m << endl;
    }


    //Wyciągniecie danych
    while (getline(file, line)) {
        //printf("%s\n", line.c_str());
        //Data.push_back(line);
        //string l;
        //l = line.substr(0, line.length() - 1);
        if (line.empty()) {
            continue;
        }
        stringstream s(line);

        int id;
        float x, y;

        s >> id >> x >> y;
        //cout << id << " " << x << " " << y << " n" << endl;
        Data.push_back({id, x, y});
    }
    /*  Test Wektora
    for (const auto& p : Data) {
        cout << "ID: " << p.id << " | X: " << p.x << " | Y: " << p.y << endl;
    }*/

    file.close();
    //wypisanie wektora z danymi
    /*
    for (string dana : Data) {
        printf("%s\n", dana.c_str());
    }


    n = stoi(Data.at(0));

    printf("%d n"+n);*/
    // zwrócić tablice z sl
    return 0;
}
