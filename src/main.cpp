#include <iostream>
#include <fstream>

#include "Scanner.h"
#include "Cwsq.h"
#include "Mindtct.h"

int debug = 0;

bool fileExists(const char* fileName)
{
	std::fstream file(fileName, std::ios::in);
	if (file.is_open()) {
		file.close();
		return true;
	}
	file.close();
	return false;
}

int copyBinary(const char* fileNameFrom, const char* fileNameTo)
{
	if (fileExists(fileNameTo)) {
		std::ifstream in(fileNameFrom, std::ios::binary);
		std::ofstream out(fileNameTo, std::ios::binary);
		out << in.rdbuf();
		out.close();
		in.close();
		return 0;
	}
	return -1;
}

void moveBinary(const char* fileNameFrom, const char* fileNameTo)
{
	if (copyBinary(fileNameFrom, fileNameTo) != 0) {
		std::cout << "Error copying file.\n";
	} else {
		if (remove(fileNameFrom) != 0)
			std::cout << "Error deleting file.\n";
		else if (debug > 0)
			std::cout << "File succesfully deleted";
	}
}

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

	moveBinary((directory + name + bmp_ext).c_str(), (directory + std::string("bmp\\") + name + bmp_ext).c_str());

	return 0;
}