#include<iostream>
#include<vector>
using namespace std;

class Czworka
{
public:
    int numer;
    int tab[4];
};
bool operator!=(Czworka pierwsza,Czworka druga)
{
    for(int i=0;i<4;i++)
    {
        if(pierwsza.tab[i] != druga.tab[i]) return true;
    }
    return false;
}

void sortowanie(vector<Czworka> czworki,int pozycja)
{
    for(int i=0;i<czworki.size();i++)
    {
        for(int j=0;j<czworki.size()-1;j++)
        {
            if(czworki[i].tab[pozycja] < czworki[j].tab[pozycja])
            {
                swap(czworki[i],czworki[j]);
            }
        }
    }

    //cout<<"Wzgledem pozycji "<<pozycja<<endl;
    for(int i=0;i<czworki.size();i++)
    {
        cout<<czworki[i].numer<<" ";
    }
    cout<<endl;

}

int main()
{
    vector<Czworka> czworki;
    int ilosc_czworek,
        liczba;

    cin>>ilosc_czworek;
    for(int i=0;i<ilosc_czworek;i++)
    {
        Czworka czworka;
        czworka.numer = i+1;
        for(int j=0;j<4;j++)
        {
            cin>>czworka.tab[j];
        }
        czworki.push_back(czworka);
    }

    vector<Czworka> czworki_kopia;
    for(int i=0;i<4;i++)
    {
        czworki_kopia = czworki;
        sortowanie(czworki_kopia,i);
    }

    // for(int i=0;i<czworki.size();i++)
    // {
    //     cout<<"Numer: "<<czworki[i].numer<<", ";
    //     for(int j=0;j<4;j++)
    //     {
    //         cout<<czworki[i].tab[j]<<" ";
    //     }
    //     cout<<endl;
    // }

    return 0;
}
