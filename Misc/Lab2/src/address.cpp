#include "address.h"
#include <cstring>

address::address() : building(0){
    memset(name, '\0', sizeof(name));
    memset(street, '\0', sizeof(street));
}

address::address(char name[], char street[], int building) : building(building){
    strcpy(this->name, name);
    strcpy(this->street, street);
}

address::~address() {
    if(*street) memset(street, '\0', sizeof(street));
    if(*name) memset(name, '\0', sizeof(name));
    building = 0;
}

ostream &operator<<(ostream &out, const address &obj){
    out << "Имя: " << obj.name << "\nУлица: " << obj.street << "\nНомер дома: " << obj.building << endl;
    return out;
}

istream &operator>>(istream &in,  address &obj){
    in >> obj.name >> obj.street >> obj.building;
    return in;
}

address &address::operator=(const address &that){
    strcpy(this->name, that.name);
    strcpy(this->street, that.street);
    this->building = that.building;
    return *this;
}
