// vim: set ts=2 sw=2 expandtab:

// Copyright (c) 2014 Luchang Jin
// All rights reserved.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <sstream>
#include <string>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cassert>

namespace qshow {

inline std::string vssprintf(const char* fmt, va_list args)
{
  std::string str;
  char* cstr;
  int ret = vasprintf(&cstr, fmt, args);
  assert(ret >= 0);
  str += std::string(cstr);
  std::free(cstr);
  return str;
}

inline std::string ssprintf(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return vssprintf(fmt, args);
}

inline std::string show()
{
  return "";
}

inline std::string show(const int& x)
{
  return ssprintf("%d", x);
}

inline std::string show(const unsigned int& x)
{
  return ssprintf("%u", x);
}

inline std::string show(const long& x)
{
  return ssprintf("%ld", x);
}

inline std::string show(const unsigned long& x)
{
  return ssprintf("%lu", x);
}

inline std::string show(const double& x)
{
  return ssprintf("%24.17E", x);
}

inline std::string show(const bool& x)
{
  return x ? "true" : "false";
}

inline std::string show(const std::string& x)
{
  std::ostringstream out;
  out << x;
  return out.str();
}

template <class T>
std::string shows(const T& x)
{
  std::ostringstream out;
  out << x;
  return out.str();
}

template <class T>
T& reads(T& x, const std::string& str)
{
  std::istringstream in(str);
  in >> x;
  return x;
}

inline long read_long(const std::string& str)
{
  long ret = 0;
  reads(ret, str);
  return ret;
}

inline double read_double(const std::string& str)
{
  double ret = 0.0;
  reads(ret, str);
  return ret;
}

inline FILE*& get_output_file()
{
  static FILE* out = stdout;
  return out;
}

inline FILE*& get_monitor_file()
{
  static FILE* out = NULL;
  return out;
}

inline void display(const std::string& str, FILE* fp = NULL)
{
  if (NULL == fp) {
    fp = get_monitor_file();
    if (NULL != fp) {
      fprintf(fp, "%s", str.c_str());
    }
    fp = get_output_file();
  }
  if (NULL != fp) {
    fprintf(fp, "%s", str.c_str());
  }
}

inline void displayln(const std::string& str, FILE* fp = NULL)
{
  if (NULL == fp) {
    fp = get_monitor_file();
    if (NULL != fp) {
      fprintf(fp, "%s\n", str.c_str());
    }
    fp = get_output_file();
  }
  if (NULL != fp) {
    fprintf(fp, "%s\n", str.c_str());
  }
}

//////////////////////////////////////////////////////////////////

inline void fdisplay(FILE* fp, const std::string& str)
{
  fprintf(fp, "%s", str.c_str());
}

inline void fdisplayln(FILE* fp, const std::string& str)
{
  fprintf(fp, "%s\n", str.c_str());
}

}

#ifndef USE_NAMESPACE
using namespace qshow;
#endif
