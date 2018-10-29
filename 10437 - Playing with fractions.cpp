#include<iostream>
#include<cmath>

using namespace std;

class Fraction
{
private:
    long int numerator, denominator;
public:
    Fraction();
    Fraction(long int numerator,long int denominator);
    long int    get_numerator(),
                get_denominator();
    Fraction operator+(Fraction other_one);
    Fraction operator-(Fraction other_one);
    Fraction operator*(Fraction other_one);
    Fraction operator/(Fraction other_one);
    void reduce_fraction();
    bool operator<(Fraction other_one);

};

int GCD(long int a, long int b)
{
    if(b == 0) return abs(a);
    else       return GCD(abs(b), abs(a % b)) ;
}

Fraction::Fraction()
{
    numerator = 0;
    denominator = 1;
}
Fraction::Fraction(long int numerator,long int denominator)
{
    this->numerator = numerator;
    this->denominator = denominator;
}
long int Fraction::get_numerator()
{
    return numerator;
}
long int Fraction::get_denominator()
{
    return denominator;
}
Fraction Fraction::operator+(Fraction other_one)
{
    Fraction result = Fraction();
    result.numerator = this->numerator * other_one.denominator + this->denominator * other_one.numerator;
    result.denominator = this->denominator * other_one.denominator;
    result.reduce_fraction();
    return result;
}
Fraction Fraction::operator-(Fraction other_one)
{
    Fraction result = Fraction();
    result.numerator = this->numerator * other_one.denominator - this->denominator * other_one.numerator;
    result.denominator = this->denominator * other_one.denominator;
    result.reduce_fraction();
    return result;
}
Fraction Fraction::operator*(Fraction other_one)
{
    Fraction result = Fraction();
    result.numerator = numerator * other_one.numerator;
    result.denominator = denominator * other_one.denominator;
    result.reduce_fraction();
    return result;
}
Fraction Fraction::operator/(Fraction other_one)
{
    Fraction result = Fraction();
    result.numerator = numerator * other_one.denominator;
    result.denominator = denominator * other_one.numerator;
    result.reduce_fraction();
    return result;
}
bool Fraction::operator<(Fraction other_one)
{
    return ((this->get_numerator*other_one.get_denominator) < (this->get_denominator * other_one.get_numerator));
}

ostream & operator<<(ostream &output,Fraction fraction)
{
    if(fraction.get_numerator() == fraction.get_denominator()) cout<< 1;
    else cout<<fraction.get_numerator() << "/" << fraction.get_denominator();
    return output;
}

void Fraction::reduce_fraction()
{
    int gcd = GCD(numerator,denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}



int main()
{
    Fraction    ulamek(2,5),
                ulamek2(3,5);

    cout << ulamek-ulamek2;


    return 0;
}
