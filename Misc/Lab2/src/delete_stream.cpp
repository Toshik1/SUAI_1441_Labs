#include "delete_stream.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

int delete_stream::find(int field, int count){
	int number = 0;
	ifstream file;
    file.open("example_stream.txt");
	if(file){
		for(int i = 0; i < count; i++){
		    for(int j = 0; j < 3; j++){
		        string str;
		        getline(file, str);
		        if(str.find("Имя") != string::npos){
		            str.erase(str.begin(), str.begin()+strlen("Имя: "));
		            strcpy(this[i].name, str.c_str());
		        } else if(str.find("Улица") != string::npos){
		            str.erase(str.begin(), str.begin()+strlen("Улица: "));
		            strcpy(this[i].street, str.c_str());
		        } else if (str.find("Номер") != string::npos){
		            str.erase(str.begin(), str.begin()+strlen("Номер дома: "));
			        this[i].building = atoi(str.c_str());
			    } else { break; }
			}
	    }
	} else {
		cout << "Проблема при открытии файла для поиска. Выход..." << endl;
		exit(EXIT_FAILURE);
	}
    switch(field){
        case 1:
            char buffer[1024];
            cout << "Введите имя, которое вы хотите найти:" << endl;
            cin >> buffer;
            for (int i = 0; i < count; i++){
                if(/*strcmp(buffer, this[i].name)*/string(this[i].name).compare(buffer) == 0){
                    number = i;
                }
            }
        break;
        case 2:
            cout << "Введите улицу, которую вы хотите найти:" << endl;
            cin >> buffer;
            for (int i = 0; i < count; i++){
                if(/*strcmp(buffer, this[i].street)*/string(this[i].street).compare(buffer) == 0){
                    number = i;
                }
            }
        break;
        case 3:
            int buf;
            cout << "Введите номер дома, который вы хотите найти:" << endl;
            cin >> buf;
            for (int i = 0; i < count; i++){
                if(buf == this[i].building){
                    number = i;
                }
            }
        break;
        /*default:
            cout << "Поле не выбрано, пока." << endl;
            exit(EXIT_FAILURE);*/
    }
	//cout << number << endl; exit(0);
    return number;
}

void delete_stream::del(fstream &file, int number, int count){
    if(file){
		vector<string>Delete;
		string str;
		while(getline(file, str))
			Delete.push_back(str);
		Delete.erase(Delete.begin() + number * 3);
		Delete.erase(Delete.begin() + number * 3);
		Delete.erase(Delete.begin() + number * 3);
		count = Delete.size();
		ofstream out;
		out.open("example_stream.txt");
		for(int i = 0; i < count; i++)
			out << Delete[i] << endl;
		out.close();
    } else {
		cout << "Проблемы с файлом во время удаления. Выход..." << endl;
		exit(EXIT_FAILURE);
	}
}
