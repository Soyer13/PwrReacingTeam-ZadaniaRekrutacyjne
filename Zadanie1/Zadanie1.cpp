#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

struct cone {
    int id;
    float x;
    float y;
};
//zad1.1
vector<cone> ConeErrorDetection(string FilePath) {
    //("../Dane/zad1/example_input.txt");
    ifstream file(FilePath);
    string line;

    vector<cone> Data;
    //kontrola błedu otwierania pliku
    if (!file.is_open()) {
        printf( ("Nie mozna otworzyc pliku! " +FilePath).c_str());
        return Data;
    }

    int n = 0; //liczba punktów w zbiorze
    float m = 0; // minimalna dopuszczana odległość między dwoma pachołkami
    //<id> <x> <y> - w kolejnych n liniach znajdować się będzie unikalne ID pachołka, oraz współrzędne x i y oddzielone spacją

    //wycągniecie n i m
    if (getline(file, line)) {
        n = atoi(line.c_str());
        getline(file, line);
        m = stof(line.c_str());
    }


    //Wyciągniecie danych
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        stringstream s(line);

        int id;
        float x, y;

        s >> id >> x >> y;
        Data.push_back({id, x, y});
    }
    file.close();

    bool ConeFlags[n];
    for (int i = 0; i < n; i++) {
        ConeFlags[i] = true;
    }


    // Sprawdzanie Odległości
    int m2 =  pow(m,2);
    struct ConesGroup {
        int Id;
        vector<int> GroupIds;
    };
    vector<ConesGroup> OldConesGroup;
    for (int i =0; i < Data.size(); i++) {
        vector<int> OldConesId;
        for (int j =0; j < Data.size(); j++) {
            // czy jest sens sprawdać poprawność do błedu pomiaru
            if (j+1 != Data[i].id and ConeFlags[j] != false) {
                if (pow(Data[j].x - Data[i].x,2)+pow(Data[j].y - Data[i].y,2) < m2) {
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
        for (int j = 0; j < OldConesGroup[i].GroupIds.size(); j++) {
            x += Data[OldConesGroup[i].GroupIds[j]-1].x;
            y += Data[OldConesGroup[i].GroupIds[j]-1].y;
        }
        x = x / (OldConesGroup[i].GroupIds.size() + 1);
        y = y / (OldConesGroup[i].GroupIds.size() + 1);
        int newId = Data.size()+1;
        Data.push_back({newId,x,y});
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

    return EndData;
}


/*Zadanie 1.2
int CrovexHull(vector<cone> Data) {
    //vector<cone> SortedData = Data.sort;
    //sortowanie danych
    /*
    sort(Data.begin(), Data.end(), [](const cone& a, const cone& b) {return a.x < b.x;});
    if (Data[0].x == Data[1].x) {
        sort(Data.begin(), Data.end(), [](const cone& a, const cone& b) {
            if (abs(a.x - b.x) > 1e-9) {
                return a.x < b.x;
            }
            return a.y < b.y;
        });
    }*/
    /*


    vector<cone> CorvexHullData;
    vector<cone> lower;
    lower.push_back(Data[0]);
    for (int i = 0; i < Data.size(); i++) {
        if ( cross_product()> 0**)
    }*//*
    sort(Data.begin(), Data.end(), [](const cone& a, const cone& b) {return a.x < b.x;});
    cout << "CrovexHull" << endl;
    for (const cone& c : Data) {
        cout << c.id << " " << c.x << " " << c.y << endl;
    }
    vector<cone> lower;
    float AB,AC,tgx=1;
    int nextId=0;
    lower.push_back(Data[nextId]);
    for (int i = 1; i < Data.size(); i++) {
        for (int j = 1; j < Data.size(); j++) {
            if (Data[j].x > lower[i-1].x && Data[j].y < lower[i-1].y) {

                AB = sqrt(pow((Data[j].y, - lower[i-1].y),2));
                AC = sqrt(pow((Data[j].x, - lower[i-1].x),2));
                if (tgx >AC/AB) {
                    cout<< "n"<<endl;
                    tgx = AC/AB;
                    nextId = i;
                }
            }

        }
        lower.push_back(Data[nextId]);
    }

    cout << "lower" << endl;
    for (const cone& c : lower) {
        cout << c.id << " " << c.x << " " << c.y << endl;
    }
    //cout << "aAA"<< cross_product(Data[0],Data[1],Data[2])<<endl;
    return 0;
    //znaleś punkt najbardziej w lewo
    //sprawdza kąt z prawej strony z dołu dopuki są x > obecnego x
    //sprawda kąty z lewej z góry i szuka najmniejszego dopuki x< obecnego
}*/
int main()
{
    vector<cone> data = ConeErrorDetection("../Dane/zad1/example_input.txt");
    //CrovexHull(data);

    for (int i =0; i < data.size(); i++) {
        cout <<"id: "<< data[i].id << " | x=  " << data[i].x << " | y= " << data[i].y << endl;
    }


    return 0;
}
