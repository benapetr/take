 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.


#include <iostream>
#include "../include/Preferences.h"
#include "../include/Debugging.h"

//! Log a text
//! @param text text to log
void Debugging::Log(string text)
{
    cout << text << endl;
}

//! Log an error text
//! @param text text to log
void Debugging::ErrorLog(string text)
{
    cerr << "ERROR: " << text << endl;
}

//! Log a warning text
//! @param text text to log
void Debugging::WarningLog(string text)
{
    cerr << "WARNING: " << text << endl;
}

//! Log a text
//! @param text text to log
void Debugging::DebugLog(string text, int verbosity)
{
    if (Preferences::Verbosity >= verbosity)
    {
        cout << "DEBUG: " << text << endl;
    }
}
