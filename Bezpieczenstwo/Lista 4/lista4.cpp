#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 * @author Mikołaj Dukiel
 * */

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

string decToBin(int decimal)
{
    string binary="";
    if (decimal>127)
        return "blad";
    int x=128;
    while (x!=0){
        if (decimal>=x){
            decimal-=x;
            binary=binary+'1';}
            else
                binary=binary+'0';
            x=x/2;
        }
    return binary;
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

int szukanieSpacji(int x){

    switch (x)
    {
        case 0:
            return 20;
        case 38:
            return 19;
        case 72:
            return 18;
        case 102:
            return 17;
        case 128:
            return 16;
        case 150:
            return 15;
        case 168:
            return 14;
        case 182:
            return 13;
        case 192:
            return 12;
        case 198:
            return 11;
        case 200:
            return 10;
        default:
            return 1;
    }
}

int main(){

    // n - liczba kryptogramów
    int n=20, max_licznik = najwiekszyLicznik(n);

    // Tworzenie tablicy z kryptogramami i wiadomosciami

    string kryptogramy[n][max_licznik];
    string klucz[max_licznik];
    char wiadomosci[n][max_licznik];

    //"Zerowanie" tablic
    for (int i=0; i<n; i++)
        for (int j=0; j<max_licznik;j++){
            kryptogramy[i][j]="";
            wiadomosci[i][j]=' ';
            klucz[j]="";
        }

        //Wczytanie kryptogramów
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

    // kryptospacje[nr_kryptogramu][nr_bajtu]
    int kryptospacje[n+1][max_licznik];
    for (int i=0; i<=n; i++)
        for (int j=0; j<max_licznik; j++)
                kryptospacje[i][j]=0;

    // xorowanie każdego kryptogramu z każdym (odpowiadające sobie bajty)
    for (int k1=0; k1<n; k1++)
        for (int k2=k1+1; k2<n; k2++)
            for(int b=0; b<max_licznik; b++){
                if (!kryptogramy[k1][b].compare("")||!kryptogramy[k2][b].compare(""))
                    break;
                string sxor=myxor(kryptogramy[k1][b], kryptogramy[k2][b]).substr(0,2);
                if (!sxor.compare("01")){
                    kryptospacje[k1][b]++;
                    kryptospacje[k2][b]++;
                }
        }

    for(int j=0; j<max_licznik; j++){
            int suma=0;
            for(int i=0; i<n; i++)
                suma+=kryptospacje[i][j];
            kryptospacje[20][j]=suma;
        }

     // xorowanie tych bajtów, gdzie było ich dużo (np dla sumy 38, tego z 19)
     for (int b=0; b<max_licznik; b++){
         for (int k=0; k<n; k++){
             if(szukanieSpacji(kryptospacje[20][b])<=kryptospacje[k][b]){
                 klucz[b] = myxor(kryptogramy[k][b], "00100000");
             }
         }
     }

    // Odkodowanie wiadomości
    for (int k=0; k<n; k++){
        cout << "\n\nOdkodowany kryptogram: " <<k+1<<": "<<endl;
        for (int b=0; b<max_licznik; b++){
            wiadomosci[k][b]=char(binToDec(myxor(kryptogramy[k][b], klucz[b])));
            cout << wiadomosci[k][b];
            }

        }
    // Reczne poprawki
    klucz[0]=myxor(kryptogramy[0][0], decToBin(int('D')));
    klucz[7]=myxor(kryptogramy[0][7], decToBin(int('b')));
    klucz[15]=myxor(kryptogramy[0][15], decToBin(int('t')));
    klucz[25]=myxor(kryptogramy[0][25], decToBin(int('s')));
    klucz[28]=myxor(kryptogramy[0][28], decToBin(int('n')));
    klucz[31]=myxor(kryptogramy[0][31], decToBin(int('J')));
    klucz[52]=myxor(kryptogramy[0][52], decToBin(int('o')));
    klucz[56]=myxor(kryptogramy[0][56], decToBin(int('d')));
    klucz[57]=myxor(kryptogramy[0][57], decToBin(int('z')));
    klucz[60]=myxor(kryptogramy[0][60], decToBin(int('l')));
    klucz[64]=myxor(kryptogramy[0][64], decToBin(int('e')));

    klucz[66]=myxor(kryptogramy[1][66], decToBin(int('o')));

    klucz[67]=myxor(kryptogramy[0][67], decToBin(int('a')));
    klucz[99]=myxor(kryptogramy[0][99], decToBin(int('k')));

    klucz[101]=myxor(kryptogramy[7][101], decToBin(int('o')));

    klucz[106]=myxor(kryptogramy[8][106], decToBin(int('k')));

   klucz[119]=myxor(kryptogramy[18][119], decToBin(int('a')));
   klucz[124]=myxor(kryptogramy[18][124], decToBin(int('z')));

   klucz[130]=myxor(kryptogramy[0][124], decToBin(int('t')));
   klucz[131]=myxor(kryptogramy[0][124], decToBin(int('y')));
   klucz[132]=myxor(kryptogramy[0][124], decToBin(int('n')));



    // Odkodowanie wiadomości po poprawce klucza
    for (int k=0; k<n; k++){
        cout << "\n\nPoprawiony odkodowany kryptogram: " <<k+1<<": "<<endl;
        for (int b=0; b<max_licznik; b++){
            wiadomosci[k][b]=char(binToDec(myxor(kryptogramy[k][b], klucz[b])));
            cout << wiadomosci[k][b];
        }

    }

    // Kryptogram do odszyfrowania
    string X[max_licznik];
    fstream plik;
    plik.open("kryptogramX.txt", ios::in);

    if (plik.good() == false) {
        cout << "Plik nie istnieje!";
        exit(0);
    }

    int licznik=0;

    cout << "\n\nOdkodowany kryptogram z zadania 1:"<<endl;

    while (plik.good()) {
        plik >> X[licznik];
        cout<<char(binToDec(myxor(X[licznik], klucz[licznik])));
        licznik++;
    }

    plik.close();



    return 0;
}
