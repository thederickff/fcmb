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
#ifndef __Fcmb__Scanner__
#define __Fcmb__Scanner__

#include <iostream>
#include <ftrScanAPI.h>

struct BitmapInfoHeader {
  unsigned long int	size;
  long int width;
  long int height;
  unsigned short int planes;
  unsigned short int bitCount;
  unsigned long int compression;
  unsigned long int sizeImage;
  long int xPelsPerMeter;
  long int yPelsPerMeter;
  unsigned long int clrUsed;
  unsigned long int	clrImportant;
};

struct RGBQuad {
  unsigned char blue;
  unsigned char green;
  unsigned char red;
  unsigned char reserved;
};

struct BitmapInfo {
  BitmapInfoHeader header;
  RGBQuad colors[1];
};

struct BitmapFileHeader {
  unsigned long int size;
  unsigned short int type;
  unsigned short int reserved1;
  unsigned short int reserved2;
  unsigned long int offBits;
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

  void ScanImage();
private:
  void ShowError(unsigned long error);
  void WriteBmpFile(int width, int height);
private:
  void *m_Device;
  std::string m_Output;
  unsigned char *m_Buffer;
  FTRSCAN_IMAGE_SIZE m_ImageSize;
};

#endif /* defined(__Fcmb__Scanner__) */
