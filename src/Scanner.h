#ifndef __Fcmb__Scanner__
#define __Fcmb__Scanner__

#include <iostream>
#include <ftrScanAPI.h>

struct BitmapInfoHeader {
  int width;
  int height;
  int xPelsPerMeter;
  int yPelsPerMeter;
  unsigned int size;
  unsigned int compression;
  unsigned int sizeImage;
  unsigned int clrUsed;
  unsigned int clrImportant;
  unsigned short int planes;
  unsigned short int bitCount;
};

struct RGBQuad {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char reserved;
};

struct BitmapInfo {
  BitmapInfoHeader header;
  RGBQuad colors[1];
};

struct BitmapFileHeader {
  unsigned int size;
  unsigned short int type;
  unsigned short int offBits;
  unsigned short int reserved1;
  unsigned short int reserved2;
};

class ScannerException {
public:
  ScannerException(const std::string& message)
  : m_message(message)  { }

  std::string what() const { return m_message; }
private:
  std::string m_message;
};

class Scanner {
public:
  Scanner(const std::string& output);
  Scanner(const Scanner& scanner) = delete;
  Scanner& operator=(const Scanner& scanner) = delete;
  ~Scanner();

  int ScanImage();
private:
  int ShowError(unsigned long error);
  int WriteBmpFile(unsigned char *image, int width, int height, const char *filename);
private:

  void *m_Device;
  std::string m_Output;
  unsigned char *m_Buffer;
  FTRSCAN_IMAGE_SIZE m_ImageSize;
};

#endif /* defined(__Fcmb__Scanner__) */
