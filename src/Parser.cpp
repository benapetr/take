 // This program is free software; you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation; either version 2 of the License, or
 // (at your option) version 3.

 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.

#include <string.h>
#include "../include/Parser.h"
#include "../include/Preferences.h"
#include "../include/Debugging.h"

//! Constructor of parser class
Parser::Parser(int c, char *v[])
{
    argc = c;
    argv = v;
}

//! Print a help for command
void Parser::ShowHelp()
{
    cout << "Usage: take [-rhvg] file [file2]..." << endl;
    cout << "take is overtaking the ownership and group of file or folder, in case its parent folder is owned by you" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  -h [--help]: Display this help" << endl;
    cout << "  -g [--group]: Overtake also a group, by default your primary group" << endl;
    cout << "  -v: Increases verbosity" << endl;
    cout << "  -r [--recursive]: Take files in a folder recursively" << endl << endl;
    cout << "Take version " << Preferences::Version << endl << endl;
    cout << "This software is open source licensed under GPL v. 3, see https://github.com/benapetr/take for source code" << endl;
}

//! Parse the parameters for program, return true if program is supposed to stop
bool Parser::Parse()
{
    if (argc < 2)
    {
        Debugging::Log("Usage: take [-rhvg] file1 [file2]...");
        return true;
    }

    int curr = 1;
    while (curr < argc)
    {
        string parameter = argv[curr];
        curr++;
        if (parameter == "-h" || parameter == "--help")
        {
            ShowHelp();
            return true;
        }
        if (parameter == "--group" || parameter == "-g")
        {
            Preferences::Group = true;
            continue;
        }
        if (parameter == "--recursive" || parameter == "-r")
        {
            Preferences::Recursive = true;
            continue;
        }
        if (parameter == "--version")
        {
            cout << "Take version: " << Preferences::Version << endl;
            return true;
        }
        if (parameter == "--")
        {
            if (curr >= argc)
            {
                Debugging::WarningLog("parameter -- can't be used without providing a name of some file or folder");
                return true;
            }
            string parm = argv[curr];
            curr++;
            Preferences::Objects.push_back(parm);
            continue;
        }
        if (parameter.size() > 1 && parameter.substr(0, 1) == "-")
        {
            unsigned int c = 1;
            while (c < parameter.size())
            {
                if ( parameter[c] == 'v' )
                {
                    Preferences::Verbosity++;
                }
                if ( parameter[c] == 'h' )
                {
                    ShowHelp();
                    return true;
                }
                if ( parameter[c] == 'r' )
                {
                    Preferences::Recursive = true;
                }
                if ( parameter[c] == 'g' )
                {
                    Preferences::Group = true;
                }
                c++;
            }
            continue;
        }
        Preferences::Objects.push_back(parameter);
    }

    if (Preferences::Objects.empty())
    {
        Debugging::ErrorLog("You need to provide a list of files to overtake owner for");
        return true;
    }

    return false;
}

Parser::~Parser()
{

}
