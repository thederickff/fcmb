#include <iostream>
#include <fstream>
#include "Util.h"

bool Util::FileExists(const char* fileName)
{
	std::fstream file(fileName, std::ios::binary | std::ios::in);
	if (file.is_open()) {
		file.close();
		return true;
	}
	file.close();
	return false;
}

int Util::CopyBinary(const char* fileNameFrom, const char* fileNameTo)
{
	std::ifstream in(fileNameFrom, std::ios::binary);
	std::ofstream out(fileNameTo, std::ios::binary);
	out << in.rdbuf();
	out.close();
	in.close();
	return 0;
}

void Util::MoveBinary(const char* fileNameFrom, const char* fileNameTo)
{
	if (CopyBinary(fileNameFrom, fileNameTo) != 0) {
		std::cout << "Error copying file.\n";
	} else {
		if (remove(fileNameFrom) != 0)
			std::cout << "Error deleting file.\n";
		else if (debug > 0)
			std::cout << "File succesfully deleted";
	}
}
