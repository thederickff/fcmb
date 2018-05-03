#include "Scanner.h"

Scanner::Scanner(const std::string &output)
: m_Output(output)
{

}

Scanner::~Scanner()
{

}

Scanner::Scanner(const Scanner &scanner)
: m_Output(scanner.m_Output)
{

}

Scanner &Scanner::operator=(const Scanner &scanner)
{
  if (&scanner != this)
  {
    this->m_Output = scanner.m_Output;
    //this->m_ImageSize = scanner.m_ImageSize;
  }
  return *this;
}

int Scanner::ScanImage()
{
  return 0;
}
int Scanner::ShowError(unsigned long errCode)
{
  return 0;
}

int Scanner::WriteBmpFile(unsigned char *image, int width, int height, const char *filename)
{
  return 0;
}
