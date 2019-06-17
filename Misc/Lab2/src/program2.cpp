#include "address_open.h"
#include <algorithm>
#include <string>
#include <iterator>

int main(){
	ifstream file_stream;
    file_stream.open("example_stream.txt");
	if(!file_stream){
		cout << "Проблема при открытии файла example_stream.txt. Выход..." << endl;
		exit(EXIT_FAILURE);
	}
	file_stream.unsetf(std::ios_base::skipws);
	int obj_count = count(
        istream_iterator<char>(file_stream),
        istream_iterator<char>(), 
        '\n')/3;
	address_open *ad = new address_open[obj_count];
    ad->open_stream(obj_count);
    for(int i = 0; i < obj_count; i++){
        cout << ad[i];
    }
	file_stream.close();

	ifstream file_write;
	file_write.open("example_write.txt");
	if(!file_write){
		cout << "Проблема при открытии файла example_write.txt. Выход..." << endl;
		exit(EXIT_FAILURE);
	}
    file_write.unsetf(std::ios_base::skipws);
	obj_count = count(
        istream_iterator<char>(file_write),
        istream_iterator<char>(), 
        '\n')/3;
	address_open *add = new address_open[obj_count];
	add->open_read(obj_count);
	for(int i = 0; i < obj_count; i++)
		cout << add[i];
	file_write.close();
	return 0;
}
