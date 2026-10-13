#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
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
    file.close();
     // Test Danych
    /*
    for (const auto& p : Data) {
        cout << "ID: " << p.id << " | X: " << p.x << " | Y: " << p.y << endl;
    }*/

    //Lista Kontrolna tablica poprawności pomiaru

    bool ConeFlags[n];
    for (int i = 0; i < n; i++) {
        ConeFlags[i] = true;
    }
    //test ConeFlag
    /*
    for (int i = 0; i < n; i++) {
        cout << ConeFlags[i] << endl ;
    }*/


    // Sprawdzanie Odległości
    int m2 =  pow(m,2);
    struct ConesGroup {
        int Id;
        vector<int> GroupIds;
    };
    vector<ConesGroup> OldConesGroup;
    for (int i =0; i < Data.size(); i++) {
        //cout << Data[i].id << " " << Data[i].x << " " << Data[i].y << endl;
        vector<int> OldConesId;
        for (int j =0; j < Data.size(); j++) {
            // czy jest sens sprawdać poprawność do błedu pomiaru
            if (j+1 != Data[i].id and ConeFlags[j] != false) {
                if (pow(Data[j].x - Data[i].x,2)+pow(Data[j].y - Data[i].y,2) < m2) {
                    //cout << Data[i].id << " " << j<< endl;
                    //cout <<pow(Data[j].x - Data[i].x,2)+pow(Data[j].y - Data[i].y,2) <<"m2" <<m2 << endl;
                    //Dopisanie do błedów pomiaru
                    ConeFlags[Data[i].id-1] = false;
                    ConeFlags[Data[j].id-1] = false;
                    OldConesId.push_back(Data[j].id);
                }
            }

        }
        if (OldConesId.size() != 0) {
            OldConesGroup.push_back({Data[i].id,OldConesId});
        }

    }

    //Tworzenie Nowych Pachołków
    for (int i =0; i < OldConesGroup.size(); i++) {
        float x = Data[OldConesGroup[i].Id-1].x;
        float y = Data[OldConesGroup[i].Id-1].y;
        //cout << x << " og " << y << endl;
        for (int j = 0; j < OldConesGroup[i].GroupIds.size(); j++) {
            x += Data[OldConesGroup[i].GroupIds[j]-1].x;
            y += Data[OldConesGroup[i].GroupIds[j]-1].y;
            //cout << Data[OldConesGroup[i].GroupIds[j]].x << " og " << Data[OldConesGroup[i].GroupIds[j]].y << endl;
        }
        x = x / (OldConesGroup[i].GroupIds.size() + 1);
        y = y / (OldConesGroup[i].GroupIds.size() + 1);
        Data.push_back({Data.size()+1,x,y});
    }
    vector<cone> EndData;
    // Wywalanie błędnych pachołków
    for (int i =0; i < Data.size(); i++) {
        if (i < n) {
            if (ConeFlags[i] == true) {
                EndData.push_back({Data[i].id,Data[i].x,Data[i].y});
            }
            else {
                cout << "usunieto pacholek " <<  Data[i].id <<endl;
            }
        }
        else {
            EndData.push_back({Data[i].id,Data[i].x,Data[i].y});
        }
    }

    /*
    cout <<"Testy" << endl;
    // Test Wywalonych id
    for (int i = 0; i < OldConesGroup.size(); i++) {
        cout << OldConesGroup[i].Id << " ";
        cout <<  "Wywalone Id ";
        for (int j = 0; j < OldConesGroup[i].GroupIds.size(); j++) {
            cout << OldConesGroup[i].GroupIds[j] << " ";
        }
        cout << endl;
    }
    //test flag po wywaleniu bledu
    cout << "\nFlagi" <<endl;
    for (int i = 0; i < n; i++) {
        cout << "id "<< i+1<< " " << ConeFlags[i] << endl ;
    }
    //wypisanie wektora z danymi
    /*
    for (string dana : Data) {
        printf("%s\n", dana.c_str());
    }


    n = stoi(Data.at(0));

    printf("%d n"+n);*/
    // zwrócić tablice z sl
    /*
    cout << "Dane Wyjścia"<< endl;
    for (const auto& p : Data) {
        cout << "ID: " << p.id << " | X: " << p.x << " | Y: " << p.y << endl;
    }*/

    //wynik-Test
    cout << " wynik"<< endl;
    for (const auto& p : EndData) {
        cout << "ID: " << p.id << " | X: " << p.x << " | Y: " << p.y << endl;
    }
    return 0;
}
