#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

typedef struct{
    int x;
    int y;
}pivot;

float A[25][25],B[25][25];
int k, l, target;

pivot* find_resolving_elem_index();
void simplex_method();
void print(float a[25][25], pivot *coord);

int main(){
    /*параметры:p-количество переменных
                target - min or max
                usl - количество условий
                k - строки матрицы
                l - столбцы матрицы
                i,j - для циклов
                A - матрица для исходного примера
                razr - разрешающий элемент
                minimum - минимальный элемент в строке
    */

    int p, usl, flag;
    cout << "Нужно найти максимум или минимум? (1/0) ";
    cin >> target;
    cout << "Введите количество переменных: ";
    cin >> p;
    cout << "Теперь введите количество условий: ";
    cin >> usl;

    k = usl + 1;//добавили строку для L
    l = p + 1;//добавили столбец для свободных членов

    cout << "Введите свободные члены\n";
    for(int i = 0; i < k; i++)
         cin >> A[i][0];
    cout << "Введите коэфиценты (построчно, через пробел)\n";
    for(int i = 0; i < k; i++)
         for(int j = 1; j < l; j++)
            cin >> A[i][j];

    //менем знаки для целевой функции
    int count = 0;
    for(int j = 1; j < l; j++){
        if(A[0][j] != 0)
            A[0][j] = -1 * A[0][j];
        if(A[0][j] == 0)
            count++;
    }
    if(count == l-1){
        cout << "Решений нет, т.к. целевая функция отсутствует\n";
        exit(0);
    }

    //менем знак коэфф если больше или равно нулю
    for(int i = 1; i < k; i++){
        cout << i << "-е условие больше или меньше? (1/0) ";
        cin >> flag;
        for(int j = 1; j < l; j++)
            if((flag == 1) && (A[i][j] != 0))
                A[i][j] = -1 * A[i][j];
        if((flag == 0) && (A[i][0] != 0))
                A[i][0] = -1 * A[i][0];
    }

    simplex_method();
    return 0;
}

void print(float a[25][25], pivot *coord){
    for(int i =0 ; i < k; i++){
        for(int j = 0; j < l; j++){
            if(i == coord->x && j == coord->y && i != 0 && j != 0){
                cout << fixed;
                cout.precision(2);
                cout << "\033[31m" << setw(5) << A[i][j] << "\033[37m" << " ";
                continue;
            }
            cout << fixed;
            cout.precision(2);
            cout << setw(5) << a[i][j] << " ";
        }
        cout << endl;
    }
}

//проверка на существование опорного решения
//поиск разрешающего элемента
pivot* find_resolving_elem_index(int type){
    float razr, minimum;
    pivot* coord = new pivot;
    minimum = 0;
    if(type == 0){
        for(int i = 0; i < k; i++){
            if((A[i][0] < 0) && (i != 0)){
                for(int j=0;j<l;j++){
                    if((A[i][j] < 0) && (j != 0)){
                        for(int m = 0; m < k; m++){
                            if((A[m][j] != 0) && (m != 0)){
                                razr = A[m][0] / A[m][j];
                                if(razr > 0){
                                if((minimum == 0) || (razr < minimum)){
                                    minimum  = razr;
                                    coord->x = m;
                                    coord->y = j;
                                }
                            }
                        }

                    }
                    if ((coord->x != 0) && (coord->y != 0)){
                        return coord;
                    }
                    else {
                        cout << "Система уравнений не совместима с "
                                "неравенствами, вытекающими из неотрицательности "
                                "переменных. Решений нет\n";
                        exit(0);
                    }
                    }
                }
            }
        }
    }
    if(type == 1){
        for(int j=0; j<l; j++){
            if((A[0][j] > 0) && (j != 0)){
                for(int i = 0; i < k; i++){
                    if((A[i][j] > 0) && (i != 0)){
                        if(A[i][j] > 0){
                            razr = A[i][0] / A[i][j];
                            if((minimum == 0) || (razr < minimum)){
                                minimum  = razr;
                                coord->x = i;
                                coord->y = j;
                            }
                        }
                    }
                }
                if ((coord->x != 0) && (coord->y != 0))
                    return coord;
                else {
                    cout << "Целевая функция неограниченно уменьшается "
                            "при любых наборах базисных переменных. "
                            "Оптимального решения нет\n";
                    exit(0);
                }
            }
        }
    }
    if(type == 2){
        for(int j = 0; j < l; j++){
            if((A[0][j] < 0) && (j != 0)){
                for(int i = 0; i < k; i++){
                    if((A[i][j] > 0) && (i != 0)){
                        if (A[i][j] > 0){
                            razr = A[i][0] / A[i][j];
                            if((minimum == 0) || (razr < minimum)){
                                minimum  = razr;
                                coord->x = i;
                                coord->y = j;
                            }
                        }
                    }
                }
                if ((coord->x != 0) && (coord->y != 0))
                    return coord;
                else {
                    cout << "Целевая функция неограниченно увеличивается "
                            "при любых наборах базисных переменных. "
                            "Оптимального решения нет\n";
                    exit(0);
                }
            }
        }
    }
    coord->x = 0;
    coord->y = 0;
    return coord;
}

string change_basis(pivot *coord){
    for(int i = 0; i < k; i++)
        for(int j = 0; j < l; j++){
            if((i != coord->x) && (j != coord->y))
                B[i][j] = A[coord->x][j] * (A[i][coord->y] *
                        (-1) / A[coord->x][coord->y]);
            if(i == coord->x)
                B[i][j] = A[i][j] * (1 /A[coord->x][coord->y]);
            if(j == coord->y)
                B[i][j] = A[i][j] * (-1) /A[coord->x][coord->y];
            if((i == coord->x) && (j == coord->y))
                B[i][j] = 1 / A[coord->x][coord->y];
        }
    for(int i = 0; i < k; i++)
        for(int j = 0; j < l; j++){
            if((i != coord->x) || (j != coord->y))
                A[i][j] = A[i][j] + B[i][j];
            if((i == coord->x)||(j == coord->y))
                A[i][j] = B[i][j];
        }
    return "y" + to_string(coord->x) + "<->" + "x" + to_string(coord->y);
}

void simplex_method(){
    pivot* coord = find_resolving_elem_index(0);
    cout << "Исходная таблица" << endl;
    print(A, coord);
    int step = 1;
    while((coord->x != 0) && (coord->y != 0)){
        string message(change_basis(coord));
        cout<<"Шаг: "<< step << endl;
        coord = find_resolving_elem_index(0);
        cout << "Вспомогательная таблица: " << endl;
        print(B, coord);
        cout << message << " Результат: " << endl;
        print(A, coord);
        step++;
    }

    cout<<"Опорное решение найдено"<<endl;

    if(target == 0){
        coord = find_resolving_elem_index(1);
        cout<<"Найдем оптимальное решение, если есть" << endl;
        cout<<"Таблица:"<<endl;
        print(A, coord);
        while((coord->x != 0) && (coord->y != 0)){
            string message(change_basis(coord));
            cout<<"Шаг: "<< step << endl;
            coord = find_resolving_elem_index(1);
            cout << "Вспомогательная таблица: " << endl;
            print(B, coord);
            cout << message << " Результат: " << endl;
            print(A, coord);
            step++;
        }
    }
    if(target == 1){
        coord = find_resolving_elem_index(2);
        cout<<"Найдем оптимальное решение, если есть" << endl;
        cout<<"Таблица:"<<endl;
        print(A, coord);
        while((coord->x != 0) && (coord->y != 0)){
            string message(change_basis(coord));
            cout<<"Шаг: "<< step << endl;
            coord = find_resolving_elem_index(2);
            cout << "Вспомогательная таблица: " << endl;
            print(B, coord);
            cout << message << " Результат: " << endl;
            print(A, coord);
            step++;
        }
    }
    cout << "Оптимальное решение найдено:" << endl;
    if(target == 0)
        cout << "L\u2098\u2097\u2099 = " << A[0][0] << endl;
    if(target == 1)
        cout << "L\u2098\u2090\u2093 = " << A[0][0] << endl;
}
