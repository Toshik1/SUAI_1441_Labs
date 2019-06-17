#include "add_stream.h"

void add_stream::new_add(int add_count){
    fstream file;
    file.open("example_stream.txt", fstream::out | fstream::app);
    if(file){
	    for(int i = 0; i < add_count; i++){
            file << this[i];
        }
    } else {
		cout << "Проблемы при открытии файла для добавления. Выход..." << endl;
		exit(EXIT_FAILURE);	
	}	
	file.close();
}

istream &operator>>(istream &in,  add_stream &obj){
    in >> obj.name >> obj.street >> obj.building;
    return in;
}
