//POP 2019-12-16 projekt 1 Traskowski Bartłomiej EIT 4 180237 ///program: Code::Blocks release 17.12 rev 11256 (2017-12-28 10:44:41) gcc 5.1.0 Windows/unicode - 32 bit ////kompilator: GNU GCC Compiler
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

float zaokraglij(float x)                       //zaokraglanie do 3 miejsc po przecinku
{
  int y = x * 10000;
  if (y % 10 >= 5) y += 10;
  return (y / 10) * 0.001;
}

string wyczysc(string a)                        //usuwa niepotrzebne znaki
{
    for(int i=0; i<a.size(); i++)
    {
        if((a[i]==',')||(a[i]==':'))
        a[i]='\0';
    }
    return a;
}

string usun(string a)                           //usuwa pierwsze słowo ze stringa
{
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]==' ')
            {
            a.erase(0, i+1);
            break;
            }
    }
    return a;
}

string pobierz(string a)                        //pobiera pierwsze slowo
{
    string slowo;
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]==' ')
            {
            slowo.insert(0, a, 0, i-1);
            break;
            }
    }
    return slowo;
}

struct dawka
{
    string A;                                   //rodzaj alkoholu
    int ilosc;                                  //ilso alkoholu w ml
    int godzina;                                //godzina bez ":"
};


int main()
{
    string dane, plec;
    int waga;                                   //waga w kilogramach

    getline(cin, dane);

    dane = wyczysc(dane);                       //usuwa pierwsze slowo

    plec = pobierz(dane);                       //pobiera plec
    dane = usun(dane);

    dane = usun(dane);                          //usuwa slowo waga

    waga = atoi(pobierz(dane).c_str());         //pobiera wage
    dane = usun(dane);

    int n;                                      //ilosc dawek
    n = floor(dane.length() / 16.);
    int x;                                      //pomocnicza zmienna
    dawka * tab;
    tab = new dawka[n];
    string dane1;                               //pomocnicza zmienna
    int i=0;                                    //iterator

    while(dane.size()>14)                       //pobiera dawki alkoholu i wpisuje je do tablicy struktur
    {
        x = dane.find("piwo");
        if(x!=string::npos)
        {
            tab[i].A="piwo";
            dane1.insert( 0, dane, x+5, 3);
            tab[i].ilosc = atoi(dane1.c_str());
            dane1.clear();
            dane1.insert( 0, dane, x+11, 4);
            tab[i].godzina = atoi(dane1.c_str());
            dane1.clear();
            dane.erase(x, 16);
            i = i+1;
        }

        x = dane.find("wino");
        if(x!=string::npos)
        {
            tab[i].A = "wino";
            dane1.insert( 0, dane, x+5, 3);
            tab[i].ilosc = atoi(dane1.c_str());
            dane1.clear();
            dane1.insert( 0, dane, x+11, 4);
            tab[i].godzina = atoi(dane1.c_str());
            dane1.clear();
            dane.erase(x, 16);
            i = i+1;
        }

        x = dane.find("wodka");
        if(x!=string::npos)
        {
            tab[i].A = "wodka";
            dane1.insert( 0, dane, x+6, 3);
            tab[i].ilosc = atoi(dane1.c_str());
            dane1.clear();
            dane1.insert( 0, dane, x+12, 4);
            tab[i].godzina = atoi(dane1.c_str());
            dane1.clear();
            dane.erase(x, 16);
            i = i+1;
        }
    }

    float s[50];                                //tablica wartosci
    int g[80];                                  //tablica godzin
    int z;                                      //zawartosc % alkoholu
    float k;                                    //wspolczynnik zalezny od plci

    if(plec == "Mezczyzna") k = 0.7;            //sprawdza plec
    else if(plec == "Kobieta") k = 0.6;
    else
    {
    cout<<"Zle dane";
    return 0;
    }

    g[0] = tab[0].godzina;                      //przypisuje odpowiednie godziny
    for (int i=1; i<80; i++)
    {
        g[i] = g[i-1] + 15;
        if(g[i] == 2360) g[i] = 2400;
        if(g[i] == 2460) g[i] = 100;
        if(g[i] == 160) g[i] = 200;
        if(g[i] == 260) g[i] = 300;
        if(g[i] == 360) g[i] = 400;
        if(g[i] == 460) g[i] = 500;
        if(g[i] == 560) g[i] = 600;
        if(g[i] == 660) g[i] = 700;
        if(g[i] == 760) g[i] = 800;
        if(g[i] == 860) g[i] = 900;
        if(g[i] == 960) g[i] = 1000;
        if(g[i] == 1060) g[i] = 1100;
        if(g[i] == 1160) g[i] = 1200;
        if(g[i] == 1260) g[i] = 1300;
        if(g[i] == 1360) g[i] = 1400;
        if(g[i] == 1460) g[i] = 1500;
        if(g[i] == 1560) g[i] = 1600;
        if(g[i] == 1660) g[i] = 1700;
        if(g[i] == 1760) g[i] = 1800;
        if(g[i] == 1860) g[i] = 1900;
        if(g[i] == 1960) g[i] = 2000;
        if(g[i] == 2060) g[i] = 2100;
        if(g[i] == 2160) g[i] = 2200;
        if(g[i] == 2260) g[i] = 2300;
    };

    for(int i=0; i<50; i++)                     //zeruje wartosci w tablicy
    {
        s[i] = 0;
    }

    if(tab[0].A == "piwo") z = 5;               //wyznaczanie zawartosci % alkoholu
    if(tab[0].A == "wino") z = 10;
    if(tab[0].A == "wodka") z = 40;

    s[0] = ((tab[0].ilosc * z / 100) * 0.79);   //przypisuje pierwsza wartosc, narazie alkohol w gramach

    for(int i=1; i<n; i++)                      //przypisuje kolejne wartosci, w odpowiednich miejscach tablicy
    {
        x = tab[i].godzina;
        int y = tab[i].ilosc;
        if(tab[i].A == "piwo") z = 5;
        if(tab[i].A == "wino") z = 10;
        if(tab[i].A == "wodka") z = 40;
        for(int i=1; i<50; i++)
        {
            if(x == g[i]) s[i] = s[i] + ((y * z / 100) * 0.79);
        }
    }

    for(int i=1; i<50; i++)                     //pilnuje zeby wartosci w tablicy nie byly mniejsze od 0
    {
        if(plec == "Mezczyzna") s[i] = s[i] + s[i-1] - 2.5;
        if(plec == "Kobieta") s[i] = s[i] + s[i-1] - 2;
        if(s[i] <= 0) s[i] = 0;
    }

    for(int i=0; i<50; i++)                     //zmienia ilosc alkoholu w gramach na promile we krwi + zaokragla wartosci
    {
        s[i] = s[i] / (waga * k);
        s[i] = zaokraglij(s[i]);
    }

    float suma=0;
    for(int i=0; i<n; i++)                      //sumuje ilosc spozytego alkoholu
    {
        if(tab[i].A == "piwo") z = 5;
        if(tab[i].A == "wino") z = 10;
        if(tab[i].A == "wodka") z = 40;
        suma += ((tab[i].ilosc * z / 100) * 0.79);
    }

    int godzina_zero;                           //godzina o ktorej schodzi caly alkohol
    for(int i=49; i>=0; i--)                    //wyznacza ta godzine i jej miejsce w tablicy
    {
        if(s[i]<=0)
        {
            godzina_zero = g[i];
            x = i;
        }

    }

    cout<<"Spozyles "<<suma<<" gram czystego alkoholu."<<endl;
    cout<<"O godzinie "<<godzina_zero<<" pozbedziesz sie calego alkoholu."<<endl;


    float t[50];                                //pomocnicza tablica do rysowania wykresu
    for(int i=0; i<50; i++)
        t[i] = s[i];

    for (int i=0; i<50; i++)                    //segreguje tablice
        for (int j=0; j<50; j++)
            if (t[j]<t[j+1])
                swap(t[j], t[j+1]);

    cout<<endl<<"promile"<<endl;                //rysowanie wykresu
    cout<<"     +";                             //pierwszy wiersz

    for(int i=0; i<88; i++)
    {
        cout<<"-";
    }

    cout<<"+"<<endl;

    for(int i=0; i<40; i++)                     //kolejne wiersze
    {
        float y = t[i];
        if(t[i]==0) break;
        cout.precision(3);
        cout<<fixed<<t[i]<<"|";
        for(int i=0; i<88; i++)
        {
            if(y==s[i])cout<<".";
            else cout<<" ";
        }
        cout<<"|"<<endl;
    }

    cout<<"     +";                             //przedostatni wiersz
    for(int i=0; i<88; i++)
    {
        cout<<"-";
    }
    cout<<"+"<<endl;

    cout<<"    "<<tab[0].godzina;               //ostatni wiersz
    for(int i=0; i<80; i++){
        if(x==i) cout<<godzina_zero;
        cout<<"-";
    }
    cout<<"godzina";

    delete [] tab;
    return 0;
}
