#include <string.h>
#include "../include/Parser.h"
#include "../include/Preferences.h"
#include "../include/Debugging.h"

Parser::Parser(int c, char *v[])
{

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
    }

    int curr = 1;
    while (curr < argc)
    {
        string parameter = argv[curr];
        if (parameter == "-h" || parameter == "--help")
        {
            ShowHelp();
            continue;
        }
        if (parameter.size() > 2 && parameter.substr(0, 2) == "-v")
        {
            Preferences::Verbosity++;
            unsigned int c = 2;
            while (c < parameter.size())
            {
                if (parameter[c] != 'v' )
                {
                    break;
                }
                Preferences::Verbosity++;
                c++;
            }
            continue;
        }
        Preferences::Objects.push_back(parameter);
        curr++;
    }

    return false;
}

Parser::~Parser()
{

}
