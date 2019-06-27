//
// Created by alexc on 4/2/2019.
//

#include "Vocabulary.h"

openvac::Vocabulary::~Vocabulary()
{
    deleteArr(_arr);
}

//Чистим весь массив
void openvac::Vocabulary::MAKENULL()
{
    deleteArr(_arr);
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
            return;
        }
        temp = _arr[hs].next;
        _arr[hs].next = _arr[hs].next -> next;
        delete temp; // Удаляем голову списка класса
        return;
    } else
    {
        if(_arr[hs].next != nullptr) //Если список класса не пуст
        {
            node * next = _arr[hs].next;
            _arr[hs].data = next -> data;
            _arr[hs].next = next -> next;
            return;
        }
        delete[] _arr[hs].data; //Удаляем данные
        _arr[hs].data = nullptr;
        return;
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
void openvac::Vocabulary::deleteArr(node * arr)
{
    int i = 0;
    for(; i < SIZE; i++)
    {
        if(arr[i].data != nullptr) //Если класс не пустой
        {
            if(arr[i].next != nullptr) //Если список класса не пустой
            {
                arr[i].next = deleteList(arr[i].next); //Удаляем список
            }
            delete[] arr[i].data; // Удаляем данные из ячейки
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
        delete[] temp1 -> data;
        delete temp1;
    }
    head = nullptr;
    return head;
}

//void openvac::Vocabulary::deleteHead(int hs)
//{
//    node * temp = _arr[hs].next;
//    _arr[hs].next = _arr[hs].next -> next;
//    delete temp;
//}


/*____Закрытое хеширование____*/

closevac::Vocabulary::~Vocabulary()
{
    deleteArr();
}

void closevac::Vocabulary::MAKENULL()
{
    deleteArr();
}

void closevac::Vocabulary::INSERT(const char * x)
{
    int key = getKey(x);
    int hs = hash(key, 0);
    if(_arr[hs].data == nullptr)
    {
        _arr[hs].data = new char[20]; //отдельная функция?
        strcpy(_arr[hs].data, x);
        return;
    }
    int check = hs;
    int iter = 0;
    while(_arr[hs].data != nullptr && _arr[hs].data[0] != '\0')
    {
        if(strcmp(_arr[hs].data, x) == 0)
            return;
        iter++;
        hs = hash(key, iter);
        if(hs == check)
            return;
    }
    if(_arr[hs].data == nullptr)
        _arr[hs].data = new char[20]; //отдельная функция?
    strcpy(_arr[hs].data, x);
}

void closevac::Vocabulary::DELETE(const char * x)
{
    int key = getKey(x);
    int hs = hash(key, 0);
    if(_arr[hs].data == nullptr)
        return;
    if(strcmp(_arr[hs].data, x) == 0)
    {
        _arr[hs].data[0] = '\0';
        return;
    }
    //запуск ф-и поиска
    int search = searchEl(x, key, 0);
    if(search != ERR)
        _arr[search].data[0] = '\0';
}

bool closevac::Vocabulary::MEMBER(const char * x) const
{
    int key = getKey(x);
    int hs = hash(key, 0);
    if(_arr[hs].data == nullptr)
        return false;
    if(strcmp(_arr[hs].data, x) == 0)
    {
        return true;
    }
    //запуск ф-и поиска
    int search = searchEl(x, key, 0);
    return search != ERR;
}

int closevac::Vocabulary::searchEl(const char * x, int key, int iter) const
{
    iter++;
    int hs = hash(key, iter);
    if(_arr[hs].data == nullptr)
        return ERR;
    while (_arr[hs].data[0] == '\0' || strcmp(_arr[hs].data, x) != 0)
    {
        iter++;
        hs = hash(key, iter);
        if(_arr[hs].data == nullptr)
            return ERR;
    }
    return hs;

//    if(_arr[hs].data[0] == '\0')
//        return searchEl(x, key, iter);
//    if(strcmp(_arr[hs].data, x) == 0)
//    {
//        return hs;
//    } else
//    {
//        return searchEl(x, key, iter);
//    }
}

int closevac::Vocabulary::hash(int key, int iter) const
{
    return (key + iter) % SIZE;
}

int closevac::Vocabulary::getKey(const char * data) const
{
    int i = 0;
    int key = 0;
    for(; i < strlen(data); i++)
    {
        key += data[i];
    }
    return key;
}

int closevac::Vocabulary::getFreePos(int key, int iter) const
{
    int check = hash(key, 0);
    iter++;
    int hs = hash(key, iter);
    while(_arr[hs].data != nullptr && _arr[hs].data[0] != '\0')
    {
        iter++;
        hs = hash(key, iter);
        if(hs == check)
            return ERR;
    }
    return hs;
}

void closevac::Vocabulary::deleteArr()
{
    int i = 0;
    for(; i < SIZE; i++)
    {
        delete[] _arr[i].data; // Удаляем данные из ячейки
    }
}

void closevac::Vocabulary::PRINT() const
{
    int i = 0;
    for(; i < SIZE; i++)
    {
        std::cout << "{" << i << "}: " << ((_arr[i].data != nullptr && _arr[i].data[0] != '\0') ? _arr[i].data : "*") << std::endl;
    }
}