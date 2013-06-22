#include <string.h>
#include "../include/Parser.h"
#include "../include/Preferences.h"
#include "../include/Debugging.h"

Parser::Parser(int c, char *v[])
{
    argc = c;
    argv = v;
}

void Parser::ShowHelp()
{
    cout << "Usage: take [-rhvg] [group] file [file2]..." << endl;
    cout << "take is overtaking the ownership and group of file or folder, in case its parent folder is owned by you" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  -h [--help]: Display this help" << endl;
    cout << "  -g [--group]: Overtake also a group, by default your primary group" << endl;
    cout << "  -v: Increases verbosity" << endl;
    cout << "  -r [--recursive]: Take files in a folder recursively" << endl << endl;
    cout << "This software is open source licensed under GPL v. 3, see https://github.com/benapetr/take" << endl;
}

bool Parser::Parse()
{
    if (argc < 2)
    {
        Debugging::Log("Usage: take [-rhvg] [group] file1 [file2]...");
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
        if (parameter == "recursive" || parameter == "-r")
        {
            Preferences::Recursive = true;
            continue;
        }
        if (parameter == "--")
        {
            if (curr >= argc)
            {
                Debugging::WarningLog("parameter -- can't be used alone");
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
