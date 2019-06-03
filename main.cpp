//
// Created by alexc on 4/2/2019.
//
#include "Vocabulary.h"
using namespace closevac;

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
    std::cout << "_____________________________" << std::endl;
}

int main()
{
    Vocabulary gg;
    Vocabulary bg;
    READFILE("C:\\ITMO_F_vocanulary\\data.txt", gg);
    gg.PRINT();
    bg.INSERT("IvanIvanovich");
    std::cout << std::endl;
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
    std::cout << "MEMBER(GoLone): " << gg.MEMBER("123") << std::endl;
return 0;
}