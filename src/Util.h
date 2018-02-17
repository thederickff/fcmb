#ifndef UTIL_H
#define UTIL_H

extern int debug;

class Util
{
public:
  static bool FileExists(const char* filename);
  static int CopyBinary(const char* fileNameFrom, const char* fileNameTo);
  static void MoveBinary(const char* fileNameFrom, const char* fileNameTo);
};

#endif // UTIL_H
