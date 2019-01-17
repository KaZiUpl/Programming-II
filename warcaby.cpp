#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <utility>
using namespace std;

#define white_space 219

enum Kolor
{
    bialy,
    czarny
};

class Pion
{
  protected:
    Kolor kolor_bierki;
  public:
    Pion(){};
    Kolor zwroc_kolor();
    virtual void wypisz_pionek() = 0;
};
Kolor Pion::zwroc_kolor()
{
    return kolor_bierki;
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
}
void Pion_zwykly::wypisz_pionek()
{
    cout.width(1);
    if (kolor_bierki == bialy)
        cout << 'x';
    else if (kolor_bierki == czarny)
        cout << 'o';
    else
        cout << ' ';
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
}
void Damka::wypisz_pionek()
{
    cout.width(1);
    if (kolor_bierki == bialy)
        cout << 'X';
    else if (kolor_bierki == czarny)
        cout << 'O';
    else
        cout << ' ';
}

class Komenda
{
 public:
    pair<int,int> skad, dokad;

    friend class Gracz;
    friend istream& operator>>(istream& input, Komenda & kom)
    {
        string czesc_pierwsza, czesc_druga;

        cin>>czesc_pierwsza>>czesc_druga;
        // ustawienie pierwszej wspolrzednej skad
        kom.skad.second = (int)czesc_pierwsza[0];
        if(czesc_pierwsza[0] >= 97) kom.skad.second -= 97;
        else if(czesc_pierwsza[0] >= 65) kom.skad.second -= 65;
        else kom.skad.second -= 48;
        // ustawienie pierwszej wspolrzednej dokad
        kom.dokad.second = (int)czesc_druga[0];
        if(czesc_druga[0] >= 97) kom.dokad.second -= 97;
        else if(czesc_druga[0] >= 65) kom.dokad.second -= 65;
        else kom.dokad.second -= 48;

        // ustawienie drugich wspolrzednych
        kom.skad.first = czesc_pierwsza[1] - 49;
        kom.dokad.first = czesc_druga[1] - 49;

        return input;
    }
    friend ostream& operator<<(ostream &output, const Komenda kom)
    {
        cout<<"= = ="<<endl;
        cout<<"skad:\t"<<kom.skad.first<<" "<<kom.skad.second<<endl;
        cout<<"dokad:\t"<<kom.dokad.first<<" "<<kom.dokad.second<<endl;
        cout<<"= = ="<<endl;
        
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
    cout<<"Podaj nick gracza "<<numer_gracza<<":"<<endl;
    cin>>nick_gracza;
    this->nick = nick_gracza;
}
string Gracz::zwroc_nick()
{
    return this->nick;
}
void Gracz::podaj_ruch()
{
    cin>>ostatnia_komenda;
}

class Gra
{
  private:
    vector<vector<Pion *> > szachownica;
    bool czy_zbito_bierke;
    bool czy_aktywny_gracz_moze_wykonac_ruch();
  public:
    Gra();
    bool czy_zakonczona;
    Kolor aktywny_gracz;
    Gracz *gracze[2];
    void rysuj_szachownice();
    bool rozpatrz_ruch();
};
Gra::Gra()
{
    vector<vector<Pion *> > szachownica(8, vector<Pion *>(8));
    // ustawienie wszystkiego na szachownicy
    for(int i=0;i<8;i++)
    {
        Pion *bierka;
        if(i == 0 || i == 1)
        {
            bierka = new Pion_zwykly(czarny);
        }
        else if(i == 6 || i == 7)
        {
            bierka = new Pion_zwykly(bialy);
        }

        for(int j=0;j<8;j+=2)
        {
            if(i==0 || i == 6)
            {
                szachownica[i][j+1] = bierka;
            }
            if(i == 1 || i == 7)
            {
                szachownica[i][j] = bierka;
            }
        }
    }
    this->szachownica = szachownica;

    //utworzenie graczy
    Gracz *gracz = new Gracz(0,bialy),
            *gracz2 = new Gracz(1,czarny);
    gracze[0] = gracz;
    gracze[1] = gracz2;

    aktywny_gracz = bialy;
    czy_zakonczona = false;
}
void Gra::rysuj_szachownice()
{
    cout<<"strona gracza:\t"<<gracze[1]->zwroc_nick()<<endl;
    char litera = 'A';
    cout << " ";
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

    for (int i = 0; i < 8; i++) // petla na ilosc rzedow
    {
        char bialy = 219;
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
                    if(j==1 && szachownica[i][h] != NULL)
                    {
                        cout.width(1);
                        cout << (h % 2 == 0 ? bialy : ' ');
                        cout.width(1);
                        cout<<' ';
                        szachownica[i][h]->wypisz_pionek();
                        cout.width(1);
                        cout<<' ';
                        cout.width(1);
                        cout << (h % 2 == 0 ? bialy : ' ');
                    }
                    else
                    {
                        cout.width(5);
                        cout << (h % 2 == 0 ? bialy_string : "     ");
                    }

                }
                else
                {
                    if(j==1 && szachownica[i][h] != NULL)
                    {
                        cout.width(1);
                        cout << (h % 2 == 1 ? bialy : ' ');
                        cout.width(1);
                        cout<<' ';
                        szachownica[i][h]->wypisz_pionek();
                        cout.width(1);
                        cout<<' ';
                        cout.width(1);
                        cout << (h % 2 == 1 ? bialy : ' ');
                    }
                    else
                    {
                        cout.width(5);
                        cout << (h % 2 == 1 ? bialy_string : "     ");
                    }

                }
            }
            cout << '|';
            if(j == 1) cout<< " "<<i+1;
            cout << endl;
        }
    }
    cout << " ";
    for (int i = 0; i < 8; i++)
    {
        cout.width(5);
        cout << "-----";
    }
    cout<<endl;
    cout<<"strona gracza:\t"<<gracze[0]->zwroc_nick()<<endl;
}
bool Gra::czy_aktywny_gracz_moze_wykonac_ruch()
{
    // sprawdzanie, czy gracz chce sie poruszyc swoja bierka
    
    if(aktywny_gracz == bialy && 
        (szachownica[gracze[0]->ostatnia_komenda.skad.first][gracze[0]->ostatnia_komenda.skad.second] == NULL || 
            szachownica[gracze[0]->ostatnia_komenda.skad.first][gracze[0]->ostatnia_komenda.skad.second]->zwroc_kolor() == czarny))
    {   
        return false;
    }
    else if(aktywny_gracz == czarny && 
        (szachownica[gracze[1]->ostatnia_komenda.skad.first][gracze[1]->ostatnia_komenda.skad.second] == NULL || 
            szachownica[gracze[1]->ostatnia_komenda.skad.first][gracze[1]->ostatnia_komenda.skad.second]->zwroc_kolor() == bialy))
    {
        return false;
    }
    // w tej chwili wiadomo, ze gracz chce sie ruszyc swoja bierka
    // sprawdzanie, czy gracz chce sie poruszyc w dobra strone
    
    
    for(int i=0 ; i<8 ; i++)
    {
        for(int j=0; j<8 ; j++)
        {
            if(szachownica[i][j] != NULL) // sprawdzam, czy pole nie jest puste
            {
                // patrze, ktory gracz obecnie wykonuje ruch
                if(aktywny_gracz == bialy)
                {
                    cout<<"pleple"<<endl;
                }
                else
                {
                    cout<<"klekle"<<endl;
                }
            }
            
        }
    }
    return true;
}
bool Gra::rozpatrz_ruch()
{
    if(!czy_aktywny_gracz_moze_wykonac_ruch()) 
    {
        cout<<gracze[0]->ostatnia_komenda;
        return false;
    }
    // zamiana aktywnego gracza
    if(aktywny_gracz == bialy) aktywny_gracz = czarny;
    else aktywny_gracz = bialy;
    return true;
}

int main()
{
    string decyzja_o_grze;
    cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "<<endl;
    cout<<"- - - - - - - - - - - - - - - - - - - - - - WARCABY - - - - - - - - - - - - - - - - - - - - - - "<<endl;
    cout<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "<<endl;
    cout<<"INSTRUKCJA:"<<endl;
    cout<<"1) Ruchy podawaj w formacie: skad dokad, np. B7 C6"<<endl;
    cout<<"2) Zasady jak w normalnych warcabach"<<endl;
    cout<<"3) Gracz bialy ma pionki 'x' oraz damki 'X'"<<endl;
    cout<<"4) Gracz czarny ma pionki 'o' oraz damki 'O'"<<endl;
    cout<<"Czy chcesz rozpoczac gre? (tak/cokolwiek): \t";
    while(cin>>decyzja_o_grze && decyzja_o_grze == "tak")
    {
        system("cls");
        Gra giera = Gra();
        // tutaj nastepuje wprowadzanie graczy

        while(giera.czy_zakonczona == false)
        {
            system("cls");
            giera.rysuj_szachownice();
            cout<<"Podaj komende ruchu gracza "<<(giera.aktywny_gracz == bialy ? giera.gracze[0]->zwroc_nick() : giera.gracze[1]->zwroc_nick())<<": "<<endl;
            if(giera.aktywny_gracz == bialy)
            {
                giera.gracze[0]->podaj_ruch();
            }
            else
            {
                giera.gracze[1]->podaj_ruch();
            }
            // dopoki nie podano prawidlowego ruchu to program prosi o podanie dobrego
            while(!giera.rozpatrz_ruch())
            {
                cout<<"Nie mozesz wykonac tego ruchu, podaj prawidlowy ruch:"<<endl;
                if(giera.aktywny_gracz == bialy)
                {
                    giera.gracze[0]->podaj_ruch();
                }
                else
                {
                    giera.gracze[1]->podaj_ruch();
                }
            }


            
            int cos;
            cin>>cos;

        }



        cout<<"Czy chcesz rozpoczac nowa gre? (tak/cokolwiek): \t";
    }

    return 0;
}
