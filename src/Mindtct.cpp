#include "Mindtct.h"

Mindtct::Mindtct(std::string file) : m_App_name("exec\\mindtct.exe "),
    m_Input_extension(".wsq "), m_File(file) { }

Mindtct::~Mindtct()
{
    std::string extensions[] = {".brw", ".dm", ".hcm", ".lcm", ".lfm", ".min", ".qm", ".wsq"};
    int size = sizeof(extensions) / sizeof(std::string);
    
    if (debug > 0)
        std::cout << "Clean up files" << std::endl;
    for (int i = 0; i < size; ++i)
    {
        remove((m_File + std::string(extensions[i])).c_str());
    }
}

void Mindtct::Execute()
{
    if (debug > 0)
        std::cout << "Executing Mindtct" << std::endl;
    std::string command = m_App_name + m_File + m_Input_extension + m_File;
    system(command.c_str());
}