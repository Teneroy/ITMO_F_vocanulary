//
// Created by alexc on 4/2/2019.
//

#ifndef ITMO_F_VOCANULARY_VOCABULARY_H
#define ITMO_F_VOCANULARY_VOCABULARY_H

#include <iostream>
#include "string.h"
#include <fstream>
//словарь открытое хеширование
namespace openvac
{
    enum  {SIZE = 20};
    struct node
    {
        char * data;
        node * next;
        node()
        {
            data = nullptr;
            next = nullptr;
        }
        node(const char * d, node * n):next(n)
        {
            data = new char[20];
            strcpy(data, d);
        }
        ~node()
        {
            delete[] data;
        }
    };


    class Vocabulary
    {
    public:
        ~Vocabulary();//НАДО ЛИ ПЕРЕГРУЖАТЬ ДЕСТРУКТОР?????
        void MAKENULL(); //Удаляем сначала next, потом сам массив, проверка на пустоту словаря
        void INSERT(const char * x); //добавляем, если такой элемент уже существует(detectClass и скорее всего searchSame), то пишем в next
        void DELETE(const char * x); //Вызываем функцию поиска и удаляем элемент, если элемент в массиве, то первый элемент next перекачует в массив
        void PRINT() const; //
        //MEMBER;//ищем элемент
    private:
        node _arr[SIZE];
        void deleteArr(); //Удаляем сначала next, потом сам массив
        int hash(int key, int b) const; //хеширование key%b
        int getKey(const char * data) const; //Суммирует коды символов в строке
        // функция поиска
        bool searchArEl(int cl) const; //возвращаем true, если в class есть какое то значение
        node * searchClassEl(node * head, const char * x) const; //ищем в списке next значение data, сравнивая строки(если есть, вернуть указатель, если нет, то nullptr)
        node * add_to_list(node * head, const char * x);
    };
}

//в закрытом хешировании сравнить первый элемент с пустым символом

#endif //ITMO_F_VOCANULARY_VOCABULARY_H
