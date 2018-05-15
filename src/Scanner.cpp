/*
* MIT License
*
* Copyright (c) 2018 Derick Felix <derickfelix@zoho.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Scanner.h"
#include "Utils.h"

#include <cstring>
#include <chrono>
#include <thread>

Scanner::Scanner(const std::string& output)
: m_Output(output)
{
  m_Device = ftrScanOpenDevice();

  if(m_Device == NULL)
  {
    if (ftrScanGetLastError() == 21) std::cout << "Permission denied, are you root?" << std::endl;
    throw ScannerException("Failed to open device!");
  }
}

Scanner::~Scanner()
{
  LOG("Device closed!")
  if (m_Device != NULL) ftrScanCloseDevice(m_Device);
  if (m_Buffer != NULL) free(m_Buffer);
}

void Scanner::ScanImage()
{

  if(!ftrScanGetImageSize(m_Device, &m_ImageSize))
  {
    throw ScannerException("Failed to get image size");
  }

  LOG("Image size caught: ")
  LOG(m_ImageSize.nImageSize)

  m_Buffer = (unsigned char *) malloc(m_ImageSize.nImageSize);

  std::cout << "Please put your finger on the scanner: " << std::endl;

  while(true)
  {
    ftrScanSetDiodesStatus(m_Device, (unsigned int)100/2, 0); // green led ON, red led OFF
    if(ftrScanIsFingerPresent(m_Device, NULL)) break;
    // sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  LOG("Capturing fingerprint...")

  if(ftrScanGetFrame(m_Device, m_Buffer, NULL))
  {
    LOG("Done\nWriting to file...")
    WriteBmpFile(m_ImageSize.nWidth, m_ImageSize.nHeight);
  }
  else
  {
    unsigned long error = ftrScanGetLastError();
    // in case of moveable finger there is a way to try again
    if (error == FTR_ERROR_MOVABLE_FINGER)
    {
      LOG("Trying again")
      ScanImage();
    }
    else
    {
      ShowError(error);
    }
  }
}

void Scanner::ShowError(unsigned long error)
{
  std::cout << "Failed to get image:" << std::endl;
  switch(error)
  {
    case 0:
        std::cout << "OK" ;
        break;
    case FTR_ERROR_EMPTY_FRAME:	// ERROR_EMPTY
        std::cout << "- Empty frame -" << std::endl;
        break;
    case FTR_ERROR_NO_FRAME:
        std::cout <<  "- No frame -" << std::endl;
        break;
    case FTR_ERROR_USER_CANCELED:
        std::cout << "- User canceled -" << std::endl;
        break;
    case FTR_ERROR_HARDWARE_INCOMPATIBLE:
        std::cout << "- Incompatible hardware -" << std::endl;
        break;
    case FTR_ERROR_FIRMWARE_INCOMPATIBLE:
        std::cout << "- Incompatible firmware -" << std::endl;
        break;
    case FTR_ERROR_INVALID_AUTHORIZATION_CODE:
        std::cout << "- Invalid authorization code -" << std::endl;
        break;
    default:
        std::cout << "Unknown return code - " << error << std::endl;
  }
}

void Scanner::WriteBmpFile(int width, int height)
{
  BitmapInfo *bitmapInfo;
  BitmapFileHeader bmfHeader;
  // allocate memory for a DIB header
  if((bitmapInfo = (BitmapInfo *) malloc(sizeof(BitmapInfo) + sizeof(RGBQuad) * 255)) == NULL)
  {
    throw ScannerException("Alloc memory failed! - Unable to write to file!!");
  }
  memset((void *) bitmapInfo, 0, sizeof(BitmapInfo) + sizeof(RGBQuad) * 255);
  // fill the DIB header
  bitmapInfo->header.size          = sizeof(BitmapInfoHeader);
  bitmapInfo->header.width         = width;
  bitmapInfo->header.height        = height;
  bitmapInfo->header.planes        = 1;
  bitmapInfo->header.bitCount      = 8;		// 8bits gray scale bmp
  bitmapInfo->header.compression   = 0;		// BI_RGB = 0;
  // initialize logical and DIB grayscale
  for(int i = 0; i < 256; i++)
  {
    bitmapInfo->colors[i].blue = bitmapInfo->colors[i].green = bitmapInfo->colors[i].red = (unsigned char) i;
  }
  // set BitmapFileHeader structure
  bmfHeader.type = 0x42 + 0x4D * 0x100;
  bmfHeader.size = 14 + sizeof(BitmapInfo) + sizeof(RGBQuad) * 255 + width * height;	//sizeof(BitmapFileHeader) = 14
  bmfHeader.offBits = 14 + bitmapInfo->header.size + sizeof(RGBQuad) * 256;
  //write to file
  FILE *fp;
  fp = fopen(m_Output.c_str(), "wb");
  if(fp == NULL)
  {
    free(bitmapInfo);
    throw ScannerException("Failed to write to file!");
  }

  fwrite((void *) &bmfHeader.type, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bmfHeader.size, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bmfHeader.reserved1, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bmfHeader.reserved2, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bmfHeader.offBits, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->header.size, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->header.width, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->header.height, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->header.planes, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bitmapInfo->header.bitCount, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bitmapInfo->header.compression, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->header.sizeImage, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->header.xPelsPerMeter, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->header.yPelsPerMeter, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->header.clrUsed, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->header.clrImportant, sizeof(unsigned int), 1, fp);
  for(int i = 0; i < 256; i++)
  {
    fwrite((void *) &bitmapInfo->colors[i].blue, sizeof(unsigned char), 1, fp);
    fwrite((void *) &bitmapInfo->colors[i].green, sizeof(unsigned char), 1, fp);
    fwrite((void *) &bitmapInfo->colors[i].red, sizeof(unsigned char), 1, fp );
    fwrite((void *) &bitmapInfo->colors[i].reserved, sizeof(unsigned char), 1, fp);
  }
  ////////////////////////// copy fingerprint image ////////////////////////////
  unsigned char *cptrData;
  unsigned char *cptrDIBData;
  unsigned char *pDIBData;

  pDIBData = (unsigned char *) malloc(height * width);
  memset((void *) pDIBData, 0, height * width);

  cptrData = m_Buffer + (height - 1) * width;
  cptrDIBData = pDIBData;
  for(int i = 0; i < height; i++)
  {
    memcpy(cptrDIBData, cptrData, width);
    cptrData = cptrData - width;
    cptrDIBData = cptrDIBData + width;
  }
  fwrite((void *) pDIBData, 1, width * height, fp);
  fclose(fp);

  std::cout << "Fingerprint image is written to file: " << m_Output << std::endl;

  free(pDIBData);
  free(bitmapInfo);

}
