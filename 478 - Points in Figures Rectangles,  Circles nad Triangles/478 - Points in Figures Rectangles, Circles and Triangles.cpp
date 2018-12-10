#include <iostream>
#include <vector>
using namespace std;

class Punkt
{
public:
    double x, y;
    Punkt() {};
    Punkt(double,double);

    friend istream & operator>>(istream & input, Punkt &punkt)
    {
        cin>>punkt.x>>punkt.y;
        return input;
    }
};

Punkt::Punkt(double x,double y)
{
    this->x = x;
    this->y = y;
}

class Figura
{
public:
    virtual bool czy_jest_w_srodku(Punkt) = 0;
    virtual void get() = 0;
};

class Prostokat: public Figura
{
private:
    Punkt lewy_gorny, lewy_dolny, prawy_dolny, prawy_gorny;
public:
    Prostokat() {};
    virtual bool czy_jest_w_srodku(Punkt);
    virtual void get();
};

void Prostokat::get()
{
    cin>>this->lewy_gorny>>this->prawy_dolny;
    this->lewy_dolny = Punkt(this->lewy_gorny.x,this->prawy_dolny.y);
    this->prawy_gorny = Punkt(this->prawy_dolny.x,this->lewy_gorny.y);
}
bool Prostokat::czy_jest_w_srodku(Punkt p)
{
    return (p.x <= this->prawy_gorny.x && p.x >= this->lewy_gorny.x && p.y <= prawy_gorny.y && p.y >= lewy_dolny.y);
}

class Okrag: public Figura
{
private:
    Punkt srodek;
    double promien;
public:
    Okrag() {};
    virtual bool czy_jest_w_srodku(Punkt);
    virtual void get();
};

void Okrag::get()
{
    cin>>this->srodek;
    cin>>this->promien;
}
bool Okrag::czy_jest_w_srodku(Punkt p)
{
    return ( (this->srodek.x - p.x)*(this->srodek.x - p.x) + (this->srodek.y - p.y) * (this->srodek.y - p.y) <= this->promien*this->promien );
}

class Trojkat: public Figura
{
private:
    Punkt a, b, c;
public:
    Trojkat() {};
    virtual bool czy_jest_w_srodku(Punkt);
    virtual void get();
};

void Trojkat::get()
{
    cin>>this->a>>this->b>>this->c;
}
bool Trojkat::czy_jest_w_srodku(Punkt p)
{
    bool czy_zawiera = false;



    return czy_zawiera;
}

int main()
{
    char znak_figury;
    Punkt punkt_do_sprawdzenia;
    vector <Figura *> figury;

    while(cin>>znak_figury && znak_figury != '*')
    {
        Figura *nowa;
        switch(znak_figury)
        {
        case 'r':
            nowa = new Prostokat();
            nowa->get();
            break;
        case 'c':
            nowa = new Okrag();
            nowa->get();
            break;
        case 't':
            nowa = new Trojkat();
            nowa->get();
            break;
        }
        figury.push_back(nowa);
        cout<<"dodano figure"<<endl;
    }

    int licznik_punktow = 1;

    while(cin>>punkt_do_sprawdzenia && punkt_do_sprawdzenia.x != 9999.9 && punkt_do_sprawdzenia.y != 9999.9)
    {
        for(int i=0;i<figury.size();i++)
        {
            bool flaga = false;
            if(figury[i].czy_jest_w_srodku(punkt_do_sprawdzenia))
            {
                cout<<"Point "<<licznik_punktow++<<" is contained in figure "<<i+1<<endl;
                flaga = true;
            }
        }
        if(flaga == false)
        {
            cout<<"Point "<<licznik_punktow++<<" is not contained in any figure "<<endl;
        }
    }

    return 0;
}
