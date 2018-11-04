#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int strToInt(string s)
{
    bool m=false;
    int tmp=0;
    int i=0;
    if(s[0]=='-')
    {
        i++;
        m = true;
    }
    while(i<s.size())
    {
        tmp = 10*tmp+s[i]-48;
        i++;
    }
    return m ? -tmp : tmp;
}

int binToDec(string binary)
{
    int bin = strToInt(binary);

    int decimal=0;
    int pow=1;
    while(bin!=0){

        if (bin%10==1)
            decimal+=pow;

        bin/=10;
        pow*=2;
    }
    return decimal;
}

string myxor(string s1, string s2) {
    string newx = "";
    for (int i = 0; i < 8; i++) {
        if (s1[i] == s2[i] )
            newx += "0";
        else newx += "1"; }
        return newx; }

int najwiekszyLicznik(int n){
    int max_licznik=0;
    for(int i=0; i<=n-1; i++) {
        fstream plik;
        string nazwa = "kryptogram"+to_string(i+1)+".txt";
        plik.open(nazwa, ios::in);

        if (plik.good() == false) {
            cout << "Plik nie istnieje!";
            exit(0);
        }

        string s;
        int licznik=0;

        while (plik.good()) {
            plik >> s;
            licznik++;
        }

        if (licznik>max_licznik)
            max_licznik=licznik;

        plik.close();
    }

    return max_licznik;
}

int main(){

    // n - liczba kryptogramów
    int n=20, max_licznik = najwiekszyLicznik(n);

    // Stworzenie tabeli pom. i wypełnienie jej zerami
    int temp[n][max_licznik];
    for (int i=0; i<n; i++)
        for (int j=0; j<max_licznik;j++)
            temp[i][j]=0;

    // Tworzenie tablicy z kryptogramami

    string kryptogramy[n][max_licznik];

    for (int i=0; i<n; i++)
        for (int j=0; j<max_licznik;j++)
            kryptogramy[i][j]="";


    for(int i=0; i<=n-1; i++) {
        fstream plik;
        string nazwa = "kryptogram"+to_string(i+1)+".txt";
        plik.open(nazwa, ios::in);

        if (plik.good() == false) {
            cout << "Plik nie istnieje!";
            exit(0);
        }

        string s;
        int licznik=0;

        while (plik.good()) {
            plik >> s;
            kryptogramy[i][licznik]=s;
            licznik++;
        }

        plik.close();
    }

    // xorowanie dwóch pierwszych bitów każdego odpowiadającego bajtu każdych kryptogramów
    for(int n1=0; n1<n; n1++)
        for(int n2=n-1; n2>n1; n2--){

            fstream plik1, plik2;
            string nazwa1 = "kryptogram"+to_string(n1+1)+".txt";
            string nazwa2 = "kryptogram"+to_string(n2+1)+".txt";
            plik1.open(nazwa1, ios::in);
            plik2.open(nazwa2, ios::in);

            if (plik1.good() == false) {
                cout << "Plik nie istnieje!";
                exit(0);
            }

            if (plik2.good() == false) {
                cout << "Plik nie istnieje!";
                exit(0);
            }

            string s1, s2, s11, s12, s21, s22;
            int licznik=0;


            while (plik1.good() && plik2.good()) {
                plik1 >> s1;
                plik2 >> s2;

                // Podział na pierwszy znak i drugi znak;
                s11=s1.substr(0,1);
                s21=s2.substr(0,1);
                s12=s1.substr(1,1);
                s22=s2.substr(1,1);

                if(!s11.compare(s21) && s12.compare(s22)){
                    temp[n1][licznik]++;
                    temp[n2][licznik]++;
                }

                licznik++;
            }

            plik1.close();
            plik2.close();
        }


    //Potencjalny klucz
    string temp2[max_licznik];

        for (int i=0; i<max_licznik; i++)
            temp2[i]="";

    int max=0, indMax=0;


    for (int j=0; j<max_licznik;j++){
        for (int i=0; i<n; i++)
            if (temp[i][j] > max){
                max=temp[i][j];
                indMax=i;
            }
       temp2[j]=kryptogramy[indMax][j];
    }

    // Xorowanie potencjalnego klucza ze znakiem spacji
    for (int j=0; j<max_licznik; j++)
    temp2[j]=myxor(temp2[j],"00100000");

    // Kryptogram do odszyfrowania
    string X[max_licznik];
    fstream plik;
    plik.open("kryptogramX.txt", ios::in);

    if (plik.good() == false) {
        cout << "Plik nie istnieje!";
        exit(0);
    }

    int licznik=0;

    while (plik.good()) {
        plik >> X[licznik];
        licznik++;
    }


    plik.close();

    //Xorowanie klucza i kryptogramu do odszyfrowania
    for (int i=0; i<max_licznik; i++){
        cout<<char(binToDec(myxor(X[i],temp2[i])));
    }


    return 0;
}
