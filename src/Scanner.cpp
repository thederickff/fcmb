#include "Scanner.h"

#include <ftrScanAPI.h>

Scanner::Scanner(const std::string&output)
: m_Output(output)
{

}

Scanner::~Scanner()
{
  ftrScanCloseDevice(m_Device);
}

Scanner::Scanner(const Scanner& scanner)
: m_Output(scanner.m_Output)
{

}

Scanner& Scanner::operator=(const Scanner& scanner)
{
  if (&scanner != this)
  {
    this->m_Output = scanner.m_Output;
    //this->m_ImageSize = scanner.m_ImageSize;
  }
  return *this;
}

int Scanner::ScanImage()
{
  m_Device = ftrScanOpenDevice();

	if(m_Device == NULL)
	{
		std::cout << "Failed to open device!" << std::endl;
		return -1;
	}

	if(!ftrScanGetImageSize(m_Device, &m_ImageSize))
	{
		std::cout << "Failed to get image size\n";
		ftrScanCloseDevice(m_Device);
		return -1;
	}

	//if (debug > 0)
	std::cout << "Image size is " << m_ImageSize.nImageSize << "\n";

	m_Buffer = (unsigned char *) malloc(m_ImageSize.nImageSize);
	std::cout << "Please put your finger on the scanner: " << std::endl;
	while(true)
	{
		if(ftrScanIsFingerPresent(m_Device, NULL)) break;
		for(int i=0; i<50; i++);	//sleep(1)
	}

	//if (debug > 0)
	std::cout << "Capturing fingerprint ......\n";
  if(ftrScanGetFrame(m_Device, m_Buffer, NULL))
	{
		//if (debug > 0)
		std::cout << "Done!\nWriting to file......\n";

		WriteBmpFile(m_Buffer, m_ImageSize.nWidth, m_ImageSize.nHeight, m_Output.c_str());
	} else {
		free(m_Buffer);
		ftrScanCloseDevice(m_Device);
		return ShowError(ftrScanGetLastError());
	}

	free(m_pBuffer);
	ftrScanCloseDevice(m_Device);

	return 0;
}
int Scanner::ShowError(unsigned long errCode)
{
  // in case of moveable finger there is a way to try again
	if (nErrCode == FTR_ERROR_MOVABLE_FINGER) {
    return ScanImage();
	}

	std::cout << "Failed to get image:\n";
  switch(errCode)
  {
    case 0:
        std::cout << "OK";
        break;
    case FTR_ERROR_EMPTY_FRAME:	// ERROR_EMPTY
        std::cout << "- Empty frame -\n";
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
        std::cout << "Unknown return code - " << errCode << "\n";
  }
  return -1;
}

int Scanner::WriteBmpFile(unsigned char *image, int width, int height, const char *filename)
{
  BitmapInfo *pDIBHeader;
	BitmapFileHeader  bmfHeader;
	int iCyc;
	// allocate memory for a DIB header
	if((pDIBHeader = (BitmapInfo *) malloc(sizeof(BitmapInfo) + sizeof(RGBQuad) * 255)) == NULL)
	{
		std::cout << "Alloc memory failed! - Unable to write to file!!\n";
		return -1;
	}
	memset((void *) pDIBHeader, 0, sizeof(BitmapInfo) + sizeof(RGBQuad) * 255);
	// fill the DIB header
	pDIBHeader->header.size          = sizeof(BitmapInfoHeader);
	pDIBHeader->header.width         = width;
	pDIBHeader->header.height        = height;
	pDIBHeader->header.planes        = 1;
	pDIBHeader->header.bitCount      = 8;		// 8bits gray scale bmp
	pDIBHeader->header.compression   = 0;		// BI_RGB = 0;
	// initialize logical and DIB grayscale
	for(iCyc = 0; iCyc < 256; iCyc++)
	{
		pDIBHeader->colors[iCyc].rgbBlue = pDIBHeader->colors[iCyc].rgbGreen = pDIBHeader->colors[iCyc].rgbRed = (unsigned char) iCyc;
	}
	// set BitmapFileHeader structure
	bmfHeader.type = 0x42 + 0x4D * 0x100;
	bmfHeader.size = 14 + sizeof(BitmapInfo) + sizeof(RGBQuad) * 255 + width * height;	//sizeof(BitmapFileHeader) = 14
	bmfHeader.offBits = 14 + pDIBHeader->header.size + sizeof(RGBQuad) * 256;
	//write to file
	FILE *fp;
	fp = fopen(filename, "wb");
	if(fp == NULL)
	{
		std::cout << "Failed to write to file\n";
		free(pDIBHeader);
		return -1;
	}
	//fwrite((void *) &bmfHeader, 1, sizeof(BitmapFileHeader), fp);
	fwrite((void *) &bmfHeader.type, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &bmfHeader.size, sizeof(unsigned int), 1, fp);
	fwrite((void *) &bmfHeader.reserved1, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &bmfHeader.reserved2, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &bmfHeader.offBits, sizeof(unsigned int), 1, fp);
	//fwrite((void *) pDIBHeader, 1, sizeof( BitmapInfo ) + sizeof( RGBQuad ) * 255, fp);
	fwrite((void *) &pDIBHeader->header.size, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->header.width, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->header.height, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->header.planes, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &pDIBHeader->header.bitCount, sizeof(unsigned short int), 1, fp);
	fwrite((void *) &pDIBHeader->header.compression, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->header.sizeImage, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->header.xPelsPerMeter, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->header.yPelsPerMeter, sizeof(int), 1, fp);
	fwrite((void *) &pDIBHeader->header.clrUsed, sizeof(unsigned int), 1, fp);
	fwrite((void *) &pDIBHeader->header.clrImportant, sizeof(unsigned int), 1, fp);
	for( iCyc=0; iCyc<256; iCyc++ )
	{
		fwrite((void *) &pDIBHeader->colors[iCyc].rgbBlue, sizeof(unsigned char), 1, fp);
		fwrite((void *) &pDIBHeader->colors[iCyc].rgbGreen, sizeof(unsigned char), 1, fp);
		fwrite((void *) &pDIBHeader->colors[iCyc].rgbRed, sizeof(unsigned char), 1, fp );
		fwrite((void *) &pDIBHeader->colors[iCyc].rgbReserved, sizeof(unsigned char), 1, fp);
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

/*
#include <iostream>
#include <ftrScanApi.h>
#include <cstring>
#include "Scanner.h"
*/
