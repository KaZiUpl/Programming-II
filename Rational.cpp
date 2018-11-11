#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class Rational
{
  private:
    long int numerator, denominator;
    static int GCD(long int, long int);
    void reduce();

  public:
    Rational();
    Rational(long int, long int = 1);
    long int get_numerator(),
        get_denominator();
    void set_numerator(long int),
        set_denominator(long int);
    void swap_num_denom();
    vector<int> return_continued_fraction();
    Rational raise_to_power(int);
    Rational operator+(Rational);
    Rational operator-(Rational);
    Rational operator-(int);
    Rational operator*(Rational);
    Rational operator/(Rational);
    bool operator<(Rational);
    bool operator>(Rational);
    bool operator<=(Rational);
    bool operator>=(Rational);
    bool operator==(Rational);
    bool operator!=(Rational);

    friend ostream &operator<<(ostream &, const Rational &);
    friend istream &operator>>(istream &, Rational &);
};

int Rational::GCD(long int a, long int b)
{
    if (b == 0)
        return abs(a);
    else
        return GCD(abs(b), abs(a % b));
}
void Rational::reduce()
{
    int gcd = GCD(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}

Rational::Rational()
{
    numerator = 0;
    denominator = 1;
}
Rational::Rational(long int numerator, long int denominator)
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
void Rational::swap_num_denom()
{
    long int help;
    help = this->numerator;
    this->numerator = this->denominator;
    this->denominator = help;
}
vector<int> Rational::return_continued_fraction()
{
    vector<int> continued_fraction;
    int div;
    Rational work_copy(this->numerator, this->denominator);

    div = work_copy.get_numerator() / work_copy.get_denominator();
    continued_fraction.push_back(div);
    work_copy = work_copy - div;
    if (work_copy.get_denominator() >= work_copy.get_numerator())
    {
        do
        {
            work_copy.swap_num_denom();
            div = work_copy.get_numerator() / work_copy.get_denominator();
            work_copy = work_copy - div;
            continued_fraction.push_back(div);
        } while (work_copy.get_denominator() >= work_copy.get_numerator() && work_copy.get_numerator() > 0);
    }
    return continued_fraction;
}
Rational Rational::raise_to_power(int power)
{
    Rational result = Rational();
    result.numerator = pow(this->numerator, power);
    result.denominator = pow(this->denominator, power);
    result.reduce();
    return result;
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
Rational Rational::operator-(int number)
{
    Rational result = Rational();
    result.numerator = this->numerator - number * this->denominator;
    result.denominator = this->denominator;
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
    return ((numerator * other_one.denominator) < (denominator * other_one.numerator));
}
bool Rational::operator>(Rational other_one)
{
    return ((numerator * other_one.denominator) > (denominator * other_one.numerator));
}
bool Rational::operator<=(Rational other_one)
{
    return ((numerator * other_one.denominator) <= (denominator * other_one.numerator));
}
bool Rational::operator>=(Rational other_one)
{
    return ((numerator * other_one.denominator) >= (denominator * other_one.numerator));
}
bool Rational::operator==(Rational other_one)
{
    return ((numerator * other_one.denominator) == (denominator * other_one.numerator));
}
bool Rational::operator!=(Rational other_one)
{
    return ((numerator * other_one.denominator) != (denominator * other_one.numerator));
}
// ------------------------------ KONIEC RATIONAL -------------------------------
ostream &operator<<(ostream &output, const Rational &fraction)
{
    if (fraction.numerator == fraction.denominator)
        cout << 1;
    else if (fraction.denominator == 1)
        cout << fraction.numerator;
    else
        cout << fraction.numerator << "|" << fraction.denominator;
    return output;
}
istream &operator>>(istream &input, Rational &fraction)
{
    string input_string;
    int position_of_line;

    cin >> input_string;
    position_of_line = input_string.find("|");

    if (position_of_line == (int)string::npos)
    {
        fraction.numerator = strtol(input_string.c_str(), NULL, 10);
    }
    else
    {
        string numerator, denominator;
        numerator = input_string.substr(0, position_of_line);
        denominator = input_string.substr(position_of_line + 1, input_string.size() - position_of_line);
        fraction.numerator = strtol(numerator.c_str(), NULL, 10);
        fraction.denominator = strtol(denominator.c_str(), NULL, 10);
        fraction.reduce();
    }
    return input;
}

int main()
{

    return 0;
}
