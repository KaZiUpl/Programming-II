#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

#define white_space 219

class Pion
{
protected:
    int kolor;
public:
    Pion(){};
    char znak;
};


class Pion_zwykly : public Pion
{

};


class Damka : public Pion
{

};


class Gra
{
private:
    vector<vector<Pion> > szachownica;
public:
    Gra();
    void rysuj_szachownice();
};
Gra::Gra()
{
    vector<vector<Pion> > szachownica(8,vector<Pion>(8));
    this->szachownica = szachownica;
}
void Gra::rysuj_szachownice()
{
    char litera = 'A';
    cout<<" ";
    for(int i=0;i<8;i++)
    {
        cout.width(1);
        cout<<' '<<' '<<litera++<<' '<<' ';
    }
    cout<<endl<<" ";
    for(int i=0;i<8;i++)
    {
        cout.width(5);
        cout<<"-----";
    }
    cout<<endl;

    for(int i=0;i<8;i++) // petla na ilosc rzedow
    {
        char bialy = 219;
        string bialy_string = "";
        bialy_string += bialy;
        bialy_string += bialy;
        bialy_string += bialy;
        bialy_string += bialy;
        bialy_string += bialy;

        for(int j=0;j<3;j++) // petla na 1/3 pola
        {
            cout<<'|';
            for(int h=0;h<8;h++)
            {
                if(i%2==0)
                {
                    cout.width(5);
                    cout<<(h%2==0 ? bialy_string : "     ");
                }
                else
                {
                    cout.width(5);
                cout<<(h%2==1 ? bialy_string : "     ");
                }

            }
            cout<<'|';
            cout<<endl;
            // gorna czesc
            // srodek

            // dolna czesc

        }

    }
    cout<<" ";
    for(int i=0;i<8;i++)
    {
        cout.width(5);
        cout<<"-----";
    }
}

int main()
{
    Gra giera;
    giera.rysuj_szachownice();
    /*- Rysowanie planszy -*/
    return 0;
}
