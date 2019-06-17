#include "address_write.hpp"
#include <algorithm>
#include <string>
#include <iterator>

int main(){
	int create_count;
	cout << "Введите количество объектов" << endl;
	cin >> create_count;
	address_write *ad = new address_write[create_count];
	for (int i = 0; i < create_count; i++)
        cin >> ad[i];
    ad->save_stream(create_count);

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
		cout << "Размер файла example_stream.txt до добавления объектов: " << size << endl
			 << "Количество объектов в данном файле до добавления: " << obj_count << endl;
	} else {
		cout << "Проблемы при открытии файла example_stream.txt для подсчета строк. Выход..." << endl;
		exit(EXIT_FAILURE);	
	}
	file.close();

    ad->save_write(create_count);
	file.open("example_write.txt");
	if(file){
		file.seekg (0,file.end);
		long size = file.tellg();
		file.seekg (0);
		file.unsetf(std::ios_base::skipws);
		int obj_count = count(
			istream_iterator<char>(file),
			istream_iterator<char>(), 
			'\n')/3;
		cout << "Размер файла example_write.txt: " << size << endl
			 << "Количество объектов в данном файле после добавления: " << obj_count << endl;
	} else {
		cout << "Проблемы при открытии файла example_write.txt для подсчета строк. Выход..." << endl;
		exit(EXIT_FAILURE);	
	}	
	file.close();
	return 0; 
}
