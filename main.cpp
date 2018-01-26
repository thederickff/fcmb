#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "ftrScanAPI.h"

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
    	unsigned char 	rgbBlue;
    	unsigned char 	rgbGreen;
    	unsigned char 	rgbRed;
    	unsigned char 	rgbReserved;
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

int write_bmp_file(unsigned char *pImage, int width, int height, const char* filename)
{
	BITMAPINFO *pDIBHeader;
	BITMAPFILEHEADER  bmfHeader;
	int iCyc;

	// allocate memory for a DIB header
	if((pDIBHeader = (BITMAPINFO *) malloc(sizeof(BITMAPINFO) + sizeof(RGBQUAD) * 255)) == NULL)
	{
		std::cout << "Alloc memory failed! - Unable to write to file!!\n";
		return -1;
	}
	memset((void *) pDIBHeader, 0, sizeof(BITMAPINFO) + sizeof(RGBQUAD) * 255);
	// fill the DIB header
	pDIBHeader->bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
	pDIBHeader->bmiHeader.biWidth         = width;
	pDIBHeader->bmiHeader.biHeight        = height;
	pDIBHeader->bmiHeader.biPlanes        = 1;
	pDIBHeader->bmiHeader.biBitCount      = 8;		// 8bits gray scale bmp
	pDIBHeader->bmiHeader.biCompression   = 0;		// BI_RGB = 0;	
	// initialize logical and DIB grayscale
	for(iCyc = 0; iCyc < 256; iCyc++)
	{
		pDIBHeader->bmiColors[iCyc].rgbBlue = pDIBHeader->bmiColors[iCyc].rgbGreen = pDIBHeader->bmiColors[iCyc].rgbRed = (unsigned char) iCyc;
	}
	// set BITMAPFILEHEADER structure
	//((char *)(&bmfHeader.bfType))[0] = 'B';
	//((char *)(&bmfHeader.bfType))[1] = 'M';
	bmfHeader.bfType = 0x42 + 0x4D * 0x100;
	bmfHeader.bfSize = 14 + sizeof(BITMAPINFO) + sizeof(RGBQUAD) * 255 + width * height;	//sizeof(BITMAPFILEHEADER) = 14
	bmfHeader.bfOffBits = 14 + pDIBHeader->bmiHeader.biSize + sizeof(RGBQUAD) * 256;
	//write to file
	FILE *fp;
	fp = fopen(filename, "wb");
	if(fp == NULL)
	{
		std::cout << "Failed to write to file\n";
		free(pDIBHeader);
		return -1;
	}
	//fwrite((void *) &bmfHeader, 1, sizeof(BITMAPFILEHEADER), fp);
	fwrite((void *) &bmfHeader.bfType, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &bmfHeader.bfSize, sizeof(unsigned int), 1, fp);
	fwrite((void *) &bmfHeader.bfReserved1, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &bmfHeader.bfReserved2, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &bmfHeader.bfOffBits, sizeof(unsigned int), 1, fp);
	//fwrite((void *) pDIBHeader, 1, sizeof( BITMAPINFO ) + sizeof( RGBQUAD ) * 255, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biSize, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biWidth, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biHeight, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biPlanes, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biBitCount, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biCompression, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biSizeImage, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biXPelsPerMeter, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biYPelsPerMeter, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biClrUsed, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->bmiHeader.biClrImportant, sizeof(unsigned int), 1, fp);
	for( iCyc=0; iCyc<256; iCyc++ )
	{
		fwrite((void *) &pDIBHeader->bmiColors[iCyc].rgbBlue, sizeof(unsigned char), 1, fp);
		fwrite((void *) &pDIBHeader->bmiColors[iCyc].rgbGreen, sizeof(unsigned char), 1, fp);
		fwrite((void *) &pDIBHeader->bmiColors[iCyc].rgbRed, sizeof(unsigned char), 1, fp );
		fwrite((void *) &pDIBHeader->bmiColors[iCyc].rgbReserved, sizeof(unsigned char), 1, fp);
	}
   	/////////////////////////// copy fingerprint image /////////////////////////////////////
	unsigned char *cptrData;
	unsigned char *cptrDIBData;
	unsigned char *pDIBData;

	pDIBData = (unsigned char *) malloc(height * width);
	memset((void *) pDIBData, 0, height * width);

	cptrData = pImage + (height - 1) * width;
	cptrDIBData = pDIBData;
	for(iCyc = 0; iCyc < height; iCyc++)
	{
		memcpy(cptrDIBData, cptrData, width);
		cptrData = cptrData - width;
		cptrDIBData = cptrDIBData + width;
	}
	fwrite((void *) pDIBData, 1, width * height, fp);
	fclose(fp);
	std::cout << "Fingerprint image is written to file: " << filename << ".\n";
	free(pDIBData);
	free(pDIBHeader);
	return 0;
}

// Show the Message
void ShowMsg(unsigned long nErrCode)
{
    switch( nErrCode ) 
	{
    case 0:
        std::cout << "OK";
        break;
    case FTR_ERROR_EMPTY_FRAME:	// ERROR_EMPTY
        std::cout << "- Empty frame -\n";
        break;
    case FTR_ERROR_MOVABLE_FINGER:
        std::cout << "- Movable finger -\n";
        break;
    case FTR_ERROR_NO_FRAME:
        std::cout <<  "- No frame -\n";
        break;
    case FTR_ERROR_USER_CANCELED:
        std::cout << "- User canceled -\n";
        break;
    case FTR_ERROR_HARDWARE_INCOMPATIBLE:
        std::cout << "- Incompatible hardware -\n";
        break;
    case FTR_ERROR_FIRMWARE_INCOMPATIBLE:
        std::cout << "- Incompatible firmware -\n";
        break;
    case FTR_ERROR_INVALID_AUTHORIZATION_CODE:
        std::cout << "- Invalid authorization code -\n";
        break;
    default:
        std::cout << "Unknown return code - " << nErrCode << "\n";
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << "dftr_scan [option] [file_name]\n" << std::endl;
		std::cerr << "Options:" << std::endl;
		std::cerr << "new\t\tCreate a new fingerprint" << std::endl;
		std::cerr << "compare\t\tCompare with a existing fingerprint\n" << std::endl;
		return 1;
	}
	std::string filename = argv[2];

	void *hDevice;
	FTRSCAN_IMAGE_SIZE ImageSize;
	unsigned char *pBuffer;
	int i;

	hDevice = ftrScanOpenDevice();
	if(hDevice == NULL)
	{
		std::cout << "Failed to open device!\n";
		return -1;
	} 

	if(!ftrScanGetImageSize(hDevice, &ImageSize))
	{
		std::cout << "Failed to get image size\n";
		ftrScanCloseDevice(hDevice);
		return -1;
	}
	else
	{
		std::cout << "Image size is " << ImageSize.nImageSize << "\n";
		pBuffer = (unsigned char *)malloc( ImageSize.nImageSize );
		std::cout << "Please put your finger on the scanner:\n";
		while(1)
		{
			if(ftrScanIsFingerPresent(hDevice, NULL))
				break;
			for(i=0; i<50; i++);	//sleep(1)
		}
		std::cout << "Capturing fingerprint ......\n";
		if(ftrScanGetFrame(hDevice, pBuffer, NULL) )
		{
			std::cout << "Done!\nWriting to file......\n";
			write_bmp_file(pBuffer, ImageSize.nWidth, ImageSize.nHeight, (filename + ".bmp").c_str());
		}
		else {
			std::cout << "Failed to get image:\n";
			ShowMsg(ftrScanGetLastError());
		}
			
		free(pBuffer);
	}

	ftrScanCloseDevice(hDevice);
	
	return 0;
}