#include <iostream>
#include <fstream>

#include "Scanner.h"
#include "Cwsq.h"
#include "Mindtct.h"
#include "Util.h"

int debug = 0;

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << argv[0] << " [directory] [name]\n" << std::endl;
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

	Util::MoveBinary((directory + name + bmp_ext).c_str(), (directory + std::string("bmp\\") + name + bmp_ext).c_str());

	return 0;
}