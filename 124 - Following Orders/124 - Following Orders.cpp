#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define SIZE(x) (signed)x.size()

vector<char> wpisz_litery(string);
vector<pair<char, char> > wpisz_reguly(string);
bool czy_to_prawidlowa_permutacja(vector<char>, vector<pair<char, char> >);

int main()
{
    string litery,
        reguly;

    while (getline(cin, litery))
    {
        vector<pair<char, char> > reguly_vec;
        vector<char> litery_vec = wpisz_litery(litery);

        getline(cin, reguly);
        reguly_vec = wpisz_reguly(reguly);

        do
        {

            if (czy_to_prawidlowa_permutacja(litery_vec, reguly_vec))
            {
                for (int i = 0; i < SIZE(litery_vec); i++)
            {
                cout << litery_vec[i];
            }
            cout << endl;
            }
        } while (next_permutation(litery_vec.begin(), litery_vec.end()));
    }

    return 0;
}

vector<char> wpisz_litery(string litery)
{
    vector<char> wynik;
    for (int i = 0; i < SIZE(litery); i++)
    {
        if (litery[i] != ' ')
            wynik.push_back(litery[i]);
    }
    sort(wynik.begin(), wynik.end());
    return wynik;
}
vector<pair<char, char> > wpisz_reguly(string reguly)
{
    vector<pair<char, char> > wynik;
    for (int i = 0; i < SIZE(reguly);)
    {
        pair<char, char> para;
        para.first = reguly[i];
        i += 2;
        para.second = reguly[i];
        wynik.push_back(para);
        i += 2;
    }
    return wynik;
}
bool czy_to_prawidlowa_permutacja(vector<char> litery, vector<pair<char, char> > reguly)
{
    int pozycja_pierwsza,
        pozycja_druga;
    for (int i = 0; i < SIZE(reguly); i++)
    {
        pozycja_pierwsza = -1;
        pozycja_druga = -1;
        for (int j = 0; j < SIZE(litery); j++)
        {
            if (litery[j] == reguly[i].first)
                pozycja_pierwsza = j;
        }
        for (int j = 0; j < SIZE(litery); j++)
        {
            if (litery[j] == reguly[i].second)
                pozycja_druga = j;
        }
        if (pozycja_druga < pozycja_pierwsza)
            return false;
    }
    return true;
}
