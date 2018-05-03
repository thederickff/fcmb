#ifndef __Fcmb__Scanner__
#define __Fcmb__Scanner__

#include <iostream>
//#include <ftrScanApi.h>

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

class Scanner {
public:
  Scanner(const std::string &output);
  Scanner(const Scanner &scanner);
  Scanner &operator=(const Scanner &scanner);
  ~Scanner();

  int ScanImage();
private:
  int ShowError(unsigned long errCode);
  int WriteBmpFile(unsigned char *image, int width, int height, const char *filename);
private:

  void *m_Device;
  std::string m_Output;
  unsigned char *m_Buffer;
  //FTRSCAN_IMAGE_SIZE m_ImageSize;
};

/*
typedef struct tagBITMAPINFOHEADER {
    unsigned int 		biSize;
    int					biWidth;
    int					biHeight;
    unsigned short int 	biPlanes;
    unsigned short int 	biBitCount;
    unsigned int 		biCompression;
    unsigned int 		biSizeImage;
    int					biXPelsPerMeter;
    int					biYPelsPerMeter;
    unsigned int 		biClrUsed;
    unsigned int 		biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;


typedef struct tagRGBQUAD {
   	unsigned char rgbBlue;
   	unsigned char rgbGreen;
   	unsigned char rgbRed;
   	unsigned char rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO {
   	BITMAPINFOHEADER 	bmiHeader;
   	RGBQUAD 			bmiColors[1];
} BITMAPINFO, *PBITMAPINFO;


typedef struct tagBITMAPFILEHEADER {
   	unsigned short int 	bfType;
   	unsigned int 		bfSize;
   	unsigned short int 	bfReserved1;
   	unsigned short int 	bfReserved2;
   	unsigned int 		bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
*/

#endif /* defined(__Fcmb__Scanner__) */
