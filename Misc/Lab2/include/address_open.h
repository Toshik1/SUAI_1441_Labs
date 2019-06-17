#ifndef ADDRESS_OPEN_H
#define ADDRESS_OPEN_H

#include "address.h"
#include <fstream>
#include <cstring>
#include <iomanip>

class address_open : public address
{
public:
    void open_stream(int count);
    void open_read(int count);

    static ostream &width_align(ostream &out){
        out << left << setw(62);
        return out;
    }

    friend ostream &operator<<(ostream &out, address_open &obj);
    friend ifstream &operator>>(ifstream &in, address_open &obj);
};

#endif // ADDRESS_OPEN_H

