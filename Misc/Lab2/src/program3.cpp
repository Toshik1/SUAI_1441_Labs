#include "add_stream.h"
#include <algorithm>
#include <string>
#include <iterator>

int main(){
	cout << "Введите кол-во объектов, которое желаете добавить: " << endl;
    int add_count;
    cin >> add_count;

	ifstream file;
	file.open("example_stream.txt");
	if(file){
		file.seekg (0,file.end);
		long size_before = file.tellg();
		file.seekg (0);
		file.unsetf(std::ios_base::skipws);
		int obj_count = count(
			istream_iterator<char>(file),
			istream_iterator<char>(), 
			'\n')/3;
		cout << "Размер файла example_stream.txt до добавления объектов: " << size_before << endl
			 << "Количество объектов в данном файле до добавления: " << obj_count << endl;
	} else {
		cout << "Проблемы при открытии файла для подсчета строк. Выход..." << endl;
		exit(EXIT_FAILURE);	
	}
	file.close();
    
	add_stream *ad = new add_stream[add_count];
    for (int i = 0; i < add_count; i++)
        cin >> ad[i];
    ad->new_add(add_count);

	file.open("example_stream.txt");
	if(file){
		file.seekg (0,file.end);
		long size_after = file.tellg();
		file.seekg (0);
		file.unsetf(std::ios_base::skipws);
		int obj_new_count = count(
			istream_iterator<char>(file),
			istream_iterator<char>(), 
			'\n')/3;
		cout << "Размер файла example_stream.txt после добавления объектов: " << size_after << endl
			 << "Количество объектов в данном файле после добавления: " << obj_new_count << endl;
	} else {
		cout << "Проблемы при переоткрытии файла для подсчета строк после записи. Выход..." << endl;
		exit(EXIT_FAILURE);	
	}	
	file.close();
	return 0;
}
