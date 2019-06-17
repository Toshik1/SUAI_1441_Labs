#ifndef CLASS_ADDRESS_H
#define CLASS_ADDRESS_H

#include <cstring>
#include <fstream>
#include "address.h"

using namespace std;

class address_write : protected address{
public:
    void save_stream(int count);
    void save_write(int count);

    friend istream &operator>>(istream &in, address_write &obj);
};

#endif // CLASS_ADDRESS_H
