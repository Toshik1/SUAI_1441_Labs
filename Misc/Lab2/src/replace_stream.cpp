#include "replace_stream.h"

int replace_stream::find(int field, int count){
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
    return number;
}

void replace_stream::repl(fstream &file, int number, int count){
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
        cout << "1 - Изменение имени\n"
                "2 - Изменение улицы\n"
                "3 - Изменение номера дома\n";
        int field;
        cin >> field;
        switch(field){
            case 1:
                cout << "Введите новое имя: " << endl;
                cin >> this[number].name;
            break;
            case 2:
                cout << "Введите новую улицу: " << endl;
                cin >> this[number].street;
            break;
            case 3:
                cout << "Введите новый номер дома: " << endl;
                cin >> this[number].building;
            break;
        }
    } else {
		cout << "Проблемы с файлом во время перезаписи. Выход..." << endl;
		exit(EXIT_FAILURE);
	}
    this->save_stream(count);
}
