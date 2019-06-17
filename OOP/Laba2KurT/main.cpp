#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

class Rational{
    int a;
    int b;
    int real;
public:
    Rational(){
        a = 0;
        b = 1;
        real = 0;
    }
    Rational(const int& _a, const int& _b){
        if(_b<0) exit(1);
        a = _a;
        if(_b)
            b = _b;
        else
            exit(1);
        real = 0;
        reduce();
    }
    Rational operator+(Rational T){
        Rational Temp;
        Temp.a = (real * b + a) * T.b + (T.real * T.b + T.a) * b;
        Temp.b = b * T.b;
        if (Temp.a < 0) Temp.a *= -1;
        Temp.reduce();
        return Temp;
    }
    Rational operator-(Rational T){
        Rational Temp;
        Temp.a = (real * b + a) * T.b - (T.real * T.b + T.a) * b;
        Temp.b = b * T.b;
        if (Temp.a < 0) Temp.a *= -1;
        Temp.reduce();
        return Temp;
    }
    Rational operator*(Rational T){
        return Rational(this->a * T.a, this->b * T.b);
    }
    Rational operator/(Rational T){
        return Rational(this->a * T.b, this->b * T.a);
    }
    void cancellation(){
        if(a == b){
            a = 1; b = 1;
        } else if(a != 0 && a != b) {
            int m = b, n = a, ost = m%n;
            if(a%b == 0){
                while(b!=1){
                    a=a/b;b=b/b;
                }
            } else {
            while(ost != 0){
                m = n; n = ost;
                ost = m % n;
            }
            int nod = n;
            a /= nod; b /= nod;}
        }
    }
    void GetIntPart(){
        if(a >= b){
            real += (a / b);
            a %= b;
        }
    }
    void reduce(){
        cancellation();
        GetIntPart();
    }

    friend ostream& operator<< (ostream &out,const Rational& drob){
        if((drob.b == 1 || drob.a == 0) && drob.real != 0)
            out << drob.a + drob.real;
        else if(drob.real != 0)
            out << drob.real << "+" << drob.a << '/' << drob.b;
        else out << drob.a << '/' << drob.b;
        return out;
    }

    friend istream& operator>> (istream& istr, Rational& b){
        char* str = new char [1024], *p;
        cin.getline(str, sizeof(str));
        p = strchr(str, '/');
        if (p){
            b.b = atoi(p+1);
            p = '\0';
            b.a = atoi(str);
        } else {
            b.a = atoi(str);
            b.b = 1;
        }
        b.reduce();
        return istr;
    }
    bool operator < (Rational& f) {
        return double(*this) <= double(f);
    }
    bool operator > (Rational& f) {
        return double(*this) >= double(f);
    }
    bool operator == (const Rational& f) const {
        return real == f.real && a * f.b == b * f.a;
    }
    bool operator != (const Rational& f) const{
        return real != f.real && a * f.b != b * f.a;
    }
    operator double(){
        return (double)(real*b+a)/b;
    }
};

int main(){
    Rational A(1,3);
    Rational B(1,8);
    Rational C,D;
    cout<<"Enter fraction C *a/b* : "; cin >> C; cout << endl;
    cout<<"Enter fraction D *a/b* : "; cin >> D; cout << endl;
    cout << A << " - " << B << " = " << A-B << endl;
    cout << C << " + " << D << " = " << C+D << endl;
    cout << A << " * " << B << " + " << C << " / " << D << " = " << A*B+C/D << endl;
    return 0;
}
