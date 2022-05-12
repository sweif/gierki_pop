//Bartlomiej Traskowski EIT 4 180237, użyty program: Visual C++ 2019
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

string wyczysc(string a)                        //usuwa niepotrzebne znaki
{
    for (unsigned short i = 0; i < a.size(); i++)
    {
        if ((a[i] == ',') || (a[i] == ':'))
            a[i] = ' ';
    }
    return a;
}
string pobierz(string a)                        //pobiera pierwsze slowo
{
    string slowo;
    for (unsigned short i = 0; i < a.size(); i++)
    {
        if (a[i] == ' ')
        {
            slowo.insert(0, a, 0, i);
            break;
        }
    }
    return slowo;
}
string usun(string a)                           //usuwa pierwsze słowo ze stringa
{
    for (unsigned short i = 0; i < a.size(); i++)
    {
        if (a[i] == ' ')
        {
            a.erase(0, i + 1);
            break;
        }
    }
    return a;
}

void opis()
{
    cout << "BAZA PLYT AUDIO" << endl;
    cout << "=======================================================================================================================================================" << endl;
    cout << "Funkcje:" << endl;
    cout << "1.dodaj " << "- dodaje nowy wpis do bazy. " << "Przyklad:'dodaj:tytul: '" << endl;
    cout << "2.szukaj " << "- szuka we wpisach zadanego slowa i wypisuje wszystkie znalezione. " << "Przyklad:'szukaj:autor:makarena'" << endl;
    cout << "3.edytuj " << "- szuka po zadanym slowie, " << "prosi o podanie numeru znalezionego wpisu do edytowania, " << "nastepnie prosi o wpisanie nowego wpisu." << endl;
    cout << "4.usun " << "- szuka po zadanym slowie, " << "prosi o podanie numeru znalezionego wpisu do usuniecia" << endl;
    cout << "=======================================================================================================================================================" << endl;
    cout << "Podfunkcje:" << endl;
    cout << "tytul " << "- dzialania na pliku opisujacym utwory " << endl;
    cout << "autor " << "- dzialania na pliku opisujacym autorow " << endl;
    cout << "=======================================================================================================================================================" << endl;
}
void formatT()                                  //wypisuje pierwsza linie pliku
{
    string linia;
    fstream plik;
    plik.open("tytul.txt", ios::in);
    if (plik.good() == false)                   //plik.good() zwraca false jesli plik nie istnieje
    {
    cout << "Nie znaleziono pliku!";
    exit(0);
    }
    getline(plik, linia);
    cout << "FORMAT:" << linia << endl;
    plik.close();
}
void formatA()
{
    string linia;
    fstream plik;
    plik.open("autor.txt", ios::in);
    if (plik.good() == false)
    {
    cout << "Nie znaleziono pliku!";
    exit(0);
    }
    getline(plik, linia);
    cout << "FORMAT:" << linia << endl;
    plik.close();
}

void dodaj_Wtytule()                            //podfunkcja dodawania
{
    fstream plik;
    string wpis;
    formatT();
    cout << "Podaj nowy/zedytowany wpis, wedlug formatu:" << endl;
    getline(cin, wpis);
    plik.open("tytul.txt", ios::out | ios::app);
    plik << wpis << endl;
    plik.close();
}
void dodaj_Wautorze()                           //podfunkcja dodawania
{
    fstream plik;
    string wpis;
    formatA();
    cout << "Podaj nowy/zedytowany wpis, wedlug formatu:" << endl;
    getline(cin, wpis);
    plik.open("autor.txt", ios::out | ios::app);
    plik << wpis << endl;
    plik.close();
}
void szukaj_Wtytule(string a)                   //wyszukuje slowo klucz w pliku i wypisuje wszystkie linie posiadajace te slowo
{
    fstream plik;
    plik.open("tytul.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    string linia;
    int nr_linii = 1;
    cout << "Znalezione wpisy:" << endl;
    while (getline(plik, linia))
    {
        if (nr_linii == 1) cout <<"FORMAT:"<< linia << endl;
        int x;
        x = linia.find(a);
        if (x != string::npos)
        {
            cout << nr_linii << linia << endl;
        }
        nr_linii++;
    }
    plik.close();
}
void szukaj_Wautorach(string a)
{
    fstream plik;
    plik.open("autor.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    string linia;
    int nr_linii = 1;
    cout << "Znalezione wpisy:" << endl;
    while (getline(plik, linia))
    {
        if (nr_linii == 1) cout <<"FORMAT:"<< linia << endl;
        int x;
        x = linia.find(a);
        if (x != string::npos)
        {
            cout << nr_linii << linia << endl;
        }
        nr_linii++;
    }
    plik.close();
}
void kasuj_wierszTytul(unsigned short wiersz)    //kasuje wiersz o numerze podanym do funkcji - przepisuje kazdy wiersz z orginalnego pliku do nowego pomijajac wiersz o zadanym numerze po czym usuwa orginalny plik a nowemu zmienia nazwe
{
    string linia;
    fstream plik;
    plik.open("tytul.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    int nr_linii = 1;
    while (getline(plik, linia))
    {
        if (wiersz != nr_linii)
        {
            fstream plik2;
            plik2.open("test2.txt", ios::in | ios::app);
            plik2 << linia << endl;
            plik2.close();
        }
        nr_linii++;
    }
    plik.close();
    remove("tytul.txt");                        //usuwa plik, zwraca 0 jesli pomyslnie usunie plik
    if (rename("test2.txt", "tytul.txt") != 0)  //zmienia nazwe pliku na nowa, zwraca 0 jesli operacja sie uda
    {
        cout << "Nie udalo sie znalezc pliku";
        exit(0);
    }
}
void kasuj_wierszAutor(unsigned short wiersz)
{
    string linia;
    fstream plik;
    plik.open("autor.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    int nr_linii = 1;
    while (getline(plik, linia))
    {
        if (wiersz != nr_linii)
        {
            fstream plik2;
            plik2.open("test2.txt", ios::in | ios::app);
            plik2 << linia << endl;
            plik2.close();
        }
        nr_linii++;
    }
    plik.close();
    remove("autor.txt");
    if (rename("test2.txt", "autor.txt") != 0)
    {
        cout << "Nie udalo sie znalezc pliku";
        exit(0);
    }
}

void dodawanie(string a)                        //dodawanie wpisu do bazy danych
{
    a = usun(a);
    string drugie = pobierz(a);
    if (drugie == "tytul") 
    {
        dodaj_Wtytule();
    }
    else if (drugie == "autor") 
    {
        dodaj_Wautorze();
    }
    else 
    {
        cout << "Zle dane";
        exit(0);
    }
}
void szukanie(string a)                         //szukanie w pliku po slowie kluczu
{
    a = usun(a);
    string drugie = pobierz(a);
    a = usun(a);
    if (drugie == "tytul")
    {
        szukaj_Wtytule(a);
    }
    else if (drugie == "autor")
    {
        szukaj_Wautorach(a);
    }
    else
    {
        cout << "Zle dane";
        exit(0);
    }
}
void usuwanie(string a)                         //usuwanie zadanego wpisu w bazie
{
    a = usun(a);
    string drugie = pobierz(a);
    a = usun(a);
    unsigned short u = 1;
    if (drugie == "tytul")
    {
        szukaj_Wtytule(a);                      //szuka wpisow i wypisuje je
        cout << "Podaj numer wpisu do usuniecia:";
        cin >> u;
        kasuj_wierszTytul(u);                   //usuwa wpis o numerze podanym przez uzytkownika
        cin.get();
    }
    else if (drugie == "autor")
    {
        szukaj_Wautorach(a);
        cout << "Podaj numer wpisu do usuniecia:";
        cin >> u;
        kasuj_wierszAutor(u);
        cin.get();
    }
    else
    {
        cout << "Zle dane";
        exit(0);
    }
}
void edytowanie(string a)                       //edytowanie wpisu
{
    a = usun(a);
    string drugie = pobierz(a);
    a = usun(a);
    unsigned short e = 1;
    if (drugie == "tytul")
    {
        szukaj_Wtytule(a);                      //szuka wpisow po slowie kluczu i je wypisuje
        cout << "Podaj numer wpisu do zedytowania:";
        cin >> e;
        kasuj_wierszTytul(e);                   //usuwa wpis o numerze podanym przez uzytkownika
        cin.get();
        dodaj_Wtytule();                        //dodaje nowy wpis
    }
    else if (drugie == "autor")
    {
        szukaj_Wautorach(a);
        cout << "Podaj numer wpisu do zedytowania:";
        cin >> e;
        kasuj_wierszAutor(e);
        cin.get();
        dodaj_Wautorze();
    }
    else
    {
        cout << "Zle dane";
        exit(0);
    }
}

void sterowanie() {
    string dane;
    string pierwsze;
    cout << "Podaj funkcje: "<< endl;
    getline(cin, dane);
    dane = wyczysc(dane);
    pierwsze = pobierz(dane);
    if (pierwsze == "dodaj")
    {
        dodawanie(dane);
        cout << "Dodales wpis!" << endl;
    }
    else if (pierwsze == "szukaj") szukanie(dane);
    else if (pierwsze == "edytuj")
    {
        edytowanie(dane);
        cout << "Zedytowales baze!" << endl;
    }
    else if (pierwsze == "usun")
    {
        usuwanie(dane);
        cout << "Usunales wpis!" << endl;
    }
    else {
        cout << "Niepoprawne dane";
        exit(0);
        }
}

int main()
{
    opis();
    for (unsigned short i = 1; i>0; i++)
    {
        sterowanie();
        int z = 0;
        cout << "Jesli chcesz dalej eksplorowac baze plikow wcisnij dowolna cyfre." << endl;
        cout << "Jesli chcesz zakonczyc wcisnij 1:";
        cin >> z;
        if (z == 1) break;
        cin.get();
    }
    return 0;
}

