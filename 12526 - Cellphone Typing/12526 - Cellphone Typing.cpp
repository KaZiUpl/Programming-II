#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

#define SIZE(x) (signed)x.size()

int klikniecia;

class Wezel
{
  private:
    char litera;
    bool czy_lisc;
    vector<Wezel> potomkowie;

  public:
    Wezel(char, bool);
    inline void zmien_stan(bool);
    void dodaj_potomka(string);
    void oblicz_klikniecia(int);
};
Wezel::Wezel(char litera = ' ', bool stan = false)
{
    this->litera = litera;
    this->czy_lisc = stan;
}
inline void Wezel::zmien_stan(bool stan)
{
    this->czy_lisc = stan;
}
void Wezel::dodaj_potomka(string wyraz)
{
    char pierwsza_litera = wyraz[0];

    wyraz = wyraz.substr(1, wyraz.size() - 1);

    int i;
    for (i = 0; i < SIZE(this->potomkowie); i++)
    {
        if (this->potomkowie[i].litera == pierwsza_litera)
        {
            if (wyraz.size() == 0)
            {
                this->potomkowie[i].zmien_stan(true);
            }
            else
            {
                this->potomkowie[i].dodaj_potomka(wyraz);
            }
            return;
        }
    }
    if (i == SIZE(this->potomkowie)) // nie ma takiego wyrazu
    {
        Wezel potomek(pierwsza_litera);
        if (wyraz.size() == 0)
        {
            potomek.zmien_stan(true);
            this->potomkowie.push_back(potomek);
        }
        else
        {
            potomek.dodaj_potomka(wyraz);
            this->potomkowie.push_back(potomek);
        }
    }
}
void Wezel::oblicz_klikniecia(int dotychczasowe = 1)
{
    if (this->czy_lisc)
    {
        klikniecia += dotychczasowe;
    }
    if (this->czy_lisc || SIZE(this->potomkowie) > 1)
    {
        if(this->litera != ' ')
        {
            dotychczasowe++;;
        }
    }

    for (int i = 0; i < SIZE(this->potomkowie); i++)
    {
        this->potomkowie[i].oblicz_klikniecia(dotychczasowe);
    }
}

int main()
{
    string wyraz;
    int liczba_wyrazow;

    while (cin >> liczba_wyrazow)
    {
        klikniecia = 0;
        Wezel *korzen = new Wezel();
        for (int i = 0; i < liczba_wyrazow; i++)
        {
            cin >> wyraz;
            korzen->dodaj_potomka(wyraz);
        }
        korzen->oblicz_klikniecia();
        cout << fixed << setprecision(2) << (double)(klikniecia) / (double)(liczba_wyrazow) << endl;
    }
    return 0;
}
