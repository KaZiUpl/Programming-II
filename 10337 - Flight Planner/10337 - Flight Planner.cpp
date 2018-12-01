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

    friend int main();
};
void Wycinek_nieba::wypisz()
{
    cout << this->wiatr << "\t" << this->koszt_paliwa << endl;
}
void Wycinek_nieba::ustaw_wiatr(int sila_wiatru)
{
    this->wiatr = sila_wiatru;
}
void Wycinek_nieba::ustaw_koszt(int koszt_paliwa)
{
    this->koszt_paliwa = koszt_paliwa;
}
Wycinek_nieba::Wycinek_nieba(int wiatr = -1e9, int koszt_paliwa = 0)
{
    this->wiatr = wiatr;
    this->koszt_paliwa = koszt_paliwa;
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
        vector<vector<Wycinek_nieba> > niebo(10, vector<Wycinek_nieba>(odleglosc + 1));

        for (int wiersz = 9; wiersz >= 0; wiersz--)
        {
            for (int kolumna = 0; kolumna < odleglosc; kolumna++)
            {
                cin >> sila_wiatru;
                niebo[wiersz][kolumna].ustaw_wiatr(sila_wiatru);
                if(kolumna == 0 && !wiersz==0) niebo[wiersz][kolumna].ustaw_koszt(500);
            }
        }
        for (int kolumna = 1; kolumna < odleglosc + 1; kolumna++)
        {
            for (int wiersz = 0; wiersz < 10; wiersz++)
            {
                if (wiersz == 0)
                {
                    niebo[wiersz][kolumna].koszt_paliwa = min(
                        20 - niebo[wiersz + 1][kolumna - 1].wiatr + niebo[wiersz + 1][kolumna - 1].koszt_paliwa,
                        30 - niebo[wiersz][kolumna - 1].wiatr + niebo[wiersz][kolumna - 1].koszt_paliwa);
                }
                else if(wiersz == 9)
                {
                    niebo[wiersz][kolumna].koszt_paliwa = min(
                        30 - niebo[wiersz][kolumna - 1].wiatr + niebo[wiersz][kolumna - 1].koszt_paliwa,
                        60 - niebo[wiersz-1][kolumna - 1].wiatr + niebo[wiersz-1][kolumna - 1].koszt_paliwa);
                }
                else
                {
                    niebo[wiersz][kolumna].koszt_paliwa = min(
                        60 - niebo[wiersz - 1][kolumna - 1].wiatr + niebo[wiersz - 1][kolumna - 1].koszt_paliwa,
                        min(
                            20 - niebo[wiersz + 1][kolumna - 1].wiatr + niebo[wiersz + 1][kolumna - 1].koszt_paliwa,
                            30 - niebo[wiersz][kolumna - 1].wiatr + niebo[wiersz][kolumna - 1].koszt_paliwa));
                }
            }
        }
        cout<<niebo[0][odleglosc].koszt_paliwa<<endl;
    }
    return 0;
}
