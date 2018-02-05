#include <iostream>

#include "Scanner.h"
#include "Cwsq.h"

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
	// Scan finger and generates a bitmap
	Scanner scanner;
	std::string filename = argv[2];
	std::string bmp_ext = ".bmp";
	scanner.ScanImage(filename);
	// Compress bitmap file to WSQ
	Cwsq cwsq(filename + bmp_ext);
	cwsq.Execute();

	return 0;
}