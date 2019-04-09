//
// Created by alexc on 4/2/2019.
//

#include "Vocabulary.h"

openvac::Vocabulary::~Vocabulary()
{
    MAKENULL();
}

void openvac::Vocabulary::MAKENULL()
{
    deleteArr();
}

void openvac::Vocabulary::DELETE(const char * x)
{
    int B = SIZE / 2; //повтор код????
    int key = getKey(x);
    int hs = hash(key, B);
    if(!searchArEl(hs))
        return;
    node * temp;
    if(strcmp(_arr[hs].data, x) != 0)
    {
        if(_arr[hs].next == nullptr)
            return;
        if(strcmp(_arr[hs].next -> data, x) != 0)
        {
            temp = searchClassEl(_arr[hs].next, x);
            if(temp == nullptr)
                return;
            node * cur = temp -> next;
            temp -> next = cur -> next;
            delete cur;
        } else
        {
            temp = _arr[hs].next;//
            _arr[hs].next = _arr[hs].next -> next;//
            delete temp; //ПОВТОР КОД
        }
    } else
    {
        if(_arr[hs].next != nullptr)
        {
            strcpy(_arr[hs].data, _arr[hs].next -> data);
            temp = _arr[hs].next;//
            _arr[hs].next = _arr[hs].next -> next;//
            delete temp; //ПОВТОР КОД
        } else
        {
            delete[] _arr[hs].data;
            _arr[hs].data = nullptr;
        }
    }
}

void openvac::Vocabulary::INSERT(const char * x)
{
    int B = SIZE / 2; //повтор код????
    int key = getKey(x);
    int hs = hash(key, B);
    //std::cout << "{source: " << x << "}, {key: " << key << "}, {B: " << B << "}, " << "{hash: " << hs << "}" << std::endl;
    if(searchArEl(hs))
    {
        if(strcmp(_arr[hs].data, x) == 0)
            return;
        if(_arr[hs].next != nullptr)
        {
            if(existListEl(hs, x))
                return;
        }
        _arr[hs].next = add_to_list(_arr[hs].next, x);
        return;
    }
    _arr[hs].data = new char[20];
    strcpy(_arr[hs].data, x);
}

bool openvac::Vocabulary::MEMBER(const char * x) const
{
    int B = SIZE / 2; //повтор код????
    int key = getKey(x);
    int hs = hash(key, B);
    if(searchArEl(hs))
    {
        if(strcmp(_arr[hs].data, x) == 0)
            return true;
        if(_arr[hs].next != nullptr)
        {
            return existListEl(hs, x);
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

int openvac::Vocabulary::hash(int key, int b) const
{
    return key % b;
}

int openvac::Vocabulary::getKey(const char * data) const
{
    int key = 0;
    for (int i = 0; i < strlen(data); ++i)
    {
        key += data[i];
    }
    return key;
}

bool openvac::Vocabulary::existListEl(int hs, const char * x) const
{
    if(strcmp(_arr[hs].next -> data, x) == 0)//Отдельная функция возможно
        return true;
    node * temp = searchClassEl(_arr[hs].next, x);
    if(temp != nullptr)
        return true;
    return false;
}

bool openvac::Vocabulary::searchArEl(int cl) const
{
    return _arr[cl].data != nullptr;
}

openvac::node * openvac::Vocabulary::add_to_list(node * head, const char * x)
{
    node * temp = new node(x, head);
    return temp;
}

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

void openvac::Vocabulary::deleteArr()
{
    int i = 0;
    for(; i < SIZE; i++)
    {
        if(_arr[i].data != nullptr)
        {
            if(_arr[i].next != nullptr)
            {
                _arr[i].next = deleteList(_arr[i].next);
            }
            delete[] _arr[i].data;
        }
    }
}

openvac::node * openvac::Vocabulary::deleteList(node * head)
{
    node * temp1;
    node * temp2 = head;
    while (temp2 != nullptr)
    {
        temp1 = temp2;
        temp2 = temp2 -> next;
        delete temp1;
    }
    head = nullptr;
    return head;
}