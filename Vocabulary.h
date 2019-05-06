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
    enum  {SIZE = 20/*размер массива*/, B = SIZE/2 /*количество классов*/};
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
//        ~node()
//        {
//            delete[] data;
//        }
    };


    class Vocabulary
    {
    public:
        //Нуже ли конструктор по умолчанию?
        ~Vocabulary();
        void MAKENULL(); //Чистим весь массив
        void INSERT(const char * x); //Добавляем элемент. Если такой элемент уже существует, то пишем в next
        void DELETE(const char * x); //Вызываем функцию поиска и удаляем элемент. Если элемент в массиве, то первый элемент next перекачует в массив
        void PRINT() const; //Вывод словаря
        bool MEMBER(const char * x) const;//Определяем принадлежит ли элемент множеству
    private:
        node _arr[SIZE];
        void deleteArr(); //Удаляем сначала next, потом data
        int hash(int key, int b) const; //хеширование key%b
        int getKey(const char * data) const; //Суммирует коды символов в строке
        bool existListEl(int hs, const char * x) const; //Существует ли элемент в списке
        bool searchArEl(int cl) const; //Возвращаем true, если в классе есть какое то значение
        node * searchClassEl(node * head, const char * x) const; //Ищем в списке next значение data(кроме головы), сравнивая строки(если есть, вернуть указатель на предыдущий элемент, если нет, то nullptr)
        node * add_to_list(node * head, const char * x); //Добавляем элемент в начало списка
        node * deleteList(node * head); //Чистим список
        void deleteHead(int hs);//Удаляем голову списка класса
    };
}

//в закрытом хешировании сравнить первый элемент с пустым символом

#endif //ITMO_F_VOCANULARY_VOCABULARY_H
