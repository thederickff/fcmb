#include <iostream>
#include <sstream>

#include "Scanner.h"

bool isInvalid(const std::string& directory)
{
  return directory[directory.size()-1] != '/';
}

int main(int argc, const char *argv[])
{
  if (argc != 3)
  {
      std::cout << "usage: progName <directory> <name> " << std::endl;
      return 1;
  }

  std::string directory = argv[1];
  std::string name = argv[2];

  if (isInvalid(directory)) {
    std::cout << "Invalid directory name given!" << std::endl;
    return 2;
  }

  std::ostringstream oss;
  oss << directory << name << ".bmp";
  std::string filename = oss.str();

  std::cout << filename << std::endl;

  try
  {
      Scanner scanner("not connected");
      scanner.ScanImage();
  }
  catch (const ScannerException& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
