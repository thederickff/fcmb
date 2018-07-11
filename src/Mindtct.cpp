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
#include "Mindtct.h"
#include "Utils.h"

Mindtct::Mindtct(const std::string& name)
: m_Name(name)
{
  m_Command << "exec" << SEPARATOR << "mindtct " << name << ".wsq " << name;
}

Mindtct::~Mindtct()
{
  std::string extensions[] = {".brw", ".dm", ".hcm", ".lcm", ".lfm", ".min", ".qm", ".wsq"};
  int size = sizeof(extensions) / sizeof(std::string);
  LOG("Cleaning up files")
  for (int i = 0; i < size; ++i)
  {
    remove((m_Name + extensions[i]).c_str());
  }
  LOG("Done!")
}

void Mindtct::Execute()
{
  LOG("Executing Mindtct")
  system(m_Command.str().c_str());
  LOG("Done!")
}
