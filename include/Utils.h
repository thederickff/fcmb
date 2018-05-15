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
#ifndef __Fcmb__Utils__
#define __Fcmb__Utils__

#define DEBUG 1

#if DEBUG
  #define LOG(x) std::cout << x << std::endl;
#else
  #define LOG(x)
#endif

#include <fstream>

namespace Fcmb {

  inline bool FileExists(const std::string& filename)
  {
    return std::fstream(filename, std::ios::binary | std::ios::in).is_open();
  }

  inline bool InvalidDir(const std::string& dir)
  {
    return dir[dir.size()-1] != '/';
  }

  void CopyBinary(const std::string& source, const std::string& target);
  void MoveBinary(const std::string& source, const std::string& target);
}

#endif /* defined(__Fcmb__Scanner__) */
