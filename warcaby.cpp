#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <utility>
#include <typeinfo>
#include <cmath>
using namespace std;

#define white_space 219

enum Kolor
{
    bialy = 0,
    czarny = 1
};
enum Typ_bierki
{
    pion_zwykly = 0,
    damka = 1
};

class Pion
{
  protected:
    Kolor kolor_bierki;
    Typ_bierki typ_bierki;

  public:
    Pion(){};
    Kolor zwroc_kolor();
    Typ_bierki zwroc_typ();
    virtual void wypisz_pionek() = 0;
};
Kolor Pion::zwroc_kolor()
{
    return kolor_bierki;
}
Typ_bierki Pion::zwroc_typ()
{
    return typ_bierki;
}

class Pion_zwykly : public Pion
{
  public:
    Pion_zwykly(){};
    Pion_zwykly(Kolor);
    virtual void wypisz_pionek();
};
Pion_zwykly::Pion_zwykly(Kolor kolor_pionka)
{
    kolor_bierki = kolor_pionka;
    typ_bierki = pion_zwykly;
}
void Pion_zwykly::wypisz_pionek()
{
    cout.width(1);
    if (kolor_bierki == bialy)
        cout << ' ' << 'x' << ' ';
    else if (kolor_bierki == czarny)
        cout << ' ' << 'o' << ' ';
    else
        cout << ' ' << ' ' << ' ';
}

class Damka : public Pion
{
  public:
    Damka(Kolor);
    virtual void wypisz_pionek();
};
Damka::Damka(Kolor kolor_damki)
{
    kolor_bierki = kolor_damki;
    typ_bierki = damka;
}
void Damka::wypisz_pionek()
{
    cout.width(1);
    if (kolor_bierki == bialy)
        cout << '-' << 'X' << '-';
    else if (kolor_bierki == czarny)
        cout << '-' << 'O' << '-';
    else
        cout << ' ' << ' ' << ' ';
}

class Komenda
{
  public:
    pair<int, int> skad, dokad;

    friend class Gracz;
    friend istream &operator>>(istream &input, Komenda &kom)
    {
        string czesc_pierwsza, czesc_druga;

        cin >> czesc_pierwsza >> czesc_druga;
        // ustawienie pierwszej wspolrzednej skad
        kom.skad.second = (int)czesc_pierwsza[0];
        if (czesc_pierwsza[0] >= 97)
            kom.skad.second -= 97;
        else if (czesc_pierwsza[0] >= 65)
            kom.skad.second -= 65;
        else
            kom.skad.second -= 48;
        // ustawienie pierwszej wspolrzednej dokad
        kom.dokad.second = (int)czesc_druga[0];
        if (czesc_druga[0] >= 97)
            kom.dokad.second -= 97;
        else if (czesc_druga[0] >= 65)
            kom.dokad.second -= 65;
        else
            kom.dokad.second -= 48;

        // ustawienie drugich wspolrzednych
        kom.skad.first = czesc_pierwsza[1] - 49;
        kom.dokad.first = czesc_druga[1] - 49;

        return input;
    }
    friend ostream &operator<<(ostream &output, const Komenda kom)
    {
        cout << "= = =" << endl;
        cout << "skad:\t" << kom.skad.first << " " << kom.skad.second << endl;
        cout << "dokad:\t" << kom.dokad.first << " " << kom.dokad.second << endl;
        cout << "= = =" << endl;

        return output;
    }
};

class Gracz
{
  private:
    Kolor kolor_gracza;
    string nick;

  public:
    Komenda ostatnia_komenda;
    Komenda ostatnia_bijaca_komenda;
    bool czy_zbil;
    void podaj_nick(int);
    string zwroc_nick();
    void podaj_ruch();
    Gracz(int, Kolor);
};
Gracz::Gracz(int numer_gracza, Kolor kolor_podany)
{
    kolor_gracza = kolor_podany;
    this->podaj_nick(numer_gracza);
}
void Gracz::podaj_nick(int numer_gracza)
{
    string nick_gracza;
    cout << "Podaj nick gracza " << numer_gracza << ":" << endl;
    cin >> nick_gracza;
    this->nick = nick_gracza;
}
string Gracz::zwroc_nick()
{
    return this->nick;
}
void Gracz::podaj_ruch()
{
    cin >> ostatnia_komenda;
}

class Gra
{
  private:
    vector<vector<Pion *> > szachownica;
    bool czy_aktywny_gracz_moze_zbic_kogokolwiek();
    bool czy_aktywny_gracz_moze_dalej_zbijac(int, Pion *);
    bool czy_aktywny_gracz_moze_wykonac_ruch(Pion *, Pion *, int);

  public:
    Gra();
    bool czy_zakonczona;
    Kolor aktywny_gracz;
    Gracz *gracze[2];
    void rysuj_szachownice();
    bool rozpatrz_ruch();
    int policz_bierki_gracza(Kolor);
};
Gra::Gra()
{
    vector<vector<Pion *> > szachownica(8, vector<Pion *>(8));
    // ustawienie wszystkiego na szachownicy
    Pion *bierka;
    for (int i = 0; i < 8; i++)
    {
        if (i == 0 || i == 1)
        {
            bierka = new Pion_zwykly(czarny);
        }
        else if (i == 6 || i == 7)
        {
            bierka = new Pion_zwykly(bialy);
        }

        for (int j = 0; j < 8; j += 2)
        {
            if (i == 0 || i == 6)
            {
                szachownica[i][j + 1] = bierka;
            }
            if (i == 1 || i == 7)
            {
                szachownica[i][j] = bierka;
            }
        }
    }
    this->szachownica = szachownica;

    //utworzenie graczy
    Gracz *gracz = new Gracz(0, bialy),
          *gracz2 = new Gracz(1, czarny);
    gracze[0] = gracz;
    gracze[1] = gracz2;

    aktywny_gracz = bialy;
    czy_zakonczona = false;
}
void Gra::rysuj_szachownice()
{
    cout << "strona gracza:\t" << gracze[1]->zwroc_nick() << endl;
    char litera = 'A';
    cout << " ";
    // rysowanie liter
    for (int i = 0; i < 8; i++)
    {
        cout.width(1);
        cout << ' ' << ' ' << litera++ << ' ' << ' ';
    }
    cout << endl
         << " ";
    for (int i = 0; i < 8; i++)
    {
        cout.width(5);
        cout << "-----";
    }
    cout << endl;
    // rysowanie szachownicy
    for (int i = 0; i < 8; i++) // petla na ilosc rzedow
    {
        char bialy = (char)219;
        string bialy_string = "";
        bialy_string += bialy;
        bialy_string += bialy;
        bialy_string += bialy;
        bialy_string += bialy;
        bialy_string += bialy;

        for (int j = 0; j < 3; j++) // petla na 1/3 pola
        {
            cout << '|';
            for (int h = 0; h < 8; h++)
            {
                if (i % 2 == 0)
                {
                    if (j == 1 && szachownica[i][h] != NULL)
                    {
                        cout.width(1);
                        cout << (h % 2 == 0 ? bialy : i);
                        szachownica[i][h]->wypisz_pionek();
                        cout.width(1);
                        cout << (h % 2 == 0 ? bialy : h);
                    }
                    else
                    {
                        cout.width(5);
                        cout << (h % 2 == 0 ? bialy_string : "     ");
                    }
                }

                else
                {
                    if (j == 1 && szachownica[i][h] != NULL)
                    {
                        cout.width(1);
                        cout << (h % 2 == 1 ? bialy : i);
                        szachownica[i][h]->wypisz_pionek();
                        cout.width(1);
                        cout << (h % 2 == 1 ? bialy : h);
                    }
                    else
                    {
                        cout.width(5);
                        cout << (h % 2 == 1 ? bialy_string : "     ");
                    }
                }
            }
            cout << '|';
            if (j == 1)
                cout << " " << i + 1;
            cout << endl;
        }
    }
    cout << " ";
    for (int i = 0; i < 8; i++)
    {
        cout.width(5);
        cout << "-----";
    }
    cout << endl;
    cout << "strona gracza:\t" << gracze[0]->zwroc_nick() << endl;
}
bool Gra::czy_aktywny_gracz_moze_dalej_zbijac(int numer_aktywnego_gracza, Pion *ostatnie_miejsce)
{
    // sprawdzanie, czy pion moze bic dalej
    if(!gracze[numer_aktywnego_gracza]->czy_zbil)
    {
        return false;
    }
    if (ostatnie_miejsce->zwroc_typ() == pion_zwykly)
    {
        cout << "Patrze, czy pion moze zbijac dalej" << endl;
        // petle sprawdzajace czy moze wokol siebie zbic bierke
        for (int i = -1; i <= 1; i += 2)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                // jezeli kolor jakiejkolwiek bierki wokol jest rozny od koloru aktywnego gracza i pole obok istnieje
                if (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + i >= 0
                    && gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + i <= 7
                    && gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + j >= 0
                    && gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + j <= 7
                    && szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + i][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + j] != NULL
                    && szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + i][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + j]->zwroc_kolor() != aktywny_gracz)
                {
                    // jezeli pole dalej istnieje i jest puste
                    if (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + 2 * i >= 0
                        && gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + 2 * i <= 7
                        && gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + 2 * j >= 0
                        && gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + 2 * j <= 7
                        && szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + 2 * i][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + 2 * j] == NULL)
                    {
                        cout << "Mozesz zbijac dalej!" << endl;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    // sprawdzanie, czy damka moze bic dalej
    else if (ostatnie_miejsce->zwroc_typ() == damka)
    {
        cout<<"Patrze, czy damka mozna zbijac dalej"<<endl;

        int strony_zajete_przez_sojusznikow = 0;
        bool napotkano_wroga = false;
        // petle sprawdzajace czy moze wokol siebie zbic bierke
        for (int i = -1; i <= 1; i += 2)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                int najwiekszy_mnoznik = min(   (i == -1 ? gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first: 7 - gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first) ,
                                                (j == -1 ? gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second: 7 - gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second) );

                //cout<<"Patrze strone "<<i<<" "<<j<<endl;
                //cout<<"Najwiekszy mnoznik to "<<najwiekszy_mnoznik<<endl;
                cout<<gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first<<" "<<gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second<<endl;
                int mnoznik = 1;
                // przegladam szachownice po diagonalach w kazda strone od damki
                while(mnoznik <= najwiekszy_mnoznik)
                {
                    //cout<<"Mnoznik = "<<mnoznik<<endl;
                    if(napotkano_wroga
                        && szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + mnoznik * i][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + mnoznik * j] == NULL)
                        {
                            //cout<<"Napotkalem na wroga i pole za nim bylo puste przy mnoznik = "<<mnoznik<<endl;
                            return true;
                        }
                    // jezeli natrafie na jakas bierke
                    if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + mnoznik * i][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + mnoznik * j] != NULL)
                    {
                        // sprawdzam, czy jest to bierka aktywnego gracza, jezeli jest to zmieniam flage i wychodze
                        if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + mnoznik * i][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + mnoznik * j]->zwroc_kolor() == aktywny_gracz)
                        {
                            //cout<<"Natrafilem na sojusznika przy mnoznik = "<<mnoznik<<endl;
                            strony_zajete_przez_sojusznikow++;
                            break;
                        }
                        // jezeli napotkano wroga
                        else
                        {
                            // jezeli pole za nim jest puste
                            if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first + mnoznik * i][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second + mnoznik * j]->zwroc_kolor() != aktywny_gracz)
                            {
                                //cout<<"Napotkalem wroga przy mnoznik = "<<mnoznik<<endl;
                                if(najwiekszy_mnoznik == mnoznik)
                                {
                                    return false;
                                }
                                napotkano_wroga = true;
                            }
                        }
                    }
                    mnoznik++;
                }
            }
        }
        if(strony_zajete_przez_sojusznikow >= 4)
        {
            //cout<<"Wszystkie strony zajete przez sojusznikow"<<endl;
            return false;
        }
        else if(!napotkano_wroga)
        {
            cout<<"Nie ma kogo zbijac"<<endl;
            return false;
        }
    }
    else
    {
        cout << "Cos nie pyklo w czy_aktywny_gracz_moze_dalej_zbijac()" << endl;
    }
    return true;
}
bool Gra::czy_aktywny_gracz_moze_wykonac_ruch(Pion *poruszana_bierka, Pion *docelowe_miejsce, int numer_aktywnego_gracza)
{
    // sprawdzenie, czy pion zostal zbity i czy gracz chce ruszyc sie czyms innym niz tym, ktory zbil
    if (gracze[numer_aktywnego_gracza]->czy_zbil)
    {
        if (gracze[numer_aktywnego_gracza]->ostatnia_bijaca_komenda.dokad != gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad)
        {
            cout << "Musisz sie ruszyc pionem, ktory ostatnio bil!" << endl;
            return false;
        }
    }
    // sprawdzanie, czy gracz chce sie poruszyc swoja bierka
    if (poruszana_bierka == NULL || poruszana_bierka->zwroc_kolor() != aktywny_gracz)
    {
        cout << "Chcesz poruszyc nie swoja bierke!" << endl;
        return false;
    }
    // w tej chwili wiadomo, ze gracz chce sie ruszyc swoja bierka
    // sprawdzanie, czy gracz chce sie poruszyc w dobra strone i dobre miejsce
    // jezeli gracz chce sie przesunac na zajete miejsce, to blad
    if (docelowe_miejsce != NULL && (docelowe_miejsce->zwroc_kolor() == czarny || docelowe_miejsce->zwroc_kolor() == bialy))
    {
        return false;
    }
    // inne przypadki
    int dlugosc_pion = abs(gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first);                  // dlugosc w pionie
    int dlugosc_poziom = abs(gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second);              // dlugoscw poziomie
    int zmiana_pion = (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first) / dlugosc_pion;       // w ktora strone chce isc w pionie (+-1)
    int zmiana_poziom = (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second) / dlugosc_poziom; // w ktora strone chec isc w poziomie (+-1)

    //cout << "dlugosc pion: " << dlugosc_pion << endl;
    //cout << "dlugosc poziom: " << dlugosc_poziom << endl;
    //cout << "zmiana pion: " << zmiana_pion << endl;
    //cout << "zmiana poziom: " << zmiana_poziom << endl;
    //cout << gracze[numer_aktywnego_gracza]->ostatnia_komenda;

    // jezeli gracz chce poruszyc sie nie po diagonalu
    if (dlugosc_pion != dlugosc_poziom)
    {
        cout << "Mozna sie poruszac tylko do liniach diagonalnych!" << endl;
        return false;
    }
    // jezeli porusza sie zwyklym pionkiem
    if (poruszana_bierka->zwroc_typ() == pion_zwykly)
    {
        //cout << "Poruszana bierka to pion " << numer_aktywnego_gracza << endl;
        //cout << "Zmiana pion i dlugosc pion " << zmiana_pion << " " << dlugosc_pion << endl;
        if (gracze[numer_aktywnego_gracza]->czy_zbil && dlugosc_pion == 1)
        {
            cout << "Musisz bic a nie sie ruszac!" << endl;
            return false;
        }
        if (zmiana_pion == (numer_aktywnego_gracza == 0 ? 1 : -1) && dlugosc_pion == 1) // jezeli chce sie poruszyc do tylu
        {
            cout << "Nie mozesz ruszac sie do tylu!" << endl;
            return false;
        }
        else if (dlugosc_pion > 2) // jezeli chce sie poruszyc o wiecej niz dwa pola
        {
            cout << "Nie mozesz poruszyc sie pionkiem o wiecej niz 2 pola!" << endl;
            return false;
        }
        else if (dlugosc_pion == 2)
        {
            // jezeli chce zbic bierke nalezaca do siebie lub puste pole
            if (szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + zmiana_poziom] == NULL || szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + zmiana_poziom]->zwroc_kolor() == aktywny_gracz)
            {
                cout << "Chcesz zbic puste miejsce lub swoja bierke!" << endl;
                return false;
            }
            else
            {
                //cout << "Teoretycznie zbilem" << endl;
                return true;
            }
        }
    }
    // jezeli porusza sie damka
    else if (poruszana_bierka->zwroc_typ() == damka) // jezeli porusza sie damka
    {
        cout<<"Poruszasz sie damka"<<endl;
        if (gracze[numer_aktywnego_gracza]->czy_zbil)
        {
            //cout<<"Bylo zbite"<<endl;
            if(dlugosc_pion == 1)
            {
                cout << "Musisz bic a nie sie ruszac!" << endl;
                return false;
            }
            bool czy_napotkalem_przeciwnika = false;
            for (int i = 1; i < dlugosc_pion; i++)
            {
                if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom] != NULL)
                {
                    if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom]->zwroc_kolor() != aktywny_gracz)
                    {
                        czy_napotkalem_przeciwnika = true;
                    }
                }
            }
            if(!czy_napotkalem_przeciwnika)
            {
                cout << "Musisz bic a nie sie ruszac!" << endl;
                return false;
            }
        }
        int ilosc_pionkow_na_przeszkodzie = 0;
        //popatrz, ile jest pionkow na przeszkodzie, jezeli ktorykolwiek ma taki sam kolor jak damka to blad
        for (int i = 1; i < dlugosc_pion; i++)
        {
            if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom] != NULL)
            {
                if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom]->zwroc_kolor() == aktywny_gracz)
                {
                    cout<<"Na drodze bicia stoi Twoj pionek!"<<endl;
                    return false;
                }
                else if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom]->zwroc_kolor() != aktywny_gracz)
                {
                    ilosc_pionkow_na_przeszkodzie++;
                }
            }
        }
        if(ilosc_pionkow_na_przeszkodzie > 1)
        {
            cout<<"Na drodze stoi wiecej niz jeden pionek przeciwnika!"<<endl;
            return false;
        }
        return true;
    }
    else
    {
        cout << "Cos nie pyklo w czy_aktywny_gracz_moze_wykonac_ruch()" << endl;
    }
    return true;
}
bool Gra::rozpatrz_ruch()
{
    int numer_aktywnego_gracza = (aktywny_gracz == bialy ? 0 : 1);
    cout << numer_aktywnego_gracza << endl;

    Pion *poruszana_bierka, *docelowe_miejsce;

    poruszana_bierka = szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second];
    docelowe_miejsce = szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second];

    if (!czy_aktywny_gracz_moze_wykonac_ruch(poruszana_bierka, docelowe_miejsce, numer_aktywnego_gracza))
    {
        return false;
    }

    int dlugosc_pion = abs(gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first);                  // dlugosc w pionie
    int dlugosc_poziom = abs(gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second);              // dlugoscw poziomie
    int zmiana_pion = (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first) / dlugosc_pion;       // w ktora strone chce isc w pionie (+-1)
    int zmiana_poziom = (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second - gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second) / dlugosc_poziom; // w ktora strone chec isc w poziomie (+-1)

    if(poruszana_bierka->zwroc_typ() == pion_zwykly)
    {
        if (dlugosc_pion == 1)
        {
            // przesuniecie bierki
            szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second] = poruszana_bierka;
            szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second] = NULL;
            // bierka tylko przesunieta, wiec kolej nastepnego gracza
            if (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first == (aktywny_gracz == bialy ? 0 : 7))
            {
                szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second] = new Damka(aktywny_gracz);
            }
            aktywny_gracz = (aktywny_gracz == bialy ? czarny : bialy);
        }
        else if (dlugosc_pion == 2)
        {
            // przesuniecie bierki
            szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second] = poruszana_bierka;
            szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second] = NULL;
            // usuniecie bierki przeciwnika o ile istnieje
            if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + zmiana_poziom] != NULL)
            {
                gracze[numer_aktywnego_gracza]->czy_zbil = true;
                gracze[numer_aktywnego_gracza]->ostatnia_bijaca_komenda = gracze[numer_aktywnego_gracza]->ostatnia_komenda;
                szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + zmiana_poziom] = NULL;
            }
            // bierka tylko przesunieta, wiec kolej nastepnego gracza
            if (!czy_aktywny_gracz_moze_dalej_zbijac(numer_aktywnego_gracza, poruszana_bierka))
            {
                if (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first == (aktywny_gracz == bialy ? 0 : 7)
                    && szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second]->zwroc_typ() != damka)
                {
                    Pion *damka = new Damka(aktywny_gracz);
                    szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second] = damka;
                }
                gracze[numer_aktywnego_gracza]->czy_zbil = false;
                aktywny_gracz = (aktywny_gracz == bialy ? czarny : bialy);
            }
        }
    }
    else if(poruszana_bierka->zwroc_typ() == damka)
    {
        // przesuniecie bierki i usuniecie bierki przeciwnika
        // przesuniecie bierki
        szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second] = poruszana_bierka;
        // petla szukajaca i usuwajaca zbita bierke
        for (int i = 1; i < dlugosc_pion; i++)
        {
            if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom] != NULL)
            {
                if(szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom]->zwroc_kolor() != aktywny_gracz)
                {
                    szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first + i*zmiana_pion][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second + i*zmiana_poziom] = NULL;
                    // zmiana ostatniej bijacej komendy
                    gracze[numer_aktywnego_gracza]->ostatnia_bijaca_komenda = gracze[numer_aktywnego_gracza]->ostatnia_komenda;
                    // zaznaczenie bicia
                    gracze[numer_aktywnego_gracza]->czy_zbil = true;
                    break;
                }
            }

        }
        // usuniecie ruszanej bierki ze starej pozycji
        szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.skad.second] = NULL;

        // bierka tylko przesunieta, wiec kolej nastepnego gracza
        if (!czy_aktywny_gracz_moze_dalej_zbijac(numer_aktywnego_gracza, poruszana_bierka))
        {
            if (gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first == (aktywny_gracz == bialy ? 0 : 7)
                && szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second]->zwroc_typ() != damka)
            {
                Pion *damka = new Damka(aktywny_gracz);
                szachownica[gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.first][gracze[numer_aktywnego_gracza]->ostatnia_komenda.dokad.second] = damka;
            }
            gracze[numer_aktywnego_gracza]->czy_zbil = false;
            aktywny_gracz = (aktywny_gracz == bialy ? czarny : bialy);
        }
    }
    return true;
}
int Gra::policz_bierki_gracza(Kolor kolor_gracza)
{
    int wynik = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (szachownica[i][j] != NULL
                && szachownica[i][j]->zwroc_kolor() == kolor_gracza)
            {
                wynik++;
            }
        }
    }
    return wynik;
}
int main()
{
    string decyzja_o_grze;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - WARCABY - - - - - - - - - - - - - - - - - - - - - - " << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
    cout << "INSTRUKCJA:" << endl;
    cout << "1) Ruchy podawaj w formacie: skad dokad, np. B7 C6" << endl;
    cout << "2) Zasady jak w normalnych warcabach" << endl;
    cout << "3) Gracz bialy ma pionki 'x' oraz damki '-X-'" << endl;
    cout << "4) Gracz czarny ma pionki 'o' oraz damki '-O-'" << endl;
    cout << "Czy chcesz rozpoczac gre? (tak/cokolwiek): \t";
    while (cin >> decyzja_o_grze && decyzja_o_grze == "tak")
    {
        system("cls");
        Gra giera = Gra(); // tutaj nastepuje wprowadzanie graczy
        while (giera.czy_zakonczona == false)
        {
            //system("cls");
            cout << "+---------------------------------+ NOWY RUCH +---------------------------------+" << endl;
            cout << "+-------------------------------------------------------------------------------+" << endl;
            giera.rysuj_szachownice();

            if(!giera.policz_bierki_gracza(giera.aktywny_gracz))
            {
                giera.czy_zakonczona = true;
                cout << "+-------------------------------------------------------------------------------+" << endl;
                cout << "+-------------------------------------------------------------------------------+" << endl;
                cout << "+-------------------------------------------------------------------------------+" << endl;
                cout << "+-------------------------------------------------------------------------------+" << endl;
                cout << "GRACZ " << (giera.aktywny_gracz == bialy ? giera.gracze[0]->zwroc_nick() : giera.gracze[1]->zwroc_nick()) << " WYGRYWA!!!" << endl;
                continue;
            }

            cout << "Podaj komende ruchu gracza " << (giera.aktywny_gracz == bialy ? giera.gracze[0]->zwroc_nick() : giera.gracze[1]->zwroc_nick()) << ": " << endl;
            if (giera.aktywny_gracz == bialy)
            {
                giera.gracze[0]->podaj_ruch();
            }
            else
            {
                giera.gracze[1]->podaj_ruch();
            }
            // dopoki nie podano prawidlowego ruchu to program prosi o podanie dobrego
            while (!giera.rozpatrz_ruch())
            {
                if (giera.aktywny_gracz == bialy)
                {
                    giera.gracze[0]->podaj_ruch();
                }
                else
                {
                    giera.gracze[1]->podaj_ruch();
                }
            }
        }

        cout << "Czy chcesz rozpoczac nowa gre? (tak/cokolwiek): \t";
    }

    return 0;
}
