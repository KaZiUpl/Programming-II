#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>


using namespace std;

class Rational
{
private:
    long int numerator, denominator;
    static int GCD(long int a, long int b);
    void reduce();
public:
    Rational();
    Rational(long int numerator,long int denominator = 1);
    long int    get_numerator(),
                get_denominator();
    void        set_numerator(long int numerator),
                set_denominator(long int denominator);
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

    friend ostream &operator<<(ostream &output,const Rational &fraction);
    friend istream &operator>>(istream &input, Rational &fraction);
};

int Rational::GCD(long int a, long int b)
{
    if(b == 0) return abs(a);
    else       return GCD(abs(b), abs(a % b)) ;
}
void Rational::reduce()
{
    int gcd = GCD(numerator,denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
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
void Rational::set_numerator(long int numerator)
{
    this->numerator = numerator;
}
void Rational::set_denominator(long int denominator)
{
    this->denominator = denominator;
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
ostream & operator<<(ostream &output,const Rational &fraction)
{
    if(fraction.numerator == fraction.denominator) cout << 1;
    else if(fraction.denominator == 1) cout<<fraction.numerator;
    else cout<<fraction.numerator << "|" << fraction.denominator;
    return output;
}
istream & operator>>(istream &input, Rational &fraction)
{
    string input_string;
    int position_of_line;

    cin>>input_string;
    position_of_line = input_string.find("|");

    if(position_of_line == (int)string::npos)
    {
        fraction.numerator = strtol(input_string.c_str(),NULL,10);
    }
    else
    {
        string numerator,denominator;
        numerator = input_string.substr(0,position_of_line);
        denominator = input_string.substr(position_of_line+1,input_string.size()-position_of_line);
        fraction.numerator = strtol(numerator.c_str(),NULL,10);
        fraction.denominator = strtol(denominator.c_str(),NULL,10);
    }
    return input;
}

int main()
{

    return 0;
}
