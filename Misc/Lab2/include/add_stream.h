#ifndef ADD_STREAM_H
#define ADD_STREAM_H

#include "address.h"
#include <fstream>
#include <cstring>

class add_stream : protected address
{
public:
    void new_add(int add_count);

    friend istream &operator>>(istream &in, add_stream &obj);
};

#endif // ADD_STREAM_H
