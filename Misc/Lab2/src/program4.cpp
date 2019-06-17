#include "delete_stream.h"
#include <algorithm>
#include <string>
#include <iterator>

int main(){
	cout << "1 - Поиск по имени\n"
            "2 - Поиск по улице\n"
            "3 - Поиск по номеру дома\n";
    int field;
    cin >> field;
    ifstream file;
    file.open("example_stream.txt");
	if(file){
		file.seekg (0,file.end);
		long size = file.tellg();
		file.seekg (0);
		file.unsetf(std::ios_base::skipws);
		int obj_count = count(
			istream_iterator<char>(file),
			istream_iterator<char>(), 
			'\n')/3;
		cout << "Размер файла example_stream.txt во время изменения: " << size << endl
			 << "Количество объектов в данном файле : " << obj_count << endl;
		file.close();
		fstream in_out;
		in_out.open("example_stream.txt", fstream::in);
		delete_stream *de = new delete_stream[obj_count];
		de->del(in_out, de->find(field, obj_count), obj_count);
		in_out.close();
	} else {
		cout << "Проблемы при открытии файла для подсчета строк. Выход..." << endl;
		exit(EXIT_FAILURE);	
	}
	
	return 0;
}
