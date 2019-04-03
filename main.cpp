//
// Created by alexc on 4/2/2019.
//
#include "Vocabulary.h"
using namespace openvac;

int main()
{
    Vocabulary gg;
    Vocabulary bg;
    char fname[256];
    std::cin >> fname;
    gg.READFILE("C:\\Users\\alexc\\YandexDisk\\ITMO_F_vocanulary\\data.txt");
    bg.READFILE("C:\\Users\\alexc\\YandexDisk\\ITMO_F_vocanulary\\data2.txt");
    gg.PRINT();
    bg.INSERT("IvanIvanovich");


return 0;
}