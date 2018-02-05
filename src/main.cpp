#include <iostream>

#include "Scanner.h"

int debug = 0;

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << argv[0] << " [option] [name]\n" << std::endl;
		std::cerr << "Options:" << std::endl;
		std::cerr << "enroll\t\tEnroll a new fingerprint" << std::endl;
		//std::cerr << "compare\t\tCompare with a existing fingerprint\n" << std::endl;
		return 1;
	}
	Scanner scanner;
	std::string filename = argv[2];

	scanner.ScanImage(filename);

	std::string oconfig = "2.25 wsq ";
	std::string ifile = filename + std::string(".bmp ");
	std::string raw_in = "-raw_in 320,480,8";	/* image characteristic parameters */

	std::string command = std::string("exec\\cwsq.exe ") + oconfig + ifile + raw_in;
	system(command.c_str());	

	return 0;
}