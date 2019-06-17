#include "address_open.h"

void address_open::open_stream(int count){
    ifstream file;
    file.open("example_stream.txt");
    if(file.good()){
		file.seekg (0,file.end);
        long size = file.tellg();
        file.seekg (0);
		cout << "Размер файла example_stream.txt при открытии: " << size << endl << "Количество объектов в файле: " << count << endl;
        for(int i = 0; i < count; i++){
            file >> this[i];
        }
    } else {
        cout << "File wasn't open. Exit..." << endl;
        exit(EXIT_FAILURE);
    }
    file.close();
}

void address_open::open_read(int count){
    fstream file;
    file.open("example_write.txt", fstream::in);
    if(file){
		file.seekg (0,file.end);
        long size = file.tellg();
        file.seekg (0);
		cout << "Размер файла example_write.txt при открытии: " << size << endl << "Количество объектов в файле: " << count << endl;
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
        cout << "File wasn't open. Exit..." << endl;
        exit(EXIT_FAILURE);
    }
    file.close();
}

ostream &operator<<(ostream &out, address_open &obj){
    out << "Имя: " << address_open::width_align << obj.name 
		<< "\nУлица: " << address_open::width_align << obj.street 
		<< "\nНомер дома: " << address_open::width_align << obj.building << endl;
    return out;
}

ifstream &operator>>(ifstream &in, address_open &obj){
    for(int i = 0; i < 3; i++){
        string str;
        getline(in, str);
        if(str.find("Имя") != string::npos){
            str.erase(str.begin(), str.begin()+strlen("Имя: "));
            strcpy(obj.name, str.c_str());
        } else if(str.find("Улица") != string::npos){
            str.erase(str.begin(), str.begin()+strlen("Улица: "));
            strcpy(obj.street, str.c_str());
        } else if (str.find("Номер") != string::npos){
            str.erase(str.begin(), str.begin()+strlen("Номер дома: "));
            obj.building = atoi(str.c_str());
        } else { break; }
    }
    return in;
}
