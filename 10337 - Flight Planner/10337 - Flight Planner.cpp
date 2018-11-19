#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int odleglosc;

class Wycinek_nieba
{
  private:
    int wiatr,
        koszt_paliwa;

  public:
    void wypisz();
    void ustaw_wiatr(int);
    void ustaw_koszt(int);
    Wycinek_nieba(int, int);

    friend int koszt_optymalnej_podrozy(int,int,vector<vector<Wycinek_nieba> >);
};
void Wycinek_nieba::wypisz()
{
    cout<<this->wiatr<<"\t"<<this->koszt_paliwa<<endl;
}
void Wycinek_nieba::ustaw_wiatr(int sila_wiatru)
{
    this->wiatr = sila_wiatru;
}
void Wycinek_nieba::ustaw_koszt(int koszt_paliwa)
{
    this->koszt_paliwa = koszt_paliwa;
}
Wycinek_nieba::Wycinek_nieba(int wiatr = 0, int koszt_paliwa = 1)
{
    this->wiatr = wiatr;
    this->koszt_paliwa = koszt_paliwa;
}

int koszt_optymalnej_podrozy(int wiersz,int kolumna,vector<vector<Wycinek_nieba> > niebo)
{
    if(wiersz == 0 && kolumna == 0)
    {
        return 30-niebo[0][0].wiatr;
    }
    
    if(wiersz>9 || wiersz < 0 || kolumna > odleglosc)
    {
        return 1e8;
    }
    if(kolumna == odleglosc)
    {
        if(wiersz == 0) return 0;
        else return 1e8;
    }
    if(niebo[wiersz][kolumna].koszt_paliwa != -1)
    {
        return niebo[wiersz][kolumna].koszt_paliwa;
    }
    else
    {
        int minimum = min(  60-niebo[wiersz][kolumna].wiatr + koszt_optymalnej_podrozy(wiersz-1,kolumna-1,niebo),
                            min(    30-niebo[wiersz][kolumna].wiatr + koszt_optymalnej_podrozy(wiersz,kolumna-1,niebo),
                                    20-niebo[wiersz][kolumna].wiatr + koszt_optymalnej_podrozy(wiersz+1,kolumna-1,niebo)
                                )
                        );
        niebo[wiersz][kolumna].koszt_paliwa = minimum;
        //cout<<"minimum w "<<wiersz<<" "<<kolumna<<" to "<<minimum<<endl;
        return minimum;
    }
}

int main()
{
    int liczba_testow;
    cin >> liczba_testow;

    while (liczba_testow--)
    {
        int sila_wiatru;
        cin >> odleglosc;
        odleglosc /= 100;
        vector<vector<Wycinek_nieba> > niebo(10, vector<Wycinek_nieba>(odleglosc));

        for (int wiersz = 9; wiersz >= 0; wiersz--)
        {
            for (int kolumna = 0; kolumna < odleglosc; kolumna++)
            {
                cin>>sila_wiatru;
                niebo[wiersz][kolumna].ustaw_wiatr(sila_wiatru);
            }
        }
        cout<<koszt_optymalnej_podrozy(0,odleglosc-1,niebo);
    }
    return 0;
}
