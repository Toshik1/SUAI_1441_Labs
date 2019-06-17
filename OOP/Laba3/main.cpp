
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>

using namespace std;

class StrCount{
    private:
        char *s;
        int len;
        int count;
        friend class String;
    public:
        StrCount() : len(0), count(0), s(new char) {}
        StrCount(char* str);
        ~StrCount();
};

class String{
    private:
        StrCount *data;
    public:
        String();
        String(char *str);
        String(String& st);
        ~String();
        int length() const;
        int counter() const;
        void print();
        char* getData(){ return data->s; }
        void setLength(int n){ data->len = n; }
        void setData(char* ch){ strcpy(data->s,ch); }
        void addData(char* ch){ strcat(data->s,ch); }
        void setCount(){ data->count++; }
        String& operator=(const String&);
        friend String operator+(String& rhs, String& dhs){
            String r;
            r.setLength(rhs.length()+dhs.length());
            r.setData(rhs.getData());
            r.addData(dhs.getData());
            r.setCount();
            return r;
        }
        const char& operator[](int) const;
        char& operator[](int);
        bool operator==(String&);
        bool operator!=(String&);
        bool operator>(const String&) const;
        bool operator<(const String&) const;
        friend ostream& operator<<(ostream&, String&);
        friend istream& operator>>(istream&, String&);
};

StrCount::StrCount (char* str){
    len = strlen(str);
    s = new char[len+1];
    strcpy(s, str);
    count = 1;
}

StrCount::~StrCount(){
    delete[] s;
}

String::String(){
    data = new StrCount();
}

String::String(char* str){
    data = new StrCount(str);
}

String::String(String& st){
    data = st.data;
    (data->count)++;
}

String::~String(){
    if(data->count==1)
        delete data;
    else
        (data->count)--;
}

int String::length() const{
   return data->len;
}

int String::counter() const{
    return data->count;
}

String& String::operator = (const String& st){
    if(data->count==1)
        delete data;
    else
        (data->count)--;
        data = st.data;
        (data->count)++;
    return *this;
}

const char& String::operator[](int i) const{
    return (i >= 0 && i < data->len) ? this->data->s[i] : 0;
}

char& String::operator[](int i){
    static char ch = ' ';
    return (i >= 0 && i < data->len) ? this->data->s[i] : ch;
}

bool String::operator==(String &rhs ){
    return (strcmp(rhs.getData(),this->getData()) == 0) ? true : false;
}

bool String::operator!=(String& rhs){
    return (strcmp(rhs.getData(),this->getData()) == 0) ? false : true;
}

bool String::operator>(const String& rhs) const {
    return (data->len > rhs.data->len) ? true : false;
}

bool String::operator<(const String& rhs) const{
    return (data->len < rhs.data->len) ? true : false;
}

ostream& operator<<(ostream& os, String& obj){
    return os << obj.getData();
}

istream& operator>>(istream& is, String& obj){
    char BUFF[2048];
    is.getline(BUFF, sizeof BUFF);
    obj = BUFF;
    return is;
}

int main (){
    String per1,per2,per3;
    cout << "per1: "; cin >> per1;
    cout << "per2: "; cin >> per2;
    cout << endl << "per1 = per2? " << (per1 == per2) << endl;
    cout << "per1 > per2? " << (per1 > per2) << endl;
    per3 = per2 + per1;
    cout << endl << "s3 = s1 + s2: " << per3 << endl;
    cout << "\nper3 count = " << per3.counter() << endl;
    cout << "\nper2 count = " << per2.counter() << endl;
    cout << "\nper1 count = " << per1.counter() << endl;
    String per4;
    per4 = per2;
    cout << endl << "per4 = per2: " << per4 << endl;
    return 0;
}
