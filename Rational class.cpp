#include<iostream>
#include<cmath>

using namespace std;

class Rational
{
private:
    long int numerator, denominator;
    void reduce();
public:
    static int GCD(long int a, long int b);
    Rational();
    Rational(long int numerator,long int denominator);
    long int    get_numerator(),
                get_denominator();
    Rational operator+(Rational other_one);
    Rational operator-(Rational other_one);
    Rational operator*(Rational other_one);
    Rational operator/(Rational other_one);
    bool operator<(Rational other_one);
    bool operator>(Rational other_one);
    bool operator<=(Rational other_one);
    bool operator>=(Rational other_one);
    bool operator==(Rational other_one);
    bool operator!=(Rational other_one);
};

void Rational::reduce()
{
    int gcd = GCD(numerator,denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}

int Rational::GCD(long int a, long int b)
{
    if(b == 0) return abs(a);
    else       return GCD(abs(b), abs(a % b)) ;
}

Rational::Rational()
{
    numerator = 0;
    denominator = 1;
}
Rational::Rational(long int numerator,long int denominator)
{
    this->numerator = numerator;
    this->denominator = denominator;
}
long int Rational::get_numerator()
{
    return numerator;
}
long int Rational::get_denominator()
{
    return denominator;
}
Rational Rational::operator+(Rational other_one)
{
    Rational result = Rational();
    result.numerator = this->numerator * other_one.denominator + this->denominator * other_one.numerator;
    result.denominator = this->denominator * other_one.denominator;
    result.reduce();
    return result;
}
Rational Rational::operator-(Rational other_one)
{
    Rational result = Rational();
    result.numerator = this->numerator * other_one.denominator - this->denominator * other_one.numerator;
    result.denominator = this->denominator * other_one.denominator;
    result.reduce();
    return result;
}
Rational Rational::operator*(Rational other_one)
{
    Rational result = Rational();
    result.numerator = numerator * other_one.numerator;
    result.denominator = denominator * other_one.denominator;
    result.reduce();
    return result;
}
Rational Rational::operator/(Rational other_one)
{
    Rational result = Rational();
    result.numerator = numerator * other_one.denominator;
    result.denominator = denominator * other_one.numerator;
    result.reduce();
    return result;
}
bool Rational::operator<(Rational other_one)
{
    return ((this->get_numerator()*other_one.get_denominator()) < (this->get_denominator() * other_one.get_numerator()));
}
bool Rational::operator>(Rational other_one)
{
    return ((this->get_numerator()*other_one.get_denominator()) > (this->get_denominator() * other_one.get_numerator()));
}
bool Rational::operator<=(Rational other_one)
{
    return ((this->get_numerator()*other_one.get_denominator()) <= (this->get_denominator() * other_one.get_numerator()));
}
bool Rational::operator>=(Rational other_one)
{
    return ((this->get_numerator()*other_one.get_denominator()) >= (this->get_denominator() * other_one.get_numerator()));
}
bool Rational::operator==(Rational other_one)
{
    return ((this->get_numerator()*other_one.get_denominator()) == (this->get_denominator() * other_one.get_numerator()));
}
bool Rational::operator!=(Rational other_one)
{
    return ((this->get_numerator()*other_one.get_denominator()) != (this->get_denominator() * other_one.get_numerator()));
}
// ------------------------------ KONIEC RATIONAL -------------------------------
ostream & operator<<(ostream &output,Rational fraction)
{
    if(fraction.get_numerator() == fraction.get_denominator()) cout<< 1;
    else cout<<fraction.get_numerator() << "/" << fraction.get_denominator();
    return output;
}





int main()
{



    return 0;
}
