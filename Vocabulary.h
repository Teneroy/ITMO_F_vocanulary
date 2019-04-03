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

    struct node
    {
        char * data;
        node * next;
        node()
        {
            data = nullptr;
            next = nullptr;
        }
        node(char * d, node * n):data(d),next(n)
        {}
    };


    class Vocabulary
    {
    public:
        Vocabulary();
        ~Vocabulary();
        void MAKENULL(); //Удаляем сначала next, потом сам массив, проверка на пустоту словаря
        void INSERT(const char * x); //добавляем, если такой элемент уже существует(detectClass и скорее всего searchSame), то пишем в next
        void DELETE(char * x); //Вызываем функцию поиска и удаляем элемент, если элемент в массиве, то первый элемент next перекачует в массив
        void PRINT() const; //
        void READFILE(const char * filename);//Читаем из файла, выделяем память под массив в соответствии с размером в файле, пишем туда всю нашу красоту.
        //MEMBER;//ищем элемент
    private:
        node * _arr;
        int _size;
        node * deleteArr(node * arr); //Удаляем сначала next, потом сам массив
        int hash(int key, int b) const; //хеширование key%b
        int getKey(const char * data) const; //Суммирует коды символов в строке
        // функция поиска
        bool searchArEl(int cl) const; //возвращаем true, если в class есть какое то значение
        /*searchArEl
        return _arr[class].data != nullptr
        */
        node * searchClassEl(int cl) const; //ищем в списке next значение data, сравнивая строки(если есть, вернуть указатель, если нет, то nullptr)
        node * add_to_list(node * head, const char * x);
    };
}

//в закрытом хешировании сравнить первый элемент с пустым символом

#endif //ITMO_F_VOCANULARY_VOCABULARY_H
