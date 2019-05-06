//
// Created by alexc on 4/2/2019.
//

#include "Vocabulary.h"

openvac::Vocabulary::~Vocabulary()
{
    deleteArr();
}

//Чистим весь массив
void openvac::Vocabulary::MAKENULL()
{
    deleteArr();
}

//Вызываем функцию поиска и удаляем элемент. Если элемент в массиве, то первый элемент next перекачует в массив
void openvac::Vocabulary::DELETE(const char * x)
{
    int key = getKey(x);//Суммируем коды символов для получения ключа
    int hs = hash(key, B); //Хешируем
    if(!searchArEl(hs)) //Если элемент пуст, то выходим из функции
        return;
    node * temp;
    if(strcmp(_arr[hs].data, x) != 0) //Если удаляемый элемент не находится в ячейке массива
    {
        if(_arr[hs].next == nullptr) //Если список элементов класса пуст, то выходим из функции
            return;
        if(strcmp(_arr[hs].next -> data, x) != 0) //Если первый элемент списка не соответствует передаваемому значению
        {
            temp = searchClassEl(_arr[hs].next, x); //Ищем значение в остальном списке (вернется прошлый элемент или nullptr)
            if(temp == nullptr) //Если ничего не нашли, то выходим из функции
                return;
            node * cur = temp -> next;
            temp -> next = cur -> next;
            delete cur;
        } else
        {
            deleteHead(hs); // Удаляем голову списка класса
        }
    } else
    {
        if(_arr[hs].next != nullptr) //Если список класса не пуст
        {
            strcpy(_arr[hs].data, _arr[hs].next -> data); // Копируем данные из головы списка в массив
            deleteHead(hs);// Удаляем голову списка класса
        } else
        {
            delete[] _arr[hs].data; //Удаляем данные
            _arr[hs].data = nullptr;
        }
    }
}

//Добавляем элемент. Если такой элемент уже существует, то пишем в next
void openvac::Vocabulary::INSERT(const char * x)
{
    int key = getKey(x);
    int hs = hash(key, B);
    if(searchArEl(hs)) //Если элемент с таким хешом существует
    {
        if(strcmp(_arr[hs].data, x) == 0) //Если элемент уже есть в массиве, то выходим из функции
            return;
        if(_arr[hs].next != nullptr) //Если список класса не пустой
        {
            if(existListEl(hs, x)) //Если элемент уже есть в списке
                return;
        }
        _arr[hs].next = add_to_list(_arr[hs].next, x);//Добавляем в список новый элемент
        return;
    }
    _arr[hs].data = new char[20]; //Добавляем элемент в массив
    strcpy(_arr[hs].data, x);
}

//Определяем принадлежит ли элемент множеству
bool openvac::Vocabulary::MEMBER(const char * x) const
{
    int key = getKey(x);
    int hs = hash(key, B);
    if(searchArEl(hs))//Если элемент с таким хешом существует
    {
        if(strcmp(_arr[hs].data, x) == 0)//Если элемент уже есть в массиве, то возвращаем истину
            return true;
        if(_arr[hs].next != nullptr) //Если список класса не пустой
        {
            return existListEl(hs, x);//Если элемент уже есть в списке, то возвращаем истину
        }
    }
    return false;
}

void openvac::Vocabulary::PRINT() const
{
    node * iter;
    for(int i = 0; i < SIZE; ++i)
    {
        if(_arr[i].data != nullptr)
        {
            std::cout << "{" << i << "} " << _arr[i].data << " [";
            if(_arr[i].next != nullptr)
            {
                iter = _arr[i].next;
                while(iter != nullptr)
                {
                    std::cout << iter -> data << ", ";
                    iter = iter -> next;
                }
            }
            std::cout << "]" << std::endl;
        }
    }
}

//хеширование key%b
int openvac::Vocabulary::hash(int key, int b) const
{
    return key % b;
}

//Суммирует коды символов в строке
int openvac::Vocabulary::getKey(const char * data) const
{
    int key = 0;
    for (int i = 0; i < strlen(data); ++i)
    {
        key += data[i];
    }
    return key;
}

//Существует ли элемент в списке
bool openvac::Vocabulary::existListEl(int hs, const char * x) const
{
    if(strcmp(_arr[hs].next -> data, x) == 0)//Если данные в первом элементе совпадают с значением для поиска, то возвращаем истину
        return true;
    node * temp = searchClassEl(_arr[hs].next, x); //Ищем по всему остальному списку
    return temp != nullptr; //Если что то нашли, то вернем true, если нет, то false
}

//Возвращаем true, если в классе есть какое то значение
bool openvac::Vocabulary::searchArEl(int cl) const
{
    return _arr[cl].data != nullptr;
}

//Добавляем элемент в начало списка
openvac::node * openvac::Vocabulary::add_to_list(node * head, const char * x)
{
    node * temp = new node(x, head);
    return temp;
}

//Ищем в списке next значение data(кроме головы), сравнивая строки(если есть, вернуть указатель на предыдущий элемент, если нет, то nullptr)
openvac::node * openvac::Vocabulary::searchClassEl(node * head, const char * x) const
{
    node * temp = head -> next;
    node * prev = head;
    while (temp != nullptr)
    {
        if(strcmp(temp -> data, x) == 0)
            return prev;
        temp = temp -> next;
        prev = prev -> next;
    }
    return nullptr;
}

//Удаляем сначала next, потом data
void openvac::Vocabulary::deleteArr()
{
    int i = 0;
    for(; i < SIZE; i++)
    {
        if(_arr[i].data != nullptr) //Если класс не пустой
        {
            if(_arr[i].next != nullptr) //Если список класса не пустой
            {
                _arr[i].next = deleteList(_arr[i].next); //Удаляем список
            }
            delete[] _arr[i].data; // Удаляем данные из ячейки
        }
    }
}

//Чистим список
openvac::node * openvac::Vocabulary::deleteList(node * head)
{
    node * temp1;
    node * temp2 = head;
    while (temp2 != nullptr)
    {
        temp1 = temp2;
        temp2 = temp2 -> next;
        //delete[] temp1 -> data;
        delete temp1;
    }
    head = nullptr;
    return head;
}

//Удаляем голову списка класса
void openvac::Vocabulary::deleteHead(int hs)
{
    node * temp = _arr[hs].next;
    _arr[hs].next = _arr[hs].next -> next;
    delete temp;
}