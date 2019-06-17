#include "address_write.h"

void address_write::save_stream(int count){
    fstream file;
    file.open("example_stream.txt", fstream::out);
    if(file.bad()){
        cout << "Проблемы с файлом example_stream.txt при записи. Выход..." << endl;
        exit(EXIT_FAILURE);
    } else {
        for(int i = 0; i < count; i++)
            file << this[i];
    }
	file.close();
}

void address_write::save_write(int count){
    fstream file;
    file.open("example_write.txt",  fstream::out);
    if(!file){
        cout << "Проблемы с файлом example_write.txt при записи. Выход..." << endl;
        exit(EXIT_FAILURE);
    } else {
        for(int i = 0; i < count; i++){
            string buffer;
            buffer.append("Имя: ");
            buffer.append(this[i].name);
            buffer.append("\nУлица: ");
            buffer.append(this[i].street);
            buffer.append("\nНомер дома: ");
            buffer.append(to_string(this[i].building));
            buffer.append("\n");
            file.write(buffer.data(), buffer.length());
        }
	}
	file.close();
}

istream &operator>>(istream &in,  address_write &obj){
    in >> obj.name >> obj.street >> obj.building;
    return in;
}
