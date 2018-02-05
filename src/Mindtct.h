#ifndef MINDTCT_H
#define MINDTCT_H

#include <iostream>

extern int debug;

class Mindtct
{
public:
    Mindtct(std::string file);
    ~Mindtct();
    void Execute();
private:
    std::string m_App_name;
    std::string m_Input_extension;
    std::string m_File;
};

#endif // MINTCT_H