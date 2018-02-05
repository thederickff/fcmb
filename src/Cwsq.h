#ifndef CWSQ_H
#define CWSQ_H

#include <iostream>

extern int debug;

class Cwsq 
{
public:
    Cwsq(std::string image);
    void Execute();
private:
    std::string m_App_name;
    std::string m_Output;
    std::string m_Image;
    std::string m_Image_settings;
};

#endif // CWSQ_H