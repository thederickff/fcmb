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
    throw ScannerException("Failed to open device!");
  }
}

Scanner::~Scanner()
{
  std::cout << "Device closed!" << std::endl;
  //free(m_Buffer);
  if (m_Device != NULL) ftrScanCloseDevice(m_Device);
  //else LOG("Device is null")//free(m_Buffer);
}

int Scanner::ScanImage()
{

  if(!ftrScanGetImageSize(m_Device, &m_ImageSize))
  {
    throw ScannerException("Failed to get image size");
  }

  //if (debug > 0)
  //std::cout << "Image size is " << m_ImageSize.nImageSize << "\n";
  LOG("Image size caught")

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

    WriteBmpFile(m_Buffer, m_ImageSize.nWidth, m_ImageSize.nHeight, m_Output.c_str());
    //write_bmp_file(m_Buffer, m_ImageSize.nWidth, m_ImageSize.nHeight, m_Output.c_str());
  } else {
    unsigned long error = ftrScanGetLastError();
    if (error == FTR_ERROR_MOVABLE_FINGER)
    {
      LOG("Trying again")
      return ScanImage();
    }
    else
    {
      return ShowError(error);
    }
  }

  return 0;
}
int Scanner::ShowError(unsigned long error)
{
  // in case of moveable finger there is a way to try again
  if (error == FTR_ERROR_MOVABLE_FINGER) {
    return ScanImage();
  }

  std::cout << "Failed to get image:\n";
  switch(error)
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
        std::cout << "Unknown return code - " << error << "\n";
  }

  return -1;
}

int Scanner::WriteBmpFile(unsigned char *image, int width, int height, const char *filename)
{
  BitmapInfo *bitmapInfo;
  BitmapFileHeader  bmfHeader;
  int iCyc;
  // allocate memory for a DIB header
  if((bitmapInfo = (BitmapInfo *) malloc(sizeof(BitmapInfo) + sizeof(RGBQuad) * 255)) == NULL)
  {
    std::cout << "Alloc memory failed! - Unable to write to file!!\n";
    return -1;
  }
  memset((void *) bitmapInfo, 0, sizeof(BitmapInfo) + sizeof(RGBQuad) * 255);
  // fill the DIB header
  bitmapInfo->bmiHeader.biSize          = sizeof(BitmapInfoHeader);
  bitmapInfo->bmiHeader.biWidth         = width;
  bitmapInfo->bmiHeader.biHeight        = height;
  bitmapInfo->bmiHeader.biPlanes        = 1;
  bitmapInfo->bmiHeader.biBitCount      = 8;		// 8bits gray scale bmp
  bitmapInfo->bmiHeader.biCompression   = 0;		// BI_RGB = 0;
  // initialize logical and DIB grayscale
  for(iCyc = 0; iCyc < 256; iCyc++)
  {
    bitmapInfo->bmiColors[iCyc].rgbBlue = bitmapInfo->bmiColors[iCyc].rgbGreen = bitmapInfo->bmiColors[iCyc].rgbRed = (unsigned char) iCyc;
  }
  // set BitmapFileHeader structure
  bmfHeader.bfType = 0x42 + 0x4D * 0x100;
  bmfHeader.bfSize = 14 + sizeof(BitmapInfo) + sizeof(RGBQuad) * 255 + width * height;	//sizeof(BitmapFileHeader) = 14
  bmfHeader.bfOffBits = 14 + bitmapInfo->bmiHeader.biSize + sizeof(RGBQuad) * 256;
  //write to file
  FILE *fp;
  fp = fopen(filename, "wb");
  if(fp == NULL)
  {
    std::cout << "Failed to write to file\n";
    free(bitmapInfo);
    return -1;
  }
  //fwrite((void *) &bmfHeader, 1, sizeof(BitmapFileHeader), fp);
  fwrite((void *) &bmfHeader.bfType, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bmfHeader.bfSize, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bmfHeader.bfReserved1, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bmfHeader.bfReserved2, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bmfHeader.bfOffBits, sizeof(unsigned int), 1, fp);
  //fwrite((void *) bitmapInfo, 1, sizeof( BitmapInfo ) + sizeof( RGBQuad ) * 255, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biSize, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biWidth, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biHeight, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biPlanes, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biBitCount, sizeof(unsigned short int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biCompression, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biSizeImage, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biXPelsPerMeter, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biYPelsPerMeter, sizeof(int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biClrUsed, sizeof(unsigned int), 1, fp);
  fwrite((void *) &bitmapInfo->bmiHeader.biClrImportant, sizeof(unsigned int), 1, fp);
  for( iCyc=0; iCyc<256; iCyc++ )
  {
    fwrite((void *) &bitmapInfo->bmiColors[iCyc].rgbBlue, sizeof(unsigned char), 1, fp);
    fwrite((void *) &bitmapInfo->bmiColors[iCyc].rgbGreen, sizeof(unsigned char), 1, fp);
    fwrite((void *) &bitmapInfo->bmiColors[iCyc].rgbRed, sizeof(unsigned char), 1, fp );
    fwrite((void *) &bitmapInfo->bmiColors[iCyc].rgbReserved, sizeof(unsigned char), 1, fp);
  }
    /////////////////////////// copy fingerprint image /////////////////////////////////////
  unsigned char *cptrData;
  unsigned char *cptrDIBData;
  unsigned char *pDIBData;

  pDIBData = (unsigned char *) malloc(height * width);
  memset((void *) pDIBData, 0, height * width);

  cptrData = m_Buffer + (height - 1) * width;
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
  free(bitmapInfo);

  return 0;
}
