#include <iostream>
#include "Scanner.h"

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << "dftr_scan [option] [file_name]\n" << std::endl;
		std::cerr << "Options:" << std::endl;
		std::cerr << "new\t\tCreate a new fingerprint" << std::endl;
		//std::cerr << "compare\t\tCompare with a existing fingerprint\n" << std::endl;
		return 1;
	}
	Scanner scanner;
	std::string filename = argv[2];

	scanner.ScanImage(filename);
	
	return 0;
}