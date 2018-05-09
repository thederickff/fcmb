#include <iostream>
#include <sstream>

bool isInvalid(const std::string &directory)
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

  return 0;
}
