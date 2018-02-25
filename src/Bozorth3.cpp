#include "Bozorth3.h"

Bozorth3::Bozorth3(std::string arguments) : m_App_name("exec\\bozorth3.exe "),
    m_Arguments(arguments) { }

void Bozorth3::execute()
{
    if (debug > 0)
        std::cout << "Executing Bozorth3..." << std:: endl;
    std::string command = m_App_name + m_Arguments;
    system(command.c_str());
}
