#include <iostream>

#include "Scanner.h"
#include "Cwsq.h"
#include "Mindtct.h"

int debug = 1;

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << argv[0] << " [directory] [name]\n" << std::endl;
		//std::cerr << "Options:" << std::endl;
		//std::cerr << "enroll [directory] [name]\tGenerates a .xyt file" << std::endl;
		//std::cerr << "verify galleryfile.xyt\t\tOne to one matching" << std::endl;
		//std::cerr << "compare\t\tCompare with a existing fingerprint\n" << std::endl;
		return 1;
	}

	std::string directory = argv[1];
	directory += std::string("\\");
	std::string name = argv[2];
	std::string bmp_ext = ".bmp";

	// Scan finger and generates a bitmap
	Scanner scanner;
	if(scanner.ScanImage(directory + name + bmp_ext) != 0) return -1;
	// Compress bitmap file to WSQ
	Cwsq cwsq(directory + name + bmp_ext);
	cwsq.Execute();
	// Generate fingerprint caracteristics (.xyt file)
	Mindtct mindtct(directory + name);
	mindtct.Execute();

	rename((directory + name + bmp_ext).c_str(), (directory + std::string("bmp\\") + name + bmp_ext).c_str());

	return 0;
}