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

string myxor(string s1, string s2){
    string s11=s1.substr(0,1);
    string s21=s2.substr(0,1);
    string s12=s1.substr(1,1);
    string s22=s2.substr(1,1);
    string s13=s1.substr(2,1);
    string s23=s2.substr(2,1);
    string s14=s1.substr(3,1);
    string s24=s2.substr(3,1);
    string s15=s1.substr(4,1);
    string s25=s2.substr(4,1);
    string s16=s1.substr(5,1);
    string s26=s2.substr(5,1);
    string s17=s1.substr(6,1);
    string s27=s2.substr(6,1);
    string s18=s1.substr(7,1);
    string s28=s2.substr(7,1);
    string c1,c2,c3,c4,c5,c6,c7,c8;
    if (!s11.compare(s21))
        c1="0";
    else
        c1="1";
    if (!s12.compare(s22))
        c2="0";
    else
        c2="1";
    if (!s13.compare(s23))
        c3="0";
    else
        c3="1";
    if (!s14.compare(s24))
        c4="0";
    else
        c4="1";
    if (!s15.compare(s25))
        c5="0";
    else
        c5="1";
    if (!s16.compare(s26))
        c6="0";
    else
        c6="1";
    if (!s17.compare(s27))
        c7="0";
    else
        c7="1";
    if (!s18.compare(s28))
        c8="0";
    else
        c8="1";

    string complete=c1+c2+c3+c4+c5+c6+c7+c8;

    return complete;

}

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

    string kryptogramy[n][max_licznik];

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
                    kryptogramy[n1][licznik]=s1;

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
        int max=0, indMax=0;


        for (int j=0; j<max_licznik;j++){
            for (int i=0; i<n; i++)
            if (temp[i][j] > max){
                max=temp[i][j];
                indMax=i;
            }
        temp2[j]=kryptogramy[indMax][j];
        cout<< temp2[j] << " ";
    }

    cout <<endl;

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
       // cout<<myxor(X[i],temp2[i]);
    }

    cout<<endl;
    cout<<binToDec("1101010");


    return 0;
}
