#ifndef REPLACE_STREAM_H
#define REPLACE_STREAM_H

#include "address_write.h"

class replace_stream : protected address_write
{
public:
	int find(int field, int count);
    void repl(fstream &file, int number, int count);
};

#endif // REPLACE_STREAM_H
