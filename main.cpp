//
// Created by alexc on 4/2/2019.
//
#include "Vocabulary.h"
using namespace openvac;

void READFILE(const char * filename, Vocabulary & ob)
{
    std::cout << "READ START " << filename << std::endl;
    std::ifstream myReadFile;
    myReadFile.open(filename);

    if (myReadFile.is_open())
    {
        char data[20];
        while (!myReadFile.eof())
        {
            myReadFile >> data;
            ob.INSERT(data);
        }
        myReadFile.close();
    }
}

int main()
{
    Vocabulary gg;
    Vocabulary bg;
    char fname[256];
    //std::cin >> fname;
    READFILE("C:\\Users\\alexc\\YandexDisk\\ITMO_F_vocanulary\\data.txt", gg);
    //bg.READFILE("C:\\Users\\alexc\\YandexDisk\\ITMO_F_vocanulary\\data2.txt");
    gg.PRINT();
    bg.INSERT("IvanIvanovich");
    std::cout << std::endl;
    //bg.PRINT();
    bg.INSERT("IvanovichIvan");
    bg.INSERT("IvanIvanovich");
    bg.INSERT("PavelZuzev");
    bg.INSERT("Bob bob");
    bg.INSERT("VanVanVanKukumber");
    std::cout << std::endl;
    //bg.PRINT();
    gg.DELETE("AnnJon");
    gg.PRINT();
    std::cout << std::endl;
    gg.DELETE("GoLone");
    //gg.DELETE("GoGO");
    gg.PRINT();
    std::cout << "MEMBER(BobBern): " << gg.MEMBER("BobBern") << std::endl;
    std::cout << "MEMBER(GoLone): " << gg.MEMBER("GoLone") << std::endl;

return 0;
}