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
#include "Utils.h"

#include <iostream>
#include <fstream>

namespace Fcmb {
  void CopyBinary(const std::string& source, const std::string& target)
  {
    LOG("Copying binary")
    std::ifstream ifs(source, std::ios::binary);
    if (!ifs) {
      std::cout << "Failed to open file " << source << " for reading!" << std::endl;
      return;
    }
    std::ofstream ofs(target, std::ios::binary);
    if (!ofs) {
      std::cout << "Failed to open file " << target << " for writing!" << std::endl;
      return;
    }
    ofs << ifs.rdbuf();
  }

  void MoveBinary(const std::string& source, const std::string& target)
  {
    CopyBinary(source, target);
    remove(source.c_str());
  }
}
