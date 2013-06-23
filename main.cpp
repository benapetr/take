 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

#include <iostream>
#include <cstdio>
#include "include/Preferences.h"
#include "include/Debugging.h"
#include "include/Parser.h"
#include "include/Take.h"

using namespace std;


int main(int argc, char * argv[])
{
    // we check the parameters of program
    Parser* parser = new Parser(argc, argv);
    if (parser->Parse())
    {
        // when true is returned the application should exit
        // this happen for example on --help
        delete parser;
        return 0;
    }
    // we don't need to store parser in memory
    delete parser;
    // if --verbose we print some info
    if (Preferences::Verbosity > 0)
    {
        cout << "Verbosity: " << Preferences::Verbosity << endl;
        cout << "DEBUG: your uid: " << Preferences::uid << endl;
        cout << "DEBUG: your euid: " << Preferences::euid << endl;
        cout << "DEBUG: your gid: " << Preferences::guid << endl;
    }

    // in case the application isn't running as a root, we have problem
    if (Preferences::euid > 0)
    {
        Debugging::WarningLog("The binary is missing root suid!!!!!!!!");
    }

    // Information that group will be changed
    if (Preferences::Group)
    {
        Debugging::DebugLog("Will change the group as well");
    }

    if (Preferences::Recursive)
    {
        Debugging::DebugLog("Operating in recursive mode for all files");
    }

    list<string>::iterator iter;

    for(iter = Preferences::Objects.begin(); iter != Preferences::Objects.end(); iter++)
    {
        Take *take = new Take(*iter);
        delete take;
    }

    if (Preferences::Verbosity >= 1)
    {
        cout << "Totally overtaken: " << Take::Successful << " errors: " << Take::Errors << endl;
    }

    return Preferences::RC;
}
