#ifndef BOZORTH3_H
#define BOZORTH3_H

#include <iostream>

extern int debug;

class Bozorth3
{
public:
    Bozorth3(std::string command);
    void execute();
private:
    std::string m_App_name;
    std::string m_Arguments;
};

#endif // BOZORTH3_H
