#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>

using namespace std;

class address{
protected:
    char    name[124];
    char    street[124];
    int     building;
public:
    address();
    address(char name[], char street[], int building);
    ~address();

    friend ostream &operator<<(ostream &out, const address &obj);
    friend istream &operator>>(istream &in, address &obj);
    address &operator=(const address &that);
};

#endif // ADDRESS_H
