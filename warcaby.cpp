#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
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
    virtual void wypisz_pionek() = 0;
};

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

class Gra
{
  private:
    vector<vector<Pion *> > szachownica;

  public:
    Gra();
    void rysuj_szachownice();
};
Gra::Gra()
{
    vector<vector<Pion *> > szachownica(8, vector<Pion *>(8));


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
}
void Gra::rysuj_szachownice()
{
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
}

int main()
{
    Gra giera = Gra();
    giera.rysuj_szachownice();
    /*- Rysowanie planszy -*/
    return 0;
}
