#include <iostream>
#include <iomanip>
#include <cassert>
#include <ctime>

using namespace std;

class Matrix{
private:
    int size_;
    int **array;
    static int determ(int** matrix, int size);
public:
    Matrix ();
    Matrix (int size);
    Matrix (int size, int value);
    Matrix(const Matrix &obj);
    ~Matrix ();

    int get(int row, int column);
    int getSize() const;
    void set(int row, int column, int data);

    int rowSum(int row);
    int columnSum(int column);

    Matrix& operator =(const Matrix& obj);
    Matrix& operator +(const Matrix& obj);
    Matrix& operator -(const Matrix& obj);
    Matrix& operator *(const Matrix& obj);

    friend int operator * (const Matrix& l, const Matrix& r);
    friend Matrix operator *(int l, const Matrix& r);
    friend Matrix operator *(const Matrix& l, int r);
    friend ostream& operator << (ostream& out, const Matrix& obj);
    friend istream& operator >> (istream& in, const Matrix& obj);

    void turn();
    void turnClockWise(int n);

    struct MatrixRow {
            explicit MatrixRow(int* array, int size);
            int& operator[](int ix);
        private:
            int* array;
            int size_;
        };
    MatrixRow operator[](int iy);
    int determ();
};

Matrix &specialFill(Matrix &matrix){ // специальное заполнение матрицы
    for(int i = 0; i < matrix.getSize(); ++i)
        for(int j = 0; j < matrix.getSize(); ++j)
            (i!=j) ? matrix.set(i, j, i + 1 + j +1 ) : matrix.set(i, j , 0);
    for(int i = 0; i < matrix.getSize(); ++i)
        matrix.set(i, i, matrix.columnSum(i) + matrix.rowSum(i));
    return matrix;
}

int main(){
    srand(clock());
    int size, n;
    cout << "Enter size and n for turn" << endl;
    cin >> size;// >> n;
    Matrix B(size), A(size), C(size);
    for (int i = 0; i < A.getSize(); ++i)
        for (int j = 0; j < A.getSize(); ++j)
            A[i][j] = 1+rand()%10;
    specialFill(B);
    //cout << "Determinant B = " << B.determ() << endl;
    //cout << B << endl;
    //cout << A << endl;
    C = A * B;
    //cout << C << endl;
    //B.turnClockWise(n);
    //cout << B << endl;
    return 0;
}

Matrix::Matrix() : size_(0), array(0) {} // конструктор по умолчанию

Matrix::Matrix(int size) : size_(size), array(new int *[size_]()) {for(int i = 0;i < size_; ++i)array[i] = new int[size_];} // с одним пар

Matrix::Matrix(int size, int data) : size_(size), array(new int *[size_]()) { // с двумя параметрами
    for(int i = 0;i < size_; ++i)
        array[i] = new int[size_];
    for(int i = 0; i < size_; ++i)
        for(int j = 0; j < size_; ++j)
            array[i][j] = data;
}

int Matrix::getSize() const{return size_;} // возврат размера

int Matrix::get(int row, int column){return array[row][column];} // возврат значения ячейки

void Matrix::set(int row, int column, int value){array[row][column] = value;} // изменение ячейки

Matrix::Matrix(const Matrix &obj) : array(new int *[size_]()){ // конструктор копирования
    for(int i = 0; i < obj.getSize(); ++i)
        array[i] = new int[obj.getSize()];
    for(int i = 0; i < obj.getSize(); ++i)
        for(int j = 0; j < obj.getSize(); ++j)
              array[i][j]=obj.array[i][j];
}

Matrix::~Matrix(){ // деструктор
    for(int i = 0; i < getSize(); ++i)
            delete []array[i];
    delete []array;
}

int Matrix::rowSum(int row){ // сумма в строке
    int result = 0;
    for(int i = 0; i < getSize(); ++i)
        result += get(row, i);
    return result;
}
int Matrix::columnSum(int column){ // сумма в столбце
    int result = 0;
    for(int i = 0; i < getSize(); ++i)
        result += get(i, column);
    return result;
}

void Matrix::turn(){ // поворот на 90 градусов
    int povmas[getSize()][getSize()];
    for(int i = 0; i < getSize(); ++i)
        for(int j = 0; j < getSize(); ++j)
            povmas[i][j] = array[i][j];
    for(int i = 0; i < getSize(); ++i)
        for(int j = 0; j < getSize(); ++j)
            array[j][getSize()-1-i] = povmas[i][j];
}

void Matrix::turnClockWise(int n){ // поворот на n*90
    for(int i = 0; i < n % 4; ++i)
        turn();
}

Matrix operator *(int left, const Matrix& right){ // умножение на число
    Matrix temp(right.getSize());
    for(int i = 0; i < right.getSize(); ++i)
        for(int j = 0; j < right.getSize(); ++j)
            temp.array[i][j] = left * right.array[i][j];
    return temp;
}

Matrix operator *(const Matrix& left, int right){ // умножение на число
    return right * left;
}

Matrix& Matrix::operator =(const Matrix& obj){ // оператор присваивания
    assert(size_ == obj.size_);
    for(int i = 0; i < getSize(); ++i)
        for(int j = 0; j < getSize(); ++j)
        array[i][j] = obj.array[i][j];
    return *this;
}

Matrix& Matrix::operator +(const Matrix& obj){ // оператор сложения
    assert(size_ == obj.size_);
    static Matrix temp(getSize());
    for(int i = 0; i < getSize(); ++i)
      for(int j = 0; j < getSize(); ++j)
        temp.array[i][j] = array[i][j] + obj.array[i][j];
    return temp;
}

Matrix& Matrix::operator -(const Matrix& obj){ // оператор вычитания
    assert(size_ == obj.size_);
    static Matrix temp(getSize());
    for(int i = 0; i < getSize(); ++i)
      for(int j = 0; j < getSize(); ++j)
        temp.array[i][j] = array[i][j] - obj.array[i][j];
    return temp;
}

Matrix& Matrix::operator *(const Matrix& obj){ // оператор умножения матриц
    assert(size_ == obj.size_);
    static Matrix temp(getSize(), 0);
    for(int i = 0; i < getSize(); ++i)
        for(int j = 0; j < getSize(); ++j)
             for(int k = 0; k < getSize(); ++k)
                temp.array[i][j] += array[i][k] * obj.array[k][j];
    return temp;
}

std::ostream& operator << (std::ostream& out, const Matrix& obj){ // оператор вывода
    if (obj.array == NULL)
        cout << "Empty" << endl;
    else {
        for(int i = 0; i < obj.getSize(); ++i) {
            for(int j = 0; j < obj.getSize(); ++j){
                out.width(5);
                out << obj.array[i][j];
            }
            out << endl;
        }
    }
    return out;
}

Matrix::MatrixRow::MatrixRow(int* row, int size) : array(row), size_(size) {}

int& Matrix::MatrixRow::operator[](int ix){return array[ix];}

Matrix::MatrixRow Matrix::operator[](int iy){return MatrixRow(array[iy], size_);}

int Matrix::determ(){ return determ(array,size_);}

int Matrix::determ(int** matrix, int size) {
    if(size == 1) return matrix[0][0];
    if(size == 2) return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    int d = 0, k = 1;
    int** p = new int*[size-1];
    int j;
    for(int i = 0; i < size; i++) {
        for(j = 0; j < size-1; j++)
            p[j] = (j<i) ? matrix[j] : matrix[j+1];
        k = ((i+j) % 2) ? -1 : 1;
        d += k * determ(p, size-1) * matrix[i][size-1];
    }
    delete[] p;
    return d;
}
