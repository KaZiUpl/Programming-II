#include <iostream>
using namespace std;

template <int p>
class Z
{
  private:
    int value;

  public:
    Z<p>();
    Z<p>(int);

    Z<p> operator+(Z<p>);
    Z<p> operator-(Z<p>);
    Z<p> operator*(Z<p>);
    Z<p> operator/(Z<p>);

    bool operator==(Z<p>);
    bool operator!=(Z<p>);
    bool operator>(Z<p>);
    bool operator>=(Z<p>);
    bool operator<(Z<p>);
    bool operator<=(Z<p>);

    Z<p> inverse_element();

    friend ostream &operator<<(ostream &output, const Z<p> &s)
    {
        output << s.value;
        return output;
    }
};
template <int p>
Z<p>::Z()
{
    value = 0;
}
template <int p>
Z<p>::Z(int starting_value)
{
    if (starting_value % p < 0)
    {
        value = starting_value % p + p;
    }
    else
    {
        value = starting_value % p;
    }
}

template <int p>
Z<p> Z<p>::operator+(Z<p> other_one)
{
    return Z<p>(value + other_one.value);
}
template <int p>
Z<p> Z<p>::operator-(Z<p> other_one)
{
    return Z<p>(value - other_one.value);
}
template <int p>
Z<p> Z<p>::operator*(Z<p> other_one)
{
    cout<<"mnoze "<<value <<" i "<<other_one.value<<"\twynik:"<<value * other_one.value<<endl;
    return Z<p>(value * other_one.value);
}
template <int p>
Z<p> Z<p>::operator/(Z<p> other_one)
{
    other_one = other_one.inverse_element();

    return Z<p>(value*other_one.value);
}

template <int p>
bool Z<p>::operator==(Z<p> other_one)
{
    return value == other_one.value;
}
template <int p>
bool Z<p>::operator!=(Z<p> other_one)
{
    return value != other_one.value;
}
template <int p>
bool Z<p>::operator<(Z<p> other_one)
{
    return value < other_one.value;
}
template <int p>
bool Z<p>::operator<=(Z<p> other_one)
{
    return value <= other_one.value;
}
template <int p>
bool Z<p>::operator>(Z<p> other_one)
{
    return value > other_one.value;
}
template <int p>
bool Z<p>::operator>=(Z<p> other_one)
{
    return value >= other_one.value;
}

template <int p>
Z<p> Z<p>::inverse_element()
{
    int temp[5] = {1, value, 0, p, 0};
    while (temp[1])
    {
        if (temp[1] < temp[3])
        {
            swap(temp[0], temp[2]);
            swap(temp[1], temp[3]);
        }

        temp[4] = temp[1] / temp[3];

        temp[0] -= temp[4] * temp[2];

        temp[1] -= temp[4] * temp[3];
    }
    return Z<p>(temp[2]);
}

int main()
{
    Z<23> a(6),b(3);
    cout<<a<<endl;
    cout << a/b;

    return 0;
}
