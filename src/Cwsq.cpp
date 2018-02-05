#include "Cwsq.h"

Cwsq::Cwsq(std::string image)
    : m_App_name("exec\\cwsq.exe "), m_Output("2.25 wsq "),
      m_Image(image), m_Image_settings(" -raw_in 320,480,8") { }

void Cwsq::Execute()
{
    if (debug > 0)
        std::cout << "Executing Cwsq" << std::endl;
    std::string command = m_App_name + m_Output + m_Image + m_Image_settings;
	system(command.c_str());	
}