#include <iostream>
#include "../include/Preferences.h"
#include "../include/Debugging.h"


void Debugging::Log(string text)
{
    cout << text << endl;
}

void Debugging::ErrorLog(string text)
{
    cerr << "ERROR: " << text << endl;
}

void Debugging::WarningLog(string text)
{
    cerr << "WARNING: " << text << endl;
}

void Debugging::DebugLog(string text, int verbosity)
{
    if (Preferences::Verbosity >= verbosity)
    {
        cout << "DEBUG: " << text << endl;
    }
}
