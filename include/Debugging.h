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
