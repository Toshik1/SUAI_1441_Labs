#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node //Структура являющаяся звеном списка
{
    int x; //Значение x будет передаваться в список
    Node *Next, *Prev; //Указатели на адреса следующего и предыдущего элементов списка
};

class List //Создаем тип данных Список
{
    Node *Head, *Tail; //Указатели на адреса начала списка и его конца
public:
    List()
        : Head(NULL)
        , Tail(NULL){}; //Инициализируем адреса как пустые
    ~List(); //Деструктор
    void show(); //Метод отображения списка на экране
    void push(int x); //Метод добавления элементов в список
    void reverse(); //Метод разворота списка
};

List::~List() //Деструктор
{
    while (Head) //Пока по адресу на начало списка что-то есть
    {
        Tail = Head->Next; //Резервная копия адреса следующего звена списка
        delete Head; //Очистка памяти от первого звена
        Head = Tail; //Смена адреса начала на адрес следующего элемента
    }
}

void List::push(int x)
{
    Node* temp = new Node; //Выделение памяти под новый элемент структуры
    temp->Next = NULL; //Указываем, что изначально по следующему адресу пусто
    temp->x = x; //Записываем значение в структуру

    if (Head != NULL) //Если список не пуст
    {
        temp->Prev = Tail; //Указываем адрес на предыдущий элемент в соотв. поле
        Tail->Next = temp; //Указываем адрес следующего за хвостом элемента
        Tail = temp; //Меняем адрес хвоста
    } else //Если список пустой
    {
        temp->Prev = NULL; //Предыдущий элемент указывает в пустоту
        Head = Tail = temp; //Голова=Хвост=тот элемент, что сейчас добавили
    }
}

void List::show()
{
    Node* temp = Head; //Временно указываем на адрес первого элемента
    while (temp != NULL) //Пока не встретим пустое значение
    {
        cout << temp->x << " "; //Выводим каждое считанное значение на экран
        temp = temp->Next; //Смена адреса на адрес следующего элемента
    }
    cout << "\n";
}

void List::reverse(){
    Node* temp = NULL; //Временный элемент для хранение последующих элементов
    Node* current = Head; //Элемент который мы сейчас обрабатываем
    while (current !=  NULL){ //Пока в списке есть поля
       temp = current->Prev; //Указываем на адрес следующего
       current->Prev = current->Next; //Меняем местами предыдущий и следующий
       current->Next = temp; //См. выше
       current = current->Prev; //Делаем текущий следующим
    }
    if(temp != NULL ) //Перед заменой головы списка проверяем не пустой ли список
        Head = temp->Prev; 
}

int main()
{
    int count; //Число элементов в список
    List lst; //Переменная, тип которой список
    srand(time(NULL)); //Инициализируем рандом по времени от начала запуска программы

    cout << "N = ";
    cin >> count; //Указали сколько элементов вводить в список

    for (int i = 0; i < count; i++) {
        int rand_data = rand()%9; //получаем рандомное значение
        lst.push(rand_data); //Добавление элемента в список
    }
    cout << "Original List:" << endl;
    lst.show(); //Вывод списка на экран
    lst.reverse(); //Переворачиваем список
    cout << "Reversed List:" << endl;
    lst.show(); //Вывод списка на экран
}