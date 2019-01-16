#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
        return abs(a);
    else
        return gcd(abs(b), abs(a % b));
}
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

template <typename T>
class Matrix
{
  protected:
    int rows,
        columns;
    vector<vector<T> > fields;

  public:
    Matrix(){};
    Matrix(int, int);
    void interchange_rows(int, int);
    void interchange_cols(int, int);
    void multiply_row(int, int);
    void divide_row(int, int);
    void add_row_a_to_row_b(int, int, int);
    void transpose();
    void increment();
    void decrement();

    friend istream &operator>>(istream &input, Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.columns; j++)
            {
                cin >> matrix.fields[i][j];
            }
        }
        return input;
    }
    friend ostream &operator<<(ostream &output, const Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.columns; j++)
            {
                cout << matrix.fields[i][j] << " ";
            }
            cout << endl;
        }
        return output;
    }
};
template <typename T>
Matrix<T>::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    fields = vector<vector<T> >(rows, vector<T>(columns));
}
template <typename T>
void Matrix<T>::interchange_rows(int row_a, int row_b)
{
    row_a--;
    row_b--;
    swap(fields[row_a], fields[row_b]);
}
template <typename T>
void Matrix<T>::interchange_cols(int col_a, int col_b)
{
    col_a--;
    col_b--;
    for (int i = 0; i < fields.size(); i++)
    {
        swap(fields[i][col_a], fields[i][col_b]);
    }
}
template <typename T>
void Matrix<T>::multiply_row(int row_num, int scalar)
{
    row_num--;
    for (int i = 0; i < columns; i++)
    {
        fields[row_num][i] = scalar * fields[row_num][i];
    }
}
template <typename T>
void Matrix<T>::divide_row(int row_num, int scalar)
{
    row_num--;
    for (int i = 0; i < columns; i++)
    {
        fields[row_num][i] = fields[row_num][i] / scalar;
    }
}
template <typename T>
void Matrix<T>::add_row_a_to_row_b(int row_a, int row_b, int scalar)
{
    row_a--;
    row_b--;
    for (int i = 0; i < columns; i++)
    {
        fields[row_b][i] += scalar * fields[row_a][i];
    }
}

template <typename T>
void Matrix<T>::transpose()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < columns; j++)
        {
            swap(fields[i][j], fields[j][i]);
        }
    }
}
template <typename T>
void Matrix<T>::increment()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            fields[i][j] = (fields[i][j] + 1) % 10;
        }
    }
}
template <typename T>
void Matrix<T>::decrement()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            fields[i][j] = (fields[i][j] - 1);
            if (fields[i][j] < 0)
                fields[i][j] += 10;
        }
    }
}

template <typename T>
class Square_matrix : public Matrix<T>
{
  private:
    int index_of_max_in_column_starting_from_row(int, int);

  public:
    Square_matrix(){};
    Square_matrix(int);
    long int determinant();
};

template <typename T>
Square_matrix<T>::Square_matrix(int size_of_matrix)
{
    this->rows = size_of_matrix;
    this->columns = size_of_matrix;
    this->fields = vector<vector<T> >(size_of_matrix, vector<T>(size_of_matrix));
}

template <typename T>
int Square_matrix<T>::index_of_max_in_column_starting_from_row(int col_num, int row_num)
{
    int result = col_num;
    for (int i = col_num; i < this->rows; i++)
    {
        if (this->fields[i][col_num] > this->fields[result][col_num])
        {
            result = i;
        }
    }
    return result;
}

template <typename T>
long int Square_matrix<T>::determinant()
{
    long int determinant = 1;
    int max_1, max_2;

    for (int col_num = 0; col_num < this->columns - 1; col_num++)
    {
        // changing row so that values in this column are >=0
        for (int i = col_num; i < this->rows; i++)
        {
            if (this->fields[i][col_num] < 0)
            {
                determinant *= -1;
                this->multiply_row(i + 1, -1);
            }
        }

        // looking for max and second max
        max_1 = index_of_max_in_column_starting_from_row(col_num, col_num);
        if (max_1 == this->rows - 1)
        {
            max_2 = max_1 - 1;
        }
        else
        {
            max_2 = this->rows - 1;
        }
        for (int i = col_num; i < this->rows; i++)
        {
            if (this->fields[i][col_num] > this->fields[max_2][col_num] && this->fields[i][col_num] <= this->fields[max_1][col_num] && i != max_1)
            {
                max_2 = i;
            }
        }

        while (this->fields[max_2][col_num] != 0)
        {
            this->add_row_a_to_row_b(max_2 + 1, max_1 + 1, -1);

            // look for max values again
            max_1 = index_of_max_in_column_starting_from_row(col_num, col_num);
            // looking for max and second max
            if (max_1 == this->rows - 1)
            {
                max_2 = max_1 - 1;
            }
            else
            {
                max_2 = this->rows - 1;
            }
            for (int i = col_num; i < this->rows; i++)
            {
                if (this->fields[i][col_num] > this->fields[max_2][col_num] && this->fields[i][col_num] <= this->fields[max_1][col_num] && i != max_1)
                {
                    max_2 = i;
                }
            }
        }
        if(max_1 != col_num)
        {
            this->interchange_rows(max_1 + 1, col_num + 1);
            determinant *= -1;
        }
    }

    for (int i = 0; i < this->rows; i++)
    {
        determinant *= this->fields[i][i];
    }
    return determinant;
}

int main()
{
    int size_of_matrix;
    cin >> size_of_matrix;
    while (size_of_matrix > 0)
    {
        Square_matrix<int> matrix(size_of_matrix);
        cin >> matrix;

        cout <<matrix.determinant() << endl;

        cin >> size_of_matrix;
    }
    if (size_of_matrix == 0)
    {
        cout << "*"<<endl;
    }
    return 0;
}

