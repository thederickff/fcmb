#include <iostream>

#include "Scanner.h"
#include "Cwsq.h"
#include "Mindtct.h"

int debug = 1;

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
	if(scanner.ScanImage(filename) != 0) return -1;
	// Compress bitmap file to WSQ
	Cwsq cwsq(filename + bmp_ext);
	cwsq.Execute();
	// Generate fingerprint caracteristics (.xyt file)
	Mindtct mindtct(filename);

	mindtct.Execute();

	return 0;
}