#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <ftrscanapi.h>

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


class Scanner {
public:
    int ScanImage(std::string output);
private:
    void *m_Device;
    unsigned char *m_pBuffer;
	FTRSCAN_IMAGE_SIZE m_ImageSize;

    void showError(unsigned long nErrCode);
    int write_bmp_file(unsigned char *pImage, int width, int height, const char* filename);
};

#endif // SCANNER_H