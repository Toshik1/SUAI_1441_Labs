#ifndef DELETE_STREAM_H
#define DELETE_STREAM_H

#include "address_write.h"

class delete_stream : protected address_write
{
public:
	int find(int field, int count);
    void del(fstream &file, int number, int count);
};

#endif // DELETE_STREAM_H
