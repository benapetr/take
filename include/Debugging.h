 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
#include <string.h>

using namespace std;

class Debugging
{
    public:
        static void Log(string text);
        static void DebugLog(string text, int verbosity = 1);
        static void WarningLog(string text);
        static void ErrorLog(string text);
};

#endif // DEBUGGING_H
