//
// Created by alexc on 4/2/2019.
//

#include "Vocabulary.h"

openvac::Vocabulary::Vocabulary()
{
    _arr = nullptr;
    _size = 0;
}

openvac::Vocabulary::~Vocabulary()
{
    MAKENULL();
}

void openvac::Vocabulary::MAKENULL()
{
    if(_arr != nullptr)
    {
        //_arr = deleteArr(_arr);
    }
}

void openvac::Vocabulary::INSERT(const char * x)
{
    if(_arr == nullptr)
    {
        _size = 1;
        _arr = new node[1];
        _arr[0].data = new char[20]; //ПОВТОР КОД!
        strcpy(_arr[0].data, x);
        return;
    }
    int B = _size / 10;
    int key = getKey(x);
    int hs = hash(key, B);
    if(searchArEl(hs))
    {
        node * temp = searchClassEl(hs);
        if(temp != nullptr)
            return;
        _arr[hs].next = add_to_list(_arr[hs].next, x);
        return;
    }
    _arr[hs].data = new char[20]; //ПОВТОР КОД!
    strcpy(_arr[hs].data, x);
}

void openvac::Vocabulary::READFILE(const char * filename)
{
    std::cout << "READ START " << filename << std::endl;
    std::ifstream myReadFile;
    myReadFile.open(filename);

    if (myReadFile.is_open())
    {
        myReadFile >> _size;
        std::cout << "READ SIZE " << _size << std::endl;
        _arr = new node[_size];
        int i = 0;
        char data[20];
        while (!myReadFile.eof())
        {
            myReadFile >> data;
            _arr[i].data = new char[20];
            strcpy(_arr[i].data, data);
            i++;
        }
        myReadFile.close();
    }
}

void openvac::Vocabulary::PRINT() const
{
    node * iter;
    for(int i = 0; i < _size; ++i)
    {
        std::cout << _arr[i].data << std::endl;
        if(_arr[i].next != nullptr)
        {
            iter = _arr[i].next;
            while(iter != nullptr)
            {
                std::cout << iter -> data << std::endl;
                iter = iter -> next;
            }
        }
    }
}